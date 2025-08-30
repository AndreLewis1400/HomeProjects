# 🦎 Complete Gecko Detection System - Manual Deployment Guide

## Overview
This guide will help you manually deploy the enhanced gecko detection system with:
- ✅ Enhanced Pi 5 camera streaming with rotation support
- ✅ Enhanced Jetson detection system with AI
- ✅ Hardware optimization for both devices
- ✅ All features enabled (RGB control, display control, camera rotation)

## Prerequisites
- Pi 5 accessible via SSH (IP: 192.168.50.108)
- Jetson accessible via SSH (IP: 100.126.96.99)
- Mac with Python 3.7+ installed
- Network connectivity to both devices

## Step 1: Deploy Enhanced Pi 5 Camera Streaming

### 1.1 Copy Enhanced Camera Script
```bash
# From your Mac, copy the enhanced camera script
scp pi5_camera_stream_enhanced.py algopree@192.168.50.108:~/pi5_camera_stream.py
```

### 1.2 SSH to Pi 5 and Install Dependencies
```bash
ssh algopree@192.168.50.108
```

Once connected to Pi 5, run:
```bash
# Update system
sudo apt update

# Install system packages
sudo apt install -y python3-pip python3-opencv python3-flask python3-numpy
sudo apt install -y libatlas-base-dev libhdf5-dev libhdf5-serial-dev libjasper-dev

# Create virtual environment
python3 -m venv gecko_env
source gecko_env/bin/activate

# Install Python packages
pip install flask opencv-python numpy requests

# Set up camera permissions
sudo usermod -a -G video $USER
```

### 1.3 Create System Service
```bash
# Create the service file
sudo tee /etc/systemd/system/gecko-camera.service > /dev/null << 'EOF'
[Unit]
Description=Gecko Detection Camera Streaming
After=network.target

[Service]
Type=simple
User=algopree
WorkingDirectory=/home/algopree
Environment=PATH=/home/algopree/gecko_env/bin
ExecStart=/home/algopree/gecko_env/bin/python3 /home/algopree/pi5_camera_stream.py
Restart=always
RestartSec=10

[Install]
WantedBy=multi-user.target
EOF

# Enable and start service
sudo systemctl daemon-reload
sudo systemctl enable gecko-camera.service
sudo systemctl start gecko-camera.service

# Check status
sudo systemctl status gecko-camera.service
```

### 1.4 Test Pi 5 Camera Streaming
```bash
# Test the web interface
curl http://192.168.50.108:8080

# Test camera streams
curl http://192.168.50.108:8080/camera0
curl http://192.168.50.108:8080/camera2
curl http://192.168.50.108:8080/camera4

# Test status API
curl http://192.168.50.108:8080/status
```

## Step 2: Deploy Enhanced Jetson Detection System

### 2.1 Copy Enhanced Detection Script
```bash
# From your Mac, copy the enhanced detection script
scp jetson_detection_system_enhanced.py algopree@100.126.96.99:~/jetson_detection_system.py
```

### 2.2 SSH to Jetson and Install Dependencies
```bash
ssh algopree@100.126.96.99
```

Once connected to Jetson, run:
```bash
# Update system
sudo apt update

# Install system packages
sudo apt install -y python3-pip python3-opencv python3-flask python3-numpy

# Create virtual environment
python3 -m venv gecko_env
source gecko_env/bin/activate

# Install PyTorch (Jetson optimized)
pip install torch torchvision torchaudio --index-url https://download.pytorch.org/whl/cu118

# Install YOLO and other packages
pip install ultralytics flask opencv-python numpy requests
```

### 2.3 Create System Service
```bash
# Create the service file
sudo tee /etc/systemd/system/gecko-detection.service > /dev/null << 'EOF'
[Unit]
Description=Gecko Detection AI System
After=network.target

[Service]
Type=simple
User=algopree
WorkingDirectory=/home/algopree
Environment=PATH=/home/algopree/gecko_env/bin
Environment=CUDA_VISIBLE_DEVICES=0
ExecStart=/home/algopree/gecko_env/bin/python3 /home/algopree/jetson_detection_system.py
Restart=always
RestartSec=10

[Install]
WantedBy=multi-user.target
EOF

# Enable and start service
sudo systemctl daemon-reload
sudo systemctl enable gecko-detection.service
sudo systemctl start gecko-detection.service

# Check status
sudo systemctl status gecko-detection.service
```

