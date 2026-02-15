# 🌊 ESP32 Based Smart Aquarium Monitoring & Automated Feeding System

## 📌 Project Overview

The ESP32-Based Smart Aquarium System is an IoT-enabled embedded solution designed to automate aquarium monitoring and maintenance. The system continuously monitors critical water parameters including temperature, pH level, water level, and light intensity using a 4-in-1 water quality sensor.

The ESP32 microcontroller acts as the central control unit, processing sensor data and comparing it with predefined safety thresholds. When abnormal conditions are detected, a relay module is activated to control the water pump automatically, ensuring proper water circulation and maintaining a stable aquatic environment.

Real-time monitoring is achieved using the Blynk IoT platform via Wi-Fi connectivity.

---

## 🛠 Hardware Components Used

- ESP32 Microcontroller  
- 4-in-1 Water Quality Sensor  
- Relay Module  
- Water Pump  
- 5V Regulated Power Supply  
- Servo Motor (for feeder mechanism)  
- Plastic Bottle (used as feed container)

---

## 🐟 Innovative Low-Cost Mechanical Fish Feeder

A key innovation in this project is the integration of a low-cost mechanical fish feeder system.

The feeder is built using a simple plastic bottle as the feed container. The bottle is connected to a hobby servo motor that rotates the bottle at scheduled intervals. A rotating flap mechanism allows controlled dispensing of fish feed.

This design offers:

- Low implementation cost  
- Use of easily available materials  
- Controlled feed dispensing  
- Reduced manual effort  
- Simple and maintainable structure  

The servo motor is controlled by the ESP32, enabling automated and scheduled feeding.

---

## ⚙ System Working

1. Sensor measures temperature, pH, water level, and light intensity.
2. ESP32 processes and validates sensor readings.
3. If values exceed safe thresholds, relay activates the water pump.
4. Real-time data is sent to the Blynk mobile dashboard.
5. Servo motor rotates the bottle feeder at scheduled intervals to dispense feed.
6. Continuous monitoring loop ensures stable operation.

---

## ⚡ System Features

- Real-time IoT monitoring  
- Automatic pump control  
- Servo-driven automated feeding  
- Low power consumption (~1.5W)  
- Compact and cost-effective design  
- Suitable for home and small-scale aquarium setups  

---

## 👩‍💻 Developed By

Stuti Pandey  
B.Tech – Electronics & Communication Engineering  

