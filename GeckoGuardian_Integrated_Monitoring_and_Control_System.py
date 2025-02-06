import os
import csv
import time
import logging
import psutil
from threading import Thread, Lock
from datetime import datetime
from flask import Flask, jsonify
from gpiozero import OutputDevice, MotionSensor
from smbus2 import SMBus
from PIL import Image, ImageDraw, ImageFont
from luma.core.interface.serial import i2c
from luma.oled.device import ssd1306
from contextlib import contextmanager
import atexit

# ------------------- Configuration -------------------
CONFIG = {
    "TEMP_SENSOR_ADDRESS": 0x44,
    "I2C_BUS_TEMP_SENSOR": 1,  # Same I2C bus for both devices
    "I2C_BUS_OLED": 1,         # Same I2C bus for OLED
    "RELAY_BASKING_PIN": 27,
    "SENSOR_RESET_PIN": 22,
    "MOTION_SENSOR_PIN": 24,
    "BASKING_TEMP_MIN": 88.0,
    "BASKING_TEMP_MAX": 92.0,
    "NIGHT_TEMP_MAX": 75.0,
    "WINTER_HOURS": (7, 19),
    "OTHER_MONTHS_HOURS": (7, 21),
    "NVME_PATH": "/mnt/nvme",
    "SYSTEM_LOG_FILE": "system_logs.log",
    "TEMP_HUMIDITY_LOG_FILE": "temp_humidity_data.csv",
    "FLASK_PORT": 5000,
}

# Initialize paths
NVME_PATH = CONFIG["NVME_PATH"]
SYSTEM_LOG_FILE = os.path.join(NVME_PATH, CONFIG["SYSTEM_LOG_FILE"])
TEMP_HUMIDITY_LOG_FILE = os.path.join(NVME_PATH, CONFIG["TEMP_HUMIDITY_LOG_FILE"])

# ------------------- Initialize Hardware -------------------
bus = SMBus(CONFIG["I2C_BUS_TEMP_SENSOR"])
sensor_lock = Lock()

# Initialize OLED display
try:
    with sensor_lock:
        serial_oled = i2c(port=CONFIG["I2C_BUS_OLED"], address=0x3C)
        time.sleep(0.1)
        disp = ssd1306(serial_oled, width=128, height=64)
        disp.clear()
        disp.show()
except Exception as e:
    raise RuntimeError(f"Failed to initialize OLED: {e}")

width, height = disp.width, disp.height
image = Image.new("1", (width, height))
draw = ImageDraw.Draw(image)
font = ImageFont.load_default()

# Initialize other hardware
basking_relay = OutputDevice(CONFIG["RELAY_BASKING_PIN"], active_high=True, initial_value=False)
sensor_power = OutputDevice(CONFIG["SENSOR_RESET_PIN"], active_high=True, initial_value=True)
motion_sensor = MotionSensor(CONFIG["MOTION_SENSOR_PIN"], queue_len=1)

sensor_data = {"temperature": None, "humidity": None, "timestamp": None}

# ------------------- Logger Setup -------------------
def setup_logger(log_file):
    logger = logging.getLogger("LeopardGecko")
    logger.setLevel(logging.DEBUG)  # Set to DEBUG for detailed logs
    handler = logging.FileHandler(log_file)
    handler.setFormatter(logging.Formatter("%(asctime)s - %(levelname)s - %(message)s"))
    logger.addHandler(handler)
    return logger

logger = setup_logger(SYSTEM_LOG_FILE)

# Ensure CSV file exists
if not os.path.exists(TEMP_HUMIDITY_LOG_FILE):
    with open(TEMP_HUMIDITY_LOG_FILE, 'w', newline='') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(["Timestamp", "Temperature (F)", "Humidity (%)"])

@atexit.register
def cleanup_resources():
    with sensor_lock:
        basking_relay.close()
        sensor_power.close()
        motion_sensor.close()
        bus.close()
        disp.clear()
        disp.show()
    logger.info("Resources cleaned up successfully.")

# ------------------- I2C Functions -------------------
@contextmanager
def safe_i2c_communication(bus):
    try:
        yield bus
    except Exception as e:
        logger.error(f"I2C error: {e}")
        try:
            bus.close()
            time.sleep(1)
            bus.open(CONFIG["I2C_BUS_TEMP_SENSOR"])
        except Exception as recovery_error:
            logger.error(f"Failed to recover I2C bus: {recovery_error}")

