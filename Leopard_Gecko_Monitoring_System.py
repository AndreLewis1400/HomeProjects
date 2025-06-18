from contextlib import contextmanager
import atexit
import logging
import csv
import os
import time
from threading import Thread, Lock
from datetime import datetime
from flask import Flask, jsonify
from gpiozero import OutputDevice, MotionSensor
from smbus2 import SMBus

# ------------------- Configuration -------------------
TEMP_SENSOR_ADDRESS = 0x44
I2C_BUS = 1
RELAY_BASKING_PIN = 27
SENSOR_RESET_PIN = 22
MOTION_SENSOR_PIN = 24
BASKING_TEMP_MIN = 88.0
BASKING_TEMP_MAX = 92.0
NIGHT_TEMP_MAX = 75.0
WINTER_HOURS = (7, 19)
OTHER_MONTHS_HOURS = (7, 21)
FLASH_DRIVE_PATH = "/media/algopree/6DE9-C26F"
SYSTEM_LOG_FILE = os.path.join(FLASH_DRIVE_PATH, "system_logs.log")
TEMP_HUMIDITY_LOG_FILE = os.path.join(FLASH_DRIVE_PATH, "temp_humidity_data.csv")

# Initialize hardware
basking_relay = OutputDevice(RELAY_BASKING_PIN)
sensor_power = OutputDevice(SENSOR_RESET_PIN)
motion_sensor = MotionSensor(MOTION_SENSOR_PIN)
bus = SMBus(I2C_BUS)

sensor_data = {"temperature": None, "humidity": None, "timestamp": None}
sensor_lock = Lock()

# ------------------- Logger Setup -------------------
def setup_logger(log_file):
    logger = logging.getLogger("LeopardGecko")
    logger.setLevel(logging.INFO)
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
    basking_relay.close()
    sensor_power.close()
    motion_sensor.close()
    bus.close()
    logger.info("Resources cleaned up successfully.")

# ------------------- I2C Reset -------------------------
def robust_i2c_reset():
    """Attempt a robust recovery of the I2C interface."""
    try:
        logger.info("Performing I2C bus recovery...")
        sensor_power.off()
        time.sleep(2)  # Power down the sensor
        os.system("i2cdetect -y 1")  # Check I2C bus status
        sensor_power.on()
        time.sleep(2)  # Power up the sensor
        with safe_i2c_communication() as bus:
            bus.write_i2c_block_data(TEMP_SENSOR_ADDRESS, 0x2C, [0x06])  # Reinitialize sensor
        logger.info("I2C bus recovery successful.")
        return True
    except Exception as e:
        logger.error(f"I2C recovery failed: {e}")
        return False

# -------------------- Periodic Health Checks --------------------------
def periodic_health_check():
    """Perform periodic health checks on the I2C bus."""
    while True:
        try:
            with safe_i2c_communication() as bus:
                bus.write_i2c_block_data(TEMP_SENSOR_ADDRESS, 0x2C, [0x06])
                time.sleep(0.5)
                logger.info("I2C health check passed.")
        except Exception as e:
            logger.warning(f"I2C health check failed: {e}")
        time.sleep(600)  # Check every 10 minutes

# ------------------- Core Functions -------------------
@contextmanager
def safe_i2c_communication():
    try:
        yield bus
    except Exception as e:
        logger.error(f"I2C error: {e}")

def read_sensor_data():
    """Read temperature and humidity from the sensor with recovery logic."""
    for attempt in range(3):  # Retry up to 3 times
        try:
            with safe_i2c_communication() as bus:
                bus.write_i2c_block_data(TEMP_SENSOR_ADDRESS, 0x2C, [0x06])
                time.sleep(0.5)
                data = bus.read_i2c_block_data(TEMP_SENSOR_ADDRESS, 0x00, 6)
                temp_raw = (data[0] << 8) | data[1]
                humidity_raw = (data[3] << 8) | data[4]
                temp_c = -45 + (175 * temp_raw / 65535.0)
                temp_f = temp_c * 9 / 5 + 32
                humidity = 100 * humidity_raw / 65535.0
                return round(temp_f, 1), round(humidity, 1)
        except Exception as e:
            logger.error(f"I2C error on attempt {attempt + 1}/3: {e}")
            time.sleep(2)  # Short delay before retry
    logger.warning("All I2C read attempts failed. Attempting recovery...")
    if robust_i2c_reset():
        return read_sensor_data()  # Retry after recovery
    else:
        return None, None  # Return None if recovery fails

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

def get_current_daytime_hours():
    return WINTER_HOURS if datetime.now().month in [12, 1, 2] else OTHER_MONTHS_HOURS

def control_heat_lamp():
    """Controls the heat lamp based on temperature and time."""
    previous_state = None
    while True:
        try:
            with sensor_lock:
                current_temp = sensor_data["temperature"]

            if current_temp is not None:
                now = datetime.now().hour
                daytime_hours = get_current_daytime_hours()

                if daytime_hours[0] <= now < daytime_hours[1]:
                    if current_temp < BASKING_TEMP_MIN:
                        new_state = "ON"
                    elif current_temp >= BASKING_TEMP_MAX:
                        new_state = "OFF"
                    else:
                        new_state = previous_state or "OFF"
                else:
                    new_state = "ON" if current_temp < NIGHT_TEMP_MAX else "OFF"

                if new_state != previous_state:
                    logger.info(f"Heat Lamp {new_state}: Temp {current_temp:.1f}F")
                    if new_state == "ON":
                        basking_relay.on()
                    else:
                        basking_relay.off()
                    previous_state = new_state

        except Exception as e:
            logger.error(f"Error controlling heat lamp: {e}")
        time.sleep(5)

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
        Thread(target=periodic_health_check, daemon=True).start()
        Thread(target=control_heat_lamp, daemon=True).start()
        app.run(host='0.0.0.0', port=5000, threaded=True, debug=False)
    except KeyboardInterrupt:
        logger.info("System shutdown initiated.")
