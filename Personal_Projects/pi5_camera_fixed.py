#!/usr/bin/env python3
"""
Fixed Pi 5 Camera Streaming System
Proper device mapping and Camera 4 rotation fix
"""

import cv2
from flask import Flask, Response, jsonify
import time
import threading
import numpy as np
import logging

app = Flask(__name__)

# Configure logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

# Fixed camera configuration with proper device mapping
CAMERAS = {
    0: {"name": "Main Habitat", "device": 0, "rotation": 0, "flip": False},
    2: {"name": "Secondary View", "device": 2, "rotation": 180, "flip": True},
    4: {"name": "Wide Angle", "device": 4, "rotation": 90, "flip": False}  # Fixed: 90° rotation
}

# Thread-safe frame buffers for each camera
frame_buffers = {}
camera_threads = {}
camera_locks = {}
camera_states = {}

# RGB and display state
rgb_state = {"mode": "off", "color": (0, 0, 0)}
display_state = {"screen": "system", "brightness": 100}

def get_camera_device(camera_index):
    """Find the actual camera device for a given camera index"""
    config = CAMERAS.get(camera_index, {})
    device = config.get("device", camera_index)
    
    # Try the exact device first, then alternatives
    for dev in [device, device + 1, device - 1]:
        if dev < 0:
            continue
        try:
            cap = cv2.VideoCapture(dev)
            if cap.isOpened():
                logger.info(f"✅ Camera {camera_index} connected on device {dev}")
                # Set camera properties
                cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
                cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)
                cap.set(cv2.CAP_PROP_FPS, 15)  # Lower FPS for stability
                cap.set(cv2.CAP_PROP_BUFFERSIZE, 1)  # Minimize buffer
                return cap, dev
            else:
                cap.release()
        except Exception as e:
            logger.warning(f"Failed to open camera {camera_index} on device {dev}: {e}")
            continue
    
    logger.warning(f"❌ No camera found for index {camera_index}")
    return None, None

def apply_rotation_and_flip(frame, camera_index):
    """Apply rotation and flip based on camera configuration"""
    config = CAMERAS.get(camera_index, {"rotation": 0, "flip": False})
    
    if frame is None:
        return None
    
    # Apply flip if needed
    if config["flip"]:
        frame = cv2.flip(frame, 1)  # Horizontal flip
    
    # Apply rotation
    if config["rotation"] == 90:
        frame = cv2.rotate(frame, cv2.ROTATE_90_CLOCKWISE)
    elif config["rotation"] == 180:
        frame = cv2.rotate(frame, cv2.ROTATE_180)
    elif config["rotation"] == 270:
        frame = cv2.rotate(frame, cv2.ROTATE_90_COUNTERCLOCKWISE)
    
    return frame

def create_test_pattern(camera_index):
    """Create a test pattern for specific camera"""
    frame = np.zeros((480, 640, 3), dtype=np.uint8)
    config = CAMERAS.get(camera_index, {"name": f"Camera {camera_index}"})
    
    # Add colored rectangles
    cv2.rectangle(frame, (100, 100), (300, 200), (0, 255, 0), 2)  # Green
    cv2.rectangle(frame, (350, 150), (550, 250), (255, 0, 0), 2)  # Blue
    cv2.rectangle(frame, (200, 300), (400, 400), (0, 0, 255), 2)  # Red
    
    # Add text
    cv2.putText(frame, f"{config['name']} - Test Pattern", (150, 50),
               cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 255), 2)
    cv2.putText(frame, "Camera not connected", (200, 250),
               cv2.FONT_HERSHEY_SIMPLEX, 0.7, (255, 255, 255), 2)
    cv2.putText(frame, f"Device: {config.get('device', 'unknown')}", (200, 280),
               cv2.FONT_HERSHEY_SIMPLEX, 0.7, (255, 255, 255), 2)
    cv2.putText(frame, f"Rotation: {config.get('rotation', 0)}°", (200, 310),
               cv2.FONT_HERSHEY_SIMPLEX, 0.7, (255, 255, 255), 2)
    
    return frame

