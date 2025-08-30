#!/usr/bin/env python3
"""
Simple Gecko Detection System Test
Shows what's working without connection issues
"""

import requests
import time
import json
from datetime import datetime

def test_pi5():
    """Test Pi 5 camera streaming"""
    print("📹 Testing Pi 5 Camera Streaming...")
    print("-" * 40)
    
    try:
        # Test main status
        response = requests.get("http://192.168.50.108:8080/status", timeout=5)
        if response.status_code == 200:
            data = response.json()
            print(f"✅ Pi 5 Status: {data['system']}")
            print(f"📹 Cameras: {list(data['cameras'].keys())}")
            print(f"🎨 RGB Lights: {data.get('rgb_lights', 'unknown')}")
            print(f"📺 Display: {data.get('display', 'unknown')}")
            return True
        else:
            print(f"❌ Pi 5 returned status {response.status_code}")
            return False
    except Exception as e:
        print(f"❌ Pi 5 connection failed: {e}")
        return False

def test_camera_feeds():
    """Test individual camera feeds"""
    print("\n📹 Testing Camera Feeds...")
    print("-" * 40)
    
    cameras = [0, 2, 4]
    working_cameras = 0
    
    for camera in cameras:
        try:
            response = requests.get(f"http://192.168.50.108:8080/camera{camera}", timeout=3)
            if response.status_code == 200:
                print(f"✅ Camera {camera}: Working")
                working_cameras += 1
            else:
                print(f"❌ Camera {camera}: Status {response.status_code}")
        except Exception as e:
            print(f"❌ Camera {camera}: Connection failed")
    
    print(f"\n📊 Camera Summary: {working_cameras}/{len(cameras)} cameras working")
    return working_cameras > 0

def test_rgb_controls():
    """Test RGB light controls"""
    print("\n🎨 Testing RGB Light Controls...")
    print("-" * 40)
    
    modes = ["gecko", "rainbow", "blue", "green", "red", "off"]
    working_modes = 0
    
    for mode in modes:
        try:
            response = requests.get(f"http://192.168.50.108:8080/rgb/{mode}", timeout=3)
            if response.status_code == 200:
                print(f"✅ RGB {mode}: Working")
                working_modes += 1
            else:
                print(f"❌ RGB {mode}: Status {response.status_code}")
        except Exception as e:
            print(f"❌ RGB {mode}: Connection failed")
    
    print(f"\n📊 RGB Summary: {working_modes}/{len(modes)} modes working")
    return working_modes > 0

def test_display_controls():
    """Test display controls"""
    print("\n📺 Testing Display Controls...")
    print("-" * 40)
    
    screens = ["system", "cameras", "gecko", "status"]
    working_screens = 0
    
    for screen in screens:
        try:
            response = requests.get(f"http://192.168.50.108:8080/display/{screen}", timeout=3)
            if response.status_code == 200:
                print(f"✅ Display {screen}: Working")
                working_screens += 1
            else:
                print(f"❌ Display {screen}: Status {response.status_code}")
        except Exception as e:
            print(f"❌ Display {screen}: Connection failed")
    
    print(f"\n📊 Display Summary: {working_screens}/{len(screens)} screens working")
    return working_screens > 0

def test_jetson():
    """Test Jetson detection system"""
    print("\n🤖 Testing Jetson Detection System...")
    print("-" * 40)
    
    try:
        response = requests.get("http://100.126.96.99:5000/detection_data", timeout=5)
        if response.status_code == 200:
            print("✅ Jetson Detection System: Working")
            return True
        else:
            print(f"❌ Jetson returned status {response.status_code}")
            return False
    except Exception as e:
        print(f"❌ Jetson connection failed: {e}")
        return False

def main():
    """Run all tests"""
    print("🦎 Gecko Detection System - Simple Test")
    print("=" * 50)
    print(f"Test started at: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    print()
    
    # Test Pi 5
    pi5_working = test_pi5()
    
    if pi5_working:
        # Test camera feeds
        cameras_working = test_camera_feeds()
        
        # Test RGB controls
        rgb_working = test_rgb_controls()
        
        # Test display controls
        display_working = test_display_controls()
    else:
        cameras_working = False
        rgb_working = False
        display_working = False
    
    # Test Jetson
    jetson_working = test_jetson()
    
    # Summary
    print("\n📊 Test Summary")
    print("=" * 50)
    print(f"Pi 5 System: {'✅ Working' if pi5_working else '❌ Failed'}")
    print(f"Camera Feeds: {'✅ Working' if cameras_working else '❌ Failed'}")
    print(f"RGB Controls: {'✅ Working' if rgb_working else '❌ Failed'}")
    print(f"Display Controls: {'✅ Working' if display_working else '❌ Failed'}")
    print(f"Jetson Detection: {'✅ Working' if jetson_working else '❌ Failed'}")
    
    print("\n🌐 Access URLs:")
    print(f"Pi 5 Interface: http://192.168.50.108:8080")
    print(f"Jetson Interface: http://100.126.96.99:5000")
    print(f"Quick Test Page: file:///Users/andrelewis/HomeProjects/Personal_Projects/quick_test.html")
    
    print("\n🎯 Next Steps:")
    if pi5_working:
        print("1. Open Pi 5 interface to see camera feeds")
        print("2. Test RGB light controls")
        print("3. Test display controls")
    else:
        print("1. Check Pi 5 network connection")
        print("2. Verify Pi 5 camera service is running")
    
    if not jetson_working:
        print("4. Deploy Jetson detection system")
    
    print("5. Run Mac remote monitor: python3 mac_remote_monitor.py")

if __name__ == "__main__":
    main()