### 2.4 Test Jetson Detection System
```bash
# Test the web interface
curl http://100.126.96.99:5000

# Test detection streams
curl http://100.126.96.99:5000/detection0
curl http://100.126.96.99:5000/detection2
curl http://100.126.96.99:5000/detection4

# Test APIs
curl http://100.126.96.99:5000/detection_data
curl http://100.126.96.99:5000/sensor_data
curl http://100.126.96.99:5000/heat_lamp_status
```

## Step 3: Hardware Optimization

### 3.1 Optimize Pi 5
SSH to Pi 5 and run:
```bash
# Set CPU governor to performance
echo performance | sudo tee /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor

# Increase GPU memory
echo "gpu_mem=256" | sudo tee -a /boot/config.txt

# Optimize network settings
echo "net.core.rmem_max=134217728" | sudo tee -a /etc/sysctl.conf
echo "net.core.wmem_max=134217728" | sudo tee -a /etc/sysctl.conf
echo "net.ipv4.tcp_rmem=4096 87380 134217728" | sudo tee -a /etc/sysctl.conf
echo "net.ipv4.tcp_wmem=4096 65536 134217728" | sudo tee -a /etc/sysctl.conf

# Apply settings
sudo sysctl -p

# Optimize camera settings (if camera is connected)
sudo v4l2-ctl --set-fmt-video=width=640,height=480,pixelformat=YUYV
sudo v4l2-ctl --set-ctrl=exposure_auto=1
sudo v4l2-ctl --set-ctrl=exposure_absolute=100

echo "✅ Pi 5 optimization complete"
```

### 3.2 Optimize Jetson
SSH to Jetson and run:
```bash
# Set performance mode
sudo nvpmodel -m 0
sudo jetson_clocks

# Optimize GPU memory
echo "gpu_mem=2048" | sudo tee -a /boot/extlinux/extlinux.conf

# Set environment variables
echo "export CUDA_VISIBLE_DEVICES=0" >> ~/.bashrc
echo "export TF_FORCE_GPU_ALLOW_GROWTH=true" >> ~/.bashrc
echo "export OPENCV_VIDEOIO_PRIORITY_MSMF=0" >> ~/.bashrc

# Optimize system settings
echo "vm.swappiness=10" | sudo tee -a /etc/sysctl.conf
echo "vm.vfs_cache_pressure=50" | sudo tee -a /etc/sysctl.conf

# Apply settings
sudo sysctl -p

echo "✅ Jetson optimization complete"
```

## Step 4: Test the Complete System

### 4.1 Run System Test
From your Mac, run the comprehensive test:
```bash
python3 test_system.py
```

### 4.2 Manual Testing
Test each component manually:

**Pi 5 Camera Streaming:**
- Open: http://192.168.50.108:8080
- Test camera rotation buttons
- Test RGB light controls
- Test display controls

**Jetson Detection System:**
- Open: http://100.126.96.99:5000
- Verify detection streams are working
- Check detection data API
- Test sensor data

**Mac Remote Monitor:**
```bash
python3 mac_remote_monitor.py
```

## Step 5: Troubleshooting

### 5.1 Common Issues

**Pi 5 Camera Issues:**
```bash
# Check camera service status
sudo systemctl status gecko-camera.service

# View logs
sudo journalctl -u gecko-camera.service -f

# Restart service
sudo systemctl restart gecko-camera.service

# Check camera permissions
ls -la /dev/video*
sudo usermod -a -G video $USER
```

**Jetson Detection Issues:**
```bash
# Check detection service status
sudo systemctl status gecko-detection.service

# View logs
sudo journalctl -u gecko-detection.service -f

# Restart service
sudo systemctl restart gecko-detection.service

# Check GPU status
nvidia-smi
```

**Network Issues:**
```bash
# Test connectivity
ping 192.168.50.108
ping 100.126.96.99

# Check ports
nmap -p 8080 192.168.50.108
nmap -p 5000 100.126.96.99
```