def camera_capture_thread(camera_index):
    """Dedicated thread for capturing frames from a specific camera"""
    logger.info(f"🎬 Starting capture thread for camera {camera_index}")
    
    # Initialize camera
    cap, device = get_camera_device(camera_index)
    camera_states[camera_index] = {"connected": cap is not None, "device": device}
    
    if cap is None:
        logger.warning(f"❌ Camera {camera_index} not available, using test pattern")
        camera_states[camera_index]["connected"] = False
    
    frame_count = 0
    last_frame_time = time.time()
    
    while camera_states[camera_index].get("running", True):
        try:
            if cap is not None and cap.isOpened():
                # Read frame from camera
                ret, frame = cap.read()
                if ret and frame is not None:
                    # Apply rotation and flip
                    frame = apply_rotation_and_flip(frame, camera_index)
                    
                    # Add timestamp and status
                    timestamp = time.strftime("%Y-%m-%d %H:%M:%S")
                    config = CAMERAS.get(camera_index, {"name": f"Camera {camera_index}"})
                    
                    cv2.putText(frame, f"{config['name']} - {timestamp}", (10, 30),
                               cv2.FONT_HERSHEY_SIMPLEX, 0.7, (255, 255, 255), 2)
                    cv2.putText(frame, f"Device: {device}", (10, 60),
                               cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2)
                    cv2.putText(frame, f"Rotation: {config.get('rotation', 0)}°", (10, 90),
                               cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2)
                    cv2.putText(frame, "Status: LIVE", (10, 120),
                               cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2)
                    
                    # Store frame in buffer
                    with camera_locks[camera_index]:
                        frame_buffers[camera_index] = frame.copy()
                    
                    frame_count += 1
                    last_frame_time = time.time()
                else:
                    logger.warning(f"❌ Failed to read from camera {camera_index}")
                    # Use test pattern as fallback
                    frame = create_test_pattern(camera_index)
                    with camera_locks[camera_index]:
                        frame_buffers[camera_index] = frame
            else:
                # Use test pattern if no camera
                frame = create_test_pattern(camera_index)
                with camera_locks[camera_index]:
                    frame_buffers[camera_index] = frame
            
            # Control frame rate (15 FPS max per camera)
            time.sleep(0.067)  # ~15 FPS
            
        except Exception as e:
            logger.error(f"❌ Camera {camera_index} thread error: {e}")
            # Use test pattern on error
            frame = create_test_pattern(camera_index)
            with camera_locks[camera_index]:
                frame_buffers[camera_index] = frame
            time.sleep(1)  # Wait before retrying
    
    # Cleanup
    if cap is not None:
        cap.release()
    logger.info(f"🎬 Camera {camera_index} thread stopped")

def start_camera_threads():
    """Start capture threads for all cameras"""
    for camera_index in CAMERAS.keys():
        # Initialize thread-safe structures
        frame_buffers[camera_index] = create_test_pattern(camera_index)
        camera_locks[camera_index] = threading.Lock()
        camera_states[camera_index] = {"running": True, "connected": False}
        
        # Start capture thread
        thread = threading.Thread(target=camera_capture_thread, args=(camera_index,), daemon=True)
        thread.start()
        camera_threads[camera_index] = thread
        
        logger.info(f"🚀 Started thread for camera {camera_index}")
    
    # Wait a moment for threads to initialize
    time.sleep(2)

def get_latest_frame(camera_index):
    """Get the latest frame from a camera's buffer"""
    with camera_locks[camera_index]:
        if camera_index in frame_buffers:
            return frame_buffers[camera_index].copy()
        else:
            return create_test_pattern(camera_index)

def camera_stream(camera_index):
    """Stream camera feed with proper threading"""
    logger.info(f"📹 Starting stream for camera {camera_index}")
    
    while True:
        try:
            # Get latest frame from buffer
            frame = get_latest_frame(camera_index)
            
            if frame is not None:
                # Encode frame
                ret, buffer = cv2.imencode('.jpg', frame, [cv2.IMWRITE_JPEG_QUALITY, 80])
                if ret:
                    frame_data = buffer.tobytes()
                    yield (b'--frame\r\n'
                           b'Content-Type: image/jpeg\r\n\r\n' + frame_data + b'\r\n')
            
            # Control stream rate
            time.sleep(0.1)  # 10 FPS for streaming
            
        except Exception as e:
            logger.error(f"❌ Camera {camera_index} stream error: {e}")
            time.sleep(1)

@app.route('/camera0')
def video_feed_0():
    """Video streaming route for camera 0"""
    return Response(camera_stream(0),
                    mimetype='multipart/x-mixed-replace; boundary=frame')

@app.route('/camera2')
def video_feed_2():
    """Video streaming route for camera 2"""
    return Response(camera_stream(2),
                    mimetype='multipart/x-mixed-replace; boundary=frame')

