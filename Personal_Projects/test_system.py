#!/usr/bin/env python3
"""
Comprehensive System Test for Gecko Detection System
Tests all components: Pi 5 camera streaming, Jetson detection, and Mac monitor
"""

import requests
import time
import json
import sys
from datetime import datetime

class SystemTester:
    def __init__(self):
        self.config = {
            "pi5_ip": "192.168.50.108",
            "jetson_ip": "100.126.96.99",
            "pi5_port": 8080,
            "jetson_port": 5000,
            "timeout": 5
        }
        
        self.results = {
            "pi5_camera": {"status": "unknown", "details": ""},
            "jetson_detection": {"status": "unknown", "details": ""},
            "camera_rotation": {"status": "unknown", "details": ""},
            "rgb_control": {"status": "unknown", "details": ""},
            "display_control": {"status": "unknown", "details": ""},
            "detection_api": {"status": "unknown", "details": ""},
            "sensor_data": {"status": "unknown", "details": ""}
        }
    
    def test_endpoint(self, url, name):
        """Test if an endpoint is reachable"""
        try:
            response = requests.get(url, timeout=self.config["timeout"])
            if response.status_code == 200:
                return True, f"✅ {name} is working (Status: {response.status_code})"
            else:
                return False, f"❌ {name} returned status {response.status_code}"
        except requests.exceptions.ConnectionError:
            return False, f"❌ {name} connection failed"
        except requests.exceptions.Timeout:
            return False, f"❌ {name} timeout"
        except Exception as e:
            return False, f"❌ {name} error: {str(e)}"
    
    def test_pi5_camera_streaming(self):
        """Test Pi 5 camera streaming"""
        print("🔍 Testing Pi 5 Camera Streaming...")
        
        # Test main interface
        url = f"http://{self.config['pi5_ip']}:{self.config['pi5_port']}"
        success, details = self.test_endpoint(url, "Pi 5 Main Interface")
        self.results["pi5_camera"]["status"] = "working" if success else "failed"
        self.results["pi5_camera"]["details"] = details
        print(f"   {details}")
        
        # Test status API
        url = f"http://{self.config['pi5_ip']}:{self.config['pi5_port']}/status"
        success, details = self.test_endpoint(url, "Pi 5 Status API")
        print(f"   {details}")
        
        # Test individual camera streams
        for camera in [0, 2, 4]:
            url = f"http://{self.config['pi5_ip']}:{self.config['pi5_port']}/camera{camera}"
            success, details = self.test_endpoint(url, f"Camera {camera} Stream")
            print(f"   {details}")
    
    def test_camera_rotation(self):
        """Test camera rotation functionality"""
        print("🔄 Testing Camera Rotation...")
        
        for camera in [0, 2, 4]:
            for angle in [0, 90, 180, 270]:
                url = f"http://{self.config['pi5_ip']}:{self.config['pi5_port']}/camera/{camera}/rotate/{angle}"
                success, details = self.test_endpoint(url, f"Camera {camera} Rotation {angle}°")
                if success:
                    print(f"   ✅ Camera {camera} rotation {angle}° working")
                else:
                    print(f"   ❌ Camera {camera} rotation {angle}° failed")
        
        self.results["camera_rotation"]["status"] = "working"
        self.results["camera_rotation"]["details"] = "Camera rotation endpoints tested"
    
    def test_rgb_control(self):
        """Test RGB light control"""
        print("🎨 Testing RGB Light Control...")
        
        modes = ["gecko", "rainbow", "blue", "green", "red", "purple", "orange", "off"]
        working_modes = 0
        
        for mode in modes:
            url = f"http://{self.config['pi5_ip']}:{self.config['pi5_port']}/rgb/{mode}"
            success, details = self.test_endpoint(url, f"RGB {mode} mode")
            if success:
                working_modes += 1
                print(f"   ✅ RGB {mode} mode working")
            else:
                print(f"   ❌ RGB {mode} mode failed")
        
        self.results["rgb_control"]["status"] = "working" if working_modes > 0 else "failed"
        self.results["rgb_control"]["details"] = f"{working_modes}/{len(modes)} RGB modes working"
    
    def test_display_control(self):
        """Test display control"""
        print("📺 Testing Display Control...")
        
        screens = ["system", "cameras", "gecko", "status", "temperature", "humidity"]
        working_screens = 0
        
        for screen in screens:
            url = f"http://{self.config['pi5_ip']}:{self.config['pi5_port']}/display/{screen}"
            success, details = self.test_endpoint(url, f"Display {screen} screen")
            if success:
                working_screens += 1
                print(f"   ✅ Display {screen} screen working")
            else:
                print(f"   ❌ Display {screen} screen failed")
        
        self.results["display_control"]["status"] = "working" if working_screens > 0 else "failed"
        self.results["display_control"]["details"] = f"{working_screens}/{len(screens)} display screens working"
    
    def test_jetson_detection(self):
        """Test Jetson detection system"""
        print("🤖 Testing Jetson Detection System...")
        
        # Test main interface
        url = f"http://{self.config['jetson_ip']}:{self.config['jetson_port']}"
        success, details = self.test_endpoint(url, "Jetson Main Interface")
        self.results["jetson_detection"]["status"] = "working" if success else "failed"
        self.results["jetson_detection"]["details"] = details
        print(f"   {details}")
        
        # Test detection data API
        url = f"http://{self.config['jetson_ip']}:{self.config['jetson_port']}/detection_data"
        success, details = self.test_endpoint(url, "Detection Data API")
        self.results["detection_api"]["status"] = "working" if success else "failed"
        self.results["detection_api"]["details"] = details
        print(f"   {details}")
        
        # Test sensor data
        url = f"http://{self.config['jetson_ip']}:{self.config['jetson_port']}/sensor_data"
        success, details = self.test_endpoint(url, "Sensor Data API")
        self.results["sensor_data"]["status"] = "working" if success else "failed"
        self.results["sensor_data"]["details"] = details
        print(f"   {details}")
        
        # Test detection streams
        for camera in [0, 2, 4]:
            url = f"http://{self.config['jetson_ip']}:{self.config['jetson_port']}/detection{camera}"
            success, details = self.test_endpoint(url, f"Detection Stream {camera}")
            print(f"   {details}")
    
    def test_heat_lamp(self):
        """Test heat lamp control"""
        print("🌡️ Testing Heat Lamp Control...")
        
        url = f"http://{self.config['jetson_ip']}:{self.config['jetson_port']}/heat_lamp_status"
        success, details = self.test_endpoint(url, "Heat Lamp Status")
        print(f"   {details}")
    
    def run_comprehensive_test(self):
        """Run all tests"""
        print("🦎 Gecko Detection System - Comprehensive Test")
        print("=" * 50)
        print(f"Test started at: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
        print()
        
        # Test Pi 5 components
        print("📹 Testing Pi 5 Components...")
        print("-" * 30)
        self.test_pi5_camera_streaming()
        print()
        
        self.test_camera_rotation()
        print()
        
        self.test_rgb_control()
        print()
        
        self.test_display_control()
        print()
        
        # Test Jetson components
        print("🔍 Testing Jetson Components...")
        print("-" * 30)
        self.test_jetson_detection()
        print()
        
        self.test_heat_lamp()
        print()
        
        # Generate summary
        self.generate_summary()
    
    def generate_summary(self):
        """Generate test summary"""
        print("📊 Test Summary")
        print("=" * 50)
        
        total_tests = len(self.results)
        passed_tests = sum(1 for result in self.results.values() if result["status"] == "working")
        failed_tests = total_tests - passed_tests
        
        print(f"Total Tests: {total_tests}")
        print(f"✅ Passed: {passed_tests}")
        print(f"❌ Failed: {failed_tests}")
        print(f"Success Rate: {(passed_tests/total_tests)*100:.1f}%")
        print()
        
        print("Detailed Results:")
        for test_name, result in self.results.items():
            status_icon = "✅" if result["status"] == "working" else "❌"
            print(f"  {status_icon} {test_name.replace('_', ' ').title()}: {result['details']}")
        
        print()
        
        if failed_tests == 0:
            print("🎉 All systems are working perfectly!")
        elif failed_tests <= 2:
            print("⚠️  Most systems are working. Check failed components.")
        else:
            print("🚨 Multiple systems need attention. Review failed components.")
        
        print()
        print("🌐 Quick Access URLs:")
        print(f"  Pi 5 Interface: http://{self.config['pi5_ip']}:{self.config['pi5_port']}")
        print(f"  Jetson Interface: http://{self.config['jetson_ip']}:{self.config['jetson_port']}")
        print()
        print("📋 Next Steps:")
        if failed_tests > 0:
            print("  1. Check network connectivity")
            print("  2. Verify services are running")
            print("  3. Check system logs")
            print("  4. Restart failed services")
        else:
            print("  1. Open Pi 5 interface to test camera rotation")
            print("  2. Open Jetson interface to view detections")
            print("  3. Run Mac remote monitor")
            print("  4. Test RGB and display controls")

def main():
    """Main function"""
    tester = SystemTester()
    
    try:
        tester.run_comprehensive_test()
    except KeyboardInterrupt:
        print("\n\n⚠️  Test interrupted by user")
        sys.exit(1)
    except Exception as e:
        print(f"\n\n❌ Test failed with error: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()
