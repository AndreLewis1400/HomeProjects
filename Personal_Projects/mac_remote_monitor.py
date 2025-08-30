#!/usr/bin/env python3
"""
Mac Remote Monitor for Gecko Detection System
View camera feeds and detection results from Jetson/Pi5 setup
"""

import cv2
import numpy as np
import requests
import json
import time
import threading
import tkinter as tk
from tkinter import ttk, messagebox
from PIL import Image, ImageTk
import os
from datetime import datetime
import logging

class MacRemoteMonitor:
    def __init__(self):
        self.root = tk.Tk()
        self.root.title("Gecko Detection System - Mac Remote Monitor")
        self.root.geometry("1400x900")
        
        # Configuration
        self.config = {
            "jetson_ip": "100.126.96.99",  # Jetson Tailscale IP
            "pi5_ip": "192.168.50.108",    # Pi 5 Local Network IP
            "cync_heat_lamp_ip": "192.168.50.74",  # Cync smart device
            "jetson_port": 5000,
            "jetson_detection_port": 5001,  # Detection streaming port
            "pi5_port": 8080,
            "cameras": [0, 2, 4],
            "update_interval": 100,  # milliseconds
            "detection_data_url": "http://100.126.96.99:5000/detection_data",  # Jetson Detection API
            "heat_lamp_url": "http://100.126.96.99:5000/heat_lamp_status",
            "detection_interface_url": "http://100.126.96.99:5000"  # Jetson Detection web interface
        }
        
        # State variables
        self.running = False
        self.camera_feeds = {}
        self.detection_data = {}
        self.system_status = {}
        
        # Setup logging
        logging.basicConfig(level=logging.INFO)
        self.logger = logging.getLogger(__name__)
        
        # Setup UI
        self.setup_ui()
        
    def setup_ui(self):
        """Setup the user interface"""
        # Main frame
        main_frame = ttk.Frame(self.root, padding="10")
        main_frame.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))
        
        # Configure grid weights
        self.root.columnconfigure(0, weight=1)
        self.root.rowconfigure(0, weight=1)
        main_frame.columnconfigure(1, weight=1)
        main_frame.rowconfigure(1, weight=1)
        
        # Title
        title_label = ttk.Label(main_frame, text="🦎 Gecko Detection System - Remote Monitor", 
                               font=("Arial", 16, "bold"))
        title_label.grid(row=0, column=0, columnspan=3, pady=(0, 10))
        
        # Control panel
        control_frame = ttk.LabelFrame(main_frame, text="Controls", padding="5")
        control_frame.grid(row=1, column=0, sticky=(tk.W, tk.E, tk.N, tk.S), padx=(0, 10))
        
        # Start/Stop button
        self.start_stop_btn = ttk.Button(control_frame, text="Start Monitoring", 
                                        command=self.toggle_monitoring)
        self.start_stop_btn.grid(row=0, column=0, pady=5, sticky=(tk.W, tk.E))
        
        # Status indicators
        status_frame = ttk.LabelFrame(control_frame, text="System Status", padding="5")
        status_frame.grid(row=1, column=0, pady=10, sticky=(tk.W, tk.E))
        
        self.jetson_status = ttk.Label(status_frame, text="Jetson: ❌ Disconnected")
        self.jetson_status.grid(row=0, column=0, sticky=tk.W)
        
        self.pi5_status = ttk.Label(status_frame, text="Pi 5: ❌ Disconnected")
        self.pi5_status.grid(row=1, column=0, sticky=tk.W)
        
        # System info
        info_frame = ttk.LabelFrame(control_frame, text="System Information", padding="5")
        info_frame.grid(row=2, column=0, pady=10, sticky=(tk.W, tk.E))
        
        self.temp_label = ttk.Label(info_frame, text="Temperature: --°F")
        self.temp_label.grid(row=0, column=0, sticky=tk.W)
        
        self.humidity_label = ttk.Label(info_frame, text="Humidity: --%")
        self.humidity_label.grid(row=1, column=0, sticky=tk.W)
        
        self.heat_lamp_label = ttk.Label(info_frame, text="Heat Lamp: --")
        self.heat_lamp_label.grid(row=2, column=0, sticky=tk.W)
        
        # Cync heat lamp control
        cync_frame = ttk.LabelFrame(control_frame, text="Cync Heat Lamp Control", padding="5")
        cync_frame.grid(row=3, column=0, pady=10, sticky=(tk.W, tk.E))
        
        self.cync_status = ttk.Label(cync_frame, text="Cync: ❌ Disconnected")
        self.cync_status.grid(row=0, column=0, sticky=tk.W)
        
        # Heat lamp control buttons
        button_frame = ttk.Frame(cync_frame)
        button_frame.grid(row=1, column=0, pady=5)
        
        self.heat_on_btn = ttk.Button(button_frame, text="Heat ON", 
                                     command=lambda: self.control_heat_lamp("on"))
        self.heat_on_btn.grid(row=0, column=0, padx=5)
        
        self.heat_off_btn = ttk.Button(button_frame, text="Heat OFF", 
                                      command=lambda: self.control_heat_lamp("off"))
        self.heat_off_btn.grid(row=0, column=1, padx=5)
        
        # Camera feeds area
        camera_frame = ttk.LabelFrame(main_frame, text="Camera Feeds", padding="5")
        camera_frame.grid(row=1, column=1, sticky=(tk.W, tk.E, tk.N, tk.S))
        camera_frame.columnconfigure(0, weight=1)
        camera_frame.columnconfigure(1, weight=1)
        camera_frame.columnconfigure(2, weight=1)
        camera_frame.rowconfigure(0, weight=1)
        camera_frame.rowconfigure(1, weight=1)
        
        # Create camera feed labels
        self.camera_labels = {}
        for i, camera_id in enumerate(self.config["cameras"]):
            row = i // 3
            col = i % 3
            
            label = ttk.Label(camera_frame, text=f"Camera {camera_id}\nConnecting...", 
                             relief="solid", borderwidth=2)
            label.grid(row=row, column=col, padx=5, pady=5, sticky=(tk.W, tk.E, tk.N, tk.S))
            self.camera_labels[camera_id] = label
        
        # Detection results area
        detection_frame = ttk.LabelFrame(main_frame, text="Detection Results", padding="5")
        detection_frame.grid(row=2, column=0, columnspan=2, sticky=(tk.W, tk.E), pady=(10, 0))
        
        # Detection interface button
        detection_button_frame = ttk.Frame(detection_frame)
        detection_button_frame.grid(row=0, column=0, pady=5, sticky=(tk.W, tk.E))
        
        self.open_detection_btn = ttk.Button(detection_button_frame, text="🦎 Open Detection Interface", 
                                           command=self.open_detection_interface)
        self.open_detection_btn.grid(row=0, column=0, padx=5)
        
        # Detection text widget
        self.detection_text = tk.Text(detection_frame, height=8, width=80)
        detection_scrollbar = ttk.Scrollbar(detection_frame, orient="vertical", 
                                          command=self.detection_text.yview)
        self.detection_text.configure(yscrollcommand=detection_scrollbar.set)
        
        self.detection_text.grid(row=1, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))
        detection_scrollbar.grid(row=1, column=1, sticky=(tk.N, tk.S))
        
        # Configure detection frame grid weights
        detection_frame.columnconfigure(0, weight=1)
        detection_frame.rowconfigure(0, weight=1)
        
    def toggle_monitoring(self):
        """Toggle monitoring on/off"""
        if not self.running:
            self.start_monitoring()
        else:
            self.stop_monitoring()
    
    def start_monitoring(self):
        """Start monitoring all systems"""
        self.running = True
        self.start_stop_btn.config(text="Stop Monitoring")
        
        # Start monitoring threads
        self.camera_thread = threading.Thread(target=self.monitor_cameras, daemon=True)
        self.camera_thread.start()
        
        self.sensor_thread = threading.Thread(target=self.monitor_sensors, daemon=True)
        self.sensor_thread.start()
        
        # Start Cync monitoring thread
        self.cync_thread = threading.Thread(target=self.monitor_cync, daemon=True)
        self.cync_thread.start()
        
        self.logger.info("Started remote monitoring")
    
    def stop_monitoring(self):
        """Stop monitoring"""
        self.running = False
        self.start_stop_btn.config(text="Start Monitoring")
        self.logger.info("Stopped remote monitoring")
    
    def monitor_cameras(self):
        """Monitor camera feeds from Pi 5"""
        while self.running:
            for camera_id in self.config["cameras"]:
                try:
                    # Try to get camera feed from Pi 5
                    url = f"http://{self.config['pi5_ip']}:{self.config['pi5_port']}/camera{camera_id}"
                    response = requests.get(url, timeout=2)
                    
                    if response.status_code == 200:
                        # Convert response to image
                        nparr = np.frombuffer(response.content, np.uint8)
                        img = cv2.imdecode(nparr, cv2.IMREAD_COLOR)
                        
                        if img is not None:
                            # Resize for display
                            img = cv2.resize(img, (320, 240))
                            img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
                            
                            # Convert to PhotoImage
                            pil_img = Image.fromarray(img)
                            photo = ImageTk.PhotoImage(pil_img)
                            
                            # Update label
                            self.camera_labels[camera_id].configure(image=photo, text="")
                            self.camera_labels[camera_id].image = photo  # Keep reference
                            
                            # Update status
                            self.pi5_status.config(text="Pi 5: ✅ Connected")
                            
                except Exception as e:
                    # Update status to show connection issue
                    self.camera_labels[camera_id].configure(image="", 
                                                          text=f"Camera {camera_id}\nConnection Error")
                    self.pi5_status.config(text="Pi 5: ❌ Connection Error")
                    self.logger.warning(f"Camera {camera_id} connection error: {e}")
            
            time.sleep(1)  # Update every second
    
    def monitor_sensors(self):
        """Monitor sensor data from Jetson"""
        while self.running:
            try:
                # Get sensor data from Jetson
                response = requests.get(self.config["detection_data_url"], timeout=2)
                if response.status_code == 200:
                    sensor_data = response.json()
                    
                    # Update temperature and humidity
                    if sensor_data.get("temperature"):
                        self.temp_label.config(text=f"Temperature: {sensor_data['temperature']}°F")
                    if sensor_data.get("humidity"):
                        self.humidity_label.config(text=f"Humidity: {sensor_data['humidity']}%")
                    
                    # Get heat lamp status
                    heat_response = requests.get(self.config["heat_lamp_url"], timeout=2)
                    if heat_response.status_code == 200:
                        heat_data = heat_response.json()
                        status = "🟢 ON" if heat_data.get("heat_lamp_status") == "ON" else "🔴 OFF"
                        self.heat_lamp_label.config(text=f"Heat Lamp: {status}")
                    
                    # Update Jetson status
                    self.jetson_status.config(text="Jetson: ✅ Connected")
                    
                    # Update detection results
                    self.update_detection_display(sensor_data)
                    
            except Exception as e:
                self.jetson_status.config(text="Jetson: ❌ Connection Error")
                self.logger.warning(f"Jetson connection error: {e}")
            
            time.sleep(2)  # Update every 2 seconds
    
    def monitor_cync(self):
        """Monitor Cync heat lamp status"""
        while self.running:
            self.check_cync_status()
            time.sleep(5)  # Check every 5 seconds
    
    def control_heat_lamp(self, action):
        """Control Cync heat lamp"""
        try:
            cync_ip = self.config["cync_heat_lamp_ip"]
            
            if action == "on":
                # Turn on heat lamp via Cync API
                response = requests.post(f"http://{cync_ip}/api/control", 
                                       json={"device": "heat_lamp", "action": "on"}, 
                                       timeout=5)
                if response.status_code == 200:
                    self.cync_status.config(text="Cync: ✅ Connected - Heat ON")
                    self.logger.info("Heat lamp turned ON")
                else:
                    self.cync_status.config(text="Cync: ⚠️ Error - Check API")
                    
            elif action == "off":
                # Turn off heat lamp via Cync API
                response = requests.post(f"http://{cync_ip}/api/control", 
                                       json={"device": "heat_lamp", "action": "off"}, 
                                       timeout=5)
                if response.status_code == 200:
                    self.cync_status.config(text="Cync: ✅ Connected - Heat OFF")
                    self.logger.info("Heat lamp turned OFF")
                else:
                    self.cync_status.config(text="Cync: ⚠️ Error - Check API")
                    
        except Exception as e:
            self.cync_status.config(text="Cync: ❌ Connection Error")
            self.logger.error(f"Cync control error: {e}")
    
    def check_cync_status(self):
        """Check Cync device status"""
        try:
            cync_ip = self.config["cync_heat_lamp_ip"]
            response = requests.get(f"http://{cync_ip}/api/status", timeout=3)
            
            if response.status_code == 200:
                status_data = response.json()
                if status_data.get("heat_lamp", {}).get("power") == "on":
                    self.cync_status.config(text="Cync: ✅ Connected - Heat ON")
                else:
                    self.cync_status.config(text="Cync: ✅ Connected - Heat OFF")
            else:
                self.cync_status.config(text="Cync: ⚠️ API Error")
                
        except Exception as e:
            self.cync_status.config(text="Cync: ❌ Disconnected")
            self.logger.warning(f"Cync status check error: {e}")
    
    def open_detection_interface(self):
        """Open the detection interface in default browser"""
        try:
            import webbrowser
            detection_url = self.config["detection_interface_url"]
            webbrowser.open(detection_url)
            self.logger.info(f"Opened detection interface: {detection_url}")
            
            # Update detection text
            self.detection_text.insert(tk.END, f"\n[{datetime.now().strftime('%H:%M:%S')}] Opened detection interface\n")
            self.detection_text.see(tk.END)
            
        except Exception as e:
            self.logger.error(f"Failed to open detection interface: {e}")
            self.detection_text.insert(tk.END, f"\n[{datetime.now().strftime('%H:%M:%S')}] Error opening detection interface: {e}\n")
            self.detection_text.see(tk.END)
    
    def update_detection_display(self, sensor_data):
        """Update detection results display"""
        timestamp = datetime.now().strftime("%H:%M:%S")
        
        # Clear previous content
        self.detection_text.delete(1.0, tk.END)
        
        # Add timestamp
        self.detection_text.insert(tk.END, f"[{timestamp}] Detection Results:\n")
        self.detection_text.insert(tk.END, "=" * 50 + "\n")
        
        # Add sensor data
        if sensor_data.get("temperature"):
            self.detection_text.insert(tk.END, f"Temperature: {sensor_data['temperature']}°F\n")
        if sensor_data.get("humidity"):
            self.detection_text.insert(tk.END, f"Humidity: {sensor_data['humidity']}%\n")
        
        # Add detection data if available
        if "detections" in sensor_data:
            self.detection_text.insert(tk.END, "\nDetected Objects:\n")
            for detection in sensor_data["detections"]:
                self.detection_text.insert(tk.END, 
                    f"- {detection['class']}: {detection['confidence']:.3f}\n")
        
        # Auto-scroll to bottom
        self.detection_text.see(tk.END)
    
    def run(self):
        """Run the application"""
        try:
            self.root.mainloop()
        except KeyboardInterrupt:
            self.stop_monitoring()
            self.root.quit()

def main():
    """Main function"""
    app = MacRemoteMonitor()
    app.run()

if __name__ == "__main__":
    main()