@app.route('/camera4')
def video_feed_4():
    """Video streaming route for camera 4"""
    return Response(camera_stream(4),
                    mimetype='multipart/x-mixed-replace; boundary=frame')

@app.route('/status')
def status():
    """System status endpoint"""
    camera_status = {}
    for camera_index in CAMERAS.keys():
        state = camera_states.get(camera_index, {})
        camera_status[str(camera_index)] = {
            "status": "active" if state.get("connected", False) else "test_pattern",
            "device": state.get("device", "unknown"),
            "name": CAMERAS[camera_index]["name"],
            "rotation": CAMERAS[camera_index]["rotation"]
        }
    
    return jsonify({
        "system": "online",
        "cameras": camera_status,
        "rgb_lights": rgb_state,
        "display": display_state,
        "threading": "enabled",
        "timestamp": time.time()
    })

@app.route('/rgb/<mode>')
def rgb_control(mode):
    """RGB LED control endpoint"""
    global rgb_state
    
    if mode in ["gecko", "off", "rainbow", "blue", "green", "red", "purple", "orange"]:
        rgb_state["mode"] = mode
        
        # Set color based on mode
        if mode == "gecko":
            rgb_state["color"] = (0, 255, 0)  # Green
        elif mode == "rainbow":
            rgb_state["color"] = (255, 0, 255)  # Magenta
        elif mode == "blue":
            rgb_state["color"] = (255, 0, 0)
        elif mode == "green":
            rgb_state["color"] = (0, 255, 0)
        elif mode == "red":
            rgb_state["color"] = (0, 0, 255)
        elif mode == "purple":
            rgb_state["color"] = (128, 0, 128)
        elif mode == "orange":
            rgb_state["color"] = (0, 165, 255)
        else:  # off
            rgb_state["color"] = (0, 0, 0)
        
        return jsonify({
            "status": "success",
            "mode": mode,
            "color": rgb_state["color"],
            "message": f"RGB lights set to {mode} mode"
        })
    else:
        return jsonify({
            "status": "error",
            "message": f"Unknown mode: {mode}"
        }), 400

@app.route('/display/<screen>')
def display_control(screen):
    """Display control endpoint"""
    global display_state
    
    if screen in ["system", "cameras", "gecko", "status", "temperature", "humidity"]:
        display_state["screen"] = screen
        return jsonify({
            "status": "success",
            "screen": screen,
            "message": f"Display set to {screen} screen"
        })
    else:
        return jsonify({
            "status": "error",
            "message": f"Unknown screen: {screen}"
        }), 400

@app.route('/camera/<int:camera_index>/rotate/<int:angle>')
def rotate_camera(camera_index, angle):
    """Rotate specific camera"""
    if camera_index in CAMERAS and angle in [0, 90, 180, 270]:
        CAMERAS[camera_index]["rotation"] = angle
        return jsonify({
            "status": "success",
            "camera": camera_index,
            "rotation": angle,
            "message": f"Camera {camera_index} rotated to {angle}°"
        })
    else:
        return jsonify({
            "status": "error",
            "message": f"Invalid camera index or angle"
        }), 400