def read_sensor_data():
    """Read temperature and humidity from the sensor."""
    global bus  # Ensure global bus usage
    for attempt in range(3):
        try:
            with sensor_lock, safe_i2c_communication(bus):
                bus.write_i2c_block_data(CONFIG["TEMP_SENSOR_ADDRESS"], 0x2C, [0x06])
                time.sleep(0.5)
                data = bus.read_i2c_block_data(CONFIG["TEMP_SENSOR_ADDRESS"], 0x00, 6)
                temp_raw = (data[0] << 8) | data[1]
                humidity_raw = (data[3] << 8) | data[4]
                temp_c = -45 + (175 * temp_raw / 65535.0)
                temp_f = temp_c * 9 / 5 + 32
                humidity = 100 * humidity_raw / 65535.0
                return round(temp_f, 1), round(humidity, 1)
        except Exception as e:
            logger.error(f"I2C error on attempt {attempt + 1}/3: {e}")
            time.sleep(2)
    logger.warning("All I2C read attempts failed. Resetting sensor power...")
    with sensor_lock:
        sensor_power.off()
        time.sleep(2)
        sensor_power.on()
        time.sleep(2)
    return None, None

# ------------------- Gecko Monitoring Functions -------------------
def log_temperature_and_humidity():
    global sensor_data
    while True:
        temp, humidity = read_sensor_data()
        with sensor_lock:
            if temp is not None and humidity is not None:
                sensor_data.update({
                    "temperature": temp,
                    "humidity": humidity,
                    "timestamp": datetime.now().isoformat()
                })
                logger.info(f"Updated sensor data: {sensor_data}")
            else:
                logger.warning("No valid sensor data available. Skipping update.")
        time.sleep(5)

def control_heat_lamp():
    previous_state = None
    while True:
        try:
            with sensor_lock:
                current_temp = sensor_data["temperature"]

            if current_temp is None:
                logger.warning("Temperature data unavailable. Keeping heat lamp in previous state.")
                time.sleep(5)
                continue

            now = datetime.now().hour
            daytime_hours = CONFIG["WINTER_HOURS"] if datetime.now().month in [12, 1, 2] else CONFIG["OTHER_MONTHS_HOURS"]

            if daytime_hours[0] <= now < daytime_hours[1]:
                if current_temp < CONFIG["BASKING_TEMP_MIN"]:
                    new_state = "ON"
                elif current_temp >= CONFIG["BASKING_TEMP_MAX"]:
                    new_state = "OFF"
                else:
                    new_state = previous_state or "OFF"
            else:
                new_state = "ON" if current_temp < CONFIG["NIGHT_TEMP_MAX"] else "OFF"

            if new_state != previous_state:
                logger.info(f"Changing heat lamp state to {new_state}. Current temp: {current_temp:.1f}")
                if new_state == "ON":
                    basking_relay.on()
                else:
                    basking_relay.off()
                previous_state = new_state

        except Exception as e:
            logger.error(f"Error controlling heat lamp: {e}")
        time.sleep(5)

# ------------------- OLED Display Functions -------------------
def update_display():
    while True:
        try:
            with sensor_lock:
                cpu = psutil.cpu_percent(interval=1)
                memory = psutil.virtual_memory()
                ram_used = memory.used / (1024 ** 2)
                ram_total = memory.total / (1024 ** 2)
                disk = psutil.disk_usage("/")
                disk_used = disk.used / (1024 ** 3)
                disk_total = disk.total / (1024 ** 3)

                temp = sensor_data["temperature"]
                humidity = sensor_data["humidity"]

                draw.rectangle((0, 0, width, height), outline=0, fill=0)
                draw.text((0, 0), f"CPU: {cpu:.1f}%", font=font, fill=255)
                draw.text((0, 10), f"RAM: {ram_used:.1f}/{ram_total:.1f} MB", font=font, fill=255)
                draw.text((0, 20), f"Disk: {disk_used:.1f}/{disk_total:.1f} GB", font=font, fill=255)
                if temp is not None and humidity is not None:
                    draw.text((0, 30), f"Temp: {temp}F", font=font, fill=255)
                    draw.text((0, 40), f"Humidity: {humidity}%", font=font, fill=255)
                else:
                    draw.text((0, 30), "Temp: N/A", font=font, fill=255)
                    draw.text((0, 40), "Humidity: N/A", font=font, fill=255)

                disp.display(image)
        except Exception as e:
            logger.error(f"Error updating OLED display: {e}")
        time.sleep(2)

# ------------------- Flask App -------------------
app = Flask(__name__)

@app.route('/sensor_data', methods=['GET'])
def sensor_data_endpoint():
    with sensor_lock:
        return jsonify(sensor_data)

@app.route('/heat_lamp_status', methods=['GET'])
def heat_lamp_status():
    state = "ON" if basking_relay.value else "OFF"
    return jsonify({"heat_lamp_status": state, "timestamp": datetime.now().isoformat()})

# ------------------- Main Code -------------------
if __name__ == '__main__':
    try:
        logger.info("Starting Leopard Gecko monitoring system...")
        Thread(target=log_temperature_and_humidity, daemon=True).start()
        Thread(target=control_heat_lamp, daemon=True).start()
        Thread(target=update_display, daemon=True).start()
        app.run(host='0.0.0.0', port=CONFIG["FLASK_PORT"], threaded=True, debug=False)
    except KeyboardInterrupt:
        logger.info("System shutdown initiated.")