### 5.2 Service Management

**Pi 5 Services:**
```bash
# Start camera service
sudo systemctl start gecko-camera.service

# Stop camera service
sudo systemctl stop gecko-camera.service

# Enable auto-start
sudo systemctl enable gecko-camera.service

# Disable auto-start
sudo systemctl disable gecko-camera.service
```

**Jetson Services:**
```bash
# Start detection service
sudo systemctl start gecko-detection.service

# Stop detection service
sudo systemctl stop gecko-detection.service

# Enable auto-start
sudo systemctl enable gecko-detection.service

# Disable auto-start
sudo systemctl disable gecko-detection.service
```

## Step 6: Access URLs

### 6.1 Pi 5 Camera Streaming
- **Main Interface:** http://192.168.50.108:8080
- **Camera 0:** http://192.168.50.108:8080/camera0
- **Camera 2:** http://192.168.50.108:8080/camera2
- **Camera 4:** http://192.168.50.108:8080/camera4
- **Status API:** http://192.168.50.108:8080/status
- **RGB Control:** http://192.168.50.108:8080/rgb/<mode>
- **Display Control:** http://192.168.50.108:8080/display/<screen>
- **Camera Rotation:** http://192.168.50.108:8080/camera/<index>/rotate/<angle>

### 6.2 Jetson Detection System
- **Main Interface:** http://100.126.96.99:5000
- **Detection 0:** http://100.126.96.99:5000/detection0
- **Detection 2:** http://100.126.96.99:5000/detection2
- **Detection 4:** http://100.126.96.99:5000/detection4
- **Detection Data:** http://100.126.96.99:5000/detection_data
- **Sensor Data:** http://100.126.96.99:5000/sensor_data
- **Heat Lamp Status:** http://100.126.96.99:5000/heat_lamp_status

### 6.3 Mac Remote Monitor
```bash
python3 mac_remote_monitor.py
```

## Step 7: Features Overview

### 7.1 Camera Features
- ✅ **Camera Rotation:** 0°, 90°, 180°, 270° for each camera
- ✅ **Stable Streaming:** Robust error handling and recovery
- ✅ **Multiple Cameras:** Support for cameras 0, 2, and 4
- ✅ **Test Patterns:** Fallback when cameras unavailable

### 7.2 RGB Light Control
- ✅ **Gecko Mode:** Green lighting for gecko habitat
- ✅ **Rainbow Mode:** Color cycling effects
- ✅ **Individual Colors:** Blue, green, red, purple, orange
- ✅ **Off Mode:** Complete shutdown

### 7.3 Display Control
- ✅ **System Screen:** System status and information
- ✅ **Cameras Screen:** Camera feed display
- ✅ **Gecko Screen:** Gecko-specific information
- ✅ **Status Screen:** Real-time status updates
- ✅ **Temperature Screen:** Temperature monitoring
- ✅ **Humidity Screen:** Humidity monitoring

### 7.4 Detection Features
- ✅ **AI Model Support:** YOLOv8n with CUDA acceleration
- ✅ **Fallback Detection:** Simulated detection when AI unavailable
- ✅ **Bounding Boxes:** Visual detection overlays
- ✅ **Confidence Scores:** Detection confidence display
- ✅ **Multiple Classes:** Gecko, water dish, hiding spots

### 7.5 System Features
- ✅ **Hardware Optimization:** Performance tuning for both devices
- ✅ **Service Management:** Automatic startup and recovery
- ✅ **Error Handling:** Robust error recovery
- ✅ **Real-time Monitoring:** Live status updates
- ✅ **Network Integration:** Seamless device communication

## Success Indicators

✅ **System is fully deployed when:**
1. Pi 5 camera streaming is accessible at http://192.168.50.108:8080
2. Jetson detection system is accessible at http://100.126.96.99:5000
3. Camera rotation controls work for all cameras
4. RGB light controls respond to commands
5. Detection system shows bounding boxes
6. Mac remote monitor connects to both systems
7. All services start automatically on boot

🎉 **Congratulations! Your enhanced gecko detection system is now fully operational!**