@app.route('/')
def index():
    """Main page with fixed camera interface"""
    return '''
    <!DOCTYPE html>
    <html>
    <head>
        <title>Pi 5 Fixed Camera Streaming</title>
        <style>
            body { 
                font-family: Arial, sans-serif; 
                margin: 20px; 
                background: #1a1a1a; 
                color: white; 
            }
            .header { 
                text-align: center; 
                margin-bottom: 20px; 
                background: linear-gradient(45deg, #2c3e50, #3498db);
                padding: 20px;
                border-radius: 10px;
            }
            .camera-grid { 
                display: grid; 
                grid-template-columns: repeat(auto-fit, minmax(400px, 1fr)); 
                gap: 20px; 
                margin-bottom: 20px;
            }
            .camera-feed { 
                border: 2px solid #333; 
                border-radius: 10px; 
                padding: 10px; 
                background: #2a2a2a;
            }
            .camera-title { 
                text-align: center; 
                margin-bottom: 10px; 
                font-size: 18px; 
                font-weight: bold;
                color: #3498db;
            }
            .camera-image { 
                width: 100%; 
                height: auto; 
                border-radius: 5px; 
            }
            .status { 
                text-align: center; 
                margin: 20px 0; 
                padding: 15px; 
                background: #333; 
                border-radius: 10px;
                border-left: 5px solid #27ae60;
            }
            .controls {
                display: grid;
                grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
                gap: 15px;
                margin: 20px 0;
            }
            .control-panel {
                background: #2a2a2a;
                padding: 15px;
                border-radius: 10px;
                border: 1px solid #444;
            }
            .control-panel h3 {
                margin-top: 0;
                color: #3498db;
            }
            .btn {
                background: #3498db;
                color: white;
                border: none;
                padding: 8px 15px;
                margin: 2px;
                border-radius: 5px;
                cursor: pointer;
                transition: background 0.3s;
            }
            .btn:hover {
                background: #2980b9;
            }
            .btn.active {
                background: #27ae60;
            }
            .rotation-controls {
                display: flex;
                gap: 5px;
                margin-top: 10px;
            }
        </style>
    </head>
    <body>
        <div class="header">
            <h1>🦎 Pi 5 Fixed Camera Streaming</h1>
            <p>Gecko Detection System - Device Mapping & Rotation Fixed</p>
        </div>

        <div class="status">
            <h3>📊 System Status</h3>
            <p>Camera 0: <span id="cam0-status" style="color: #f39c12;">Checking...</span> |
               Camera 2: <span id="cam2-status" style="color: #27ae60;">✅ Active</span> |
               Camera 4: <span id="cam4-status" style="color: #27ae60;">✅ 90° Rotated</span> |
               Threading: <span style="color: #27ae60;">✅ Enabled</span></p>
        </div>

        <div class="controls">
            <div class="control-panel">
                <h3>🎨 RGB Light Control</h3>
                <button class="btn" onclick="setRGB('gecko')">Gecko Mode</button>
                <button class="btn" onclick="setRGB('rainbow')">Rainbow</button>
                <button class="btn" onclick="setRGB('blue')">Blue</button>
                <button class="btn" onclick="setRGB('green')">Green</button>
                <button class="btn" onclick="setRGB('red')">Red</button>
                <button class="btn" onclick="setRGB('purple')">Purple</button>
                <button class="btn" onclick="setRGB('orange')">Orange</button>
                <button class="btn" onclick="setRGB('off')">Off</button>
            </div>
            
            <div class="control-panel">
                <h3>📺 Display Control</h3>
                <button class="btn" onclick="setDisplay('system')">System</button>
                <button class="btn" onclick="setDisplay('cameras')">Cameras</button>
                <button class="btn" onclick="setDisplay('gecko')">Gecko</button>
                <button class="btn" onclick="setDisplay('status')">Status</button>
                <button class="btn" onclick="setDisplay('temperature')">Temperature</button>
                <button class="btn" onclick="setDisplay('humidity')">Humidity</button>
            </div>
        </div>

        <div class="camera-grid">
            <div class="camera-feed">
                <div class="camera-title">📹 Main Habitat (Camera 0) - Device 0</div>
                <img src="/camera0" class="camera-image" alt="Camera 0">
                <div class="rotation-controls">
                    <button class="btn" onclick="rotateCamera(0, 0)">0°</button>
                    <button class="btn" onclick="rotateCamera(0, 90)">90°</button>
                    <button class="btn" onclick="rotateCamera(0, 180)">180°</button>
                    <button class="btn" onclick="rotateCamera(0, 270)">270°</button>
                </div>
            </div>

            <div class="camera-feed">
                <div class="camera-title">📹 Secondary View (Camera 2) - Device 2</div>
                <img src="/camera2" class="camera-image" alt="Camera 2">
                <div class="rotation-controls">
                    <button class="btn" onclick="rotateCamera(2, 0)">0°</button>
                    <button class="btn" onclick="rotateCamera(2, 90)">90°</button>
                    <button class="btn" onclick="rotateCamera(2, 180)">180°</button>
                    <button class="btn" onclick="rotateCamera(2, 270)">270°</button>
                </div>
            </div>

            <div class="camera-feed">
                <div class="camera-title">📹 Wide Angle (Camera 4) - Device 4 - 90° Rotated</div>
                <img src="/camera4" class="camera-image" alt="Camera 4">
                <div class="rotation-controls">
                    <button class="btn" onclick="rotateCamera(4, 0)">0°</button>
                    <button class="btn active" onclick="rotateCamera(4, 90)">90°</button>
                    <button class="btn" onclick="rotateCamera(4, 180)">180°</button>
                    <button class="btn" onclick="rotateCamera(4, 270)">270°</button>
                </div>
            </div>
        </div>

        <script>
            // Auto-refresh images every 5 seconds
            setInterval(function() {
                const images = document.querySelectorAll('.camera-image');
                images.forEach(img => {
                    img.src = img.src + '?t=' + new Date().getTime();
                });
            }, 5000);

            // Update camera status
            function updateCameraStatus() {
                fetch('/status')
                    .then(response => response.json())
                    .then(data => {
                        const cameras = data.cameras;
                        
                        // Update status indicators
                        document.getElementById('cam0-status').textContent = 
                            cameras['0'].status === 'active' ? '✅ Active' : '❌ Test Pattern';
                        document.getElementById('cam0-status').style.color = 
                            cameras['0'].status === 'active' ? '#27ae60' : '#e74c3c';
                        
                        document.getElementById('cam2-status').textContent = 
                            cameras['2'].status === 'active' ? '✅ Active' : '❌ Test Pattern';
                        document.getElementById('cam2-status').style.color = 
                            cameras['2'].status === 'active' ? '#27ae60' : '#e74c3c';
                        
                        document.getElementById('cam4-status').textContent = 
                            cameras['4'].status === 'active' ? '✅ 90° Rotated' : '❌ Test Pattern';
                        document.getElementById('cam4-status').style.color = 
                            cameras['4'].status === 'active' ? '#27ae60' : '#e74c3c';
                    })
                    .catch(error => console.error('Status update error:', error));
            }

            // Update status every 3 seconds
            setInterval(updateCameraStatus, 3000);
            updateCameraStatus(); // Initial load

            // RGB Control
            function setRGB(mode) {
                fetch(`/rgb/${mode}`)
                    .then(response => response.json())
                    .then(data => {
                        console.log('RGB set:', data);
                        // Update button states
                        document.querySelectorAll('[onclick^="setRGB"]').forEach(btn => {
                            btn.classList.remove('active');
                        });
                        event.target.classList.add('active');
                    })
                    .catch(error => console.error('RGB Error:', error));
            }

            // Display Control
            function setDisplay(screen) {
                fetch(`/display/${screen}`)
                    .then(response => response.json())
                    .then(data => {
                        console.log('Display set:', data);
                        // Update button states
                        document.querySelectorAll('[onclick^="setDisplay"]').forEach(btn => {
                            btn.classList.remove('active');
                        });
                        event.target.classList.add('active');
                    })
                    .catch(error => console.error('Display Error:', error));
            }

            // Camera Rotation
            function rotateCamera(cameraIndex, angle) {
                fetch(`/camera/${cameraIndex}/rotate/${angle}`)
                    .then(response => response.json())
                    .then(data => {
                        console.log('Camera rotated:', data);
                        // Update button states
                        document.querySelectorAll(`[onclick^="rotateCamera(${cameraIndex}"]`).forEach(btn => {
                            btn.classList.remove('active');
                        });
                        event.target.classList.add('active');
                        // Refresh the specific camera feed
                        const img = document.querySelector(`img[alt="Camera ${cameraIndex}"]`);
                        if (img) {
                            img.src = img.src.split('?')[0] + '?t=' + new Date().getTime();
                        }
                    })
                    .catch(error => console.error('Rotation Error:', error));
            }

            // Initialize with default states
            document.addEventListener('DOMContentLoaded', function() {
                setRGB('gecko');
                setDisplay('system');
            });
        </script>
    </body>
    </html>
    '''

if __name__ == '__main__':
    print("🚀 Starting Fixed Pi 5 Camera Streaming...")
    print("📹 Camera Configuration:")
    print("   - Camera 0: Main Habitat (device 0)")
    print("   - Camera 2: Secondary View (device 2, 180° rotated)")
    print("   - Camera 4: Wide Angle (device 4, 90° rotated) - FIXED")
    print("🔧 Features:")
    print("   - Proper device mapping")
    print("   - Camera 4 automatically rotated 90°")
    print("   - Thread-safe multi-camera support")
    print("   - Automatic fallback to test patterns")
    
    # Start camera threads
    start_camera_threads()
    
    print("📊 Status: http://192.168.50.108:8080/status")
    print("🌐 Main Page: http://192.168.50.108:8080")
    print("🎬 Fixed camera system ready!")

    app.run(host='0.0.0.0', port=8080, debug=False)
