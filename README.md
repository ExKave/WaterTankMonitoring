# Aquapylot – Smart Water Tank Monitoring App 🚰📲

Aquapylot is a mobile app developed using MIT App Inventor for real-time monitoring of water tank levels, water quality (pH, TDS), and motor control using Bluetooth communication with an Arduino-based system.

## 🛠️ Features

- 🚰 Real-time water level monitoring
- 📊 pH and TDS sensor readings
- 🧠 Auto/Manual motor control
- 📲 Bluetooth connectivity to Arduino
- 📟 Custom UI designed in MIT App Inventor

---

## 📸 Screenshots

### Designer View (UI Components)
![Designer Screenshot](screenshots/designer_view.png)

### Block Code – Bluetooth Setup
![Bluetooth Block Code](screenshots/bluetooth_blocks.png)

### Block Code – Auto Mode Control
![Auto Mode Block Code](screenshots/auto_mode_blocks.png)

### Block Code – Sensor Data Handling
![Sensor Block Code](screenshots/sensor_blocks.png)

> 📁 All screenshots are placed inside the `screenshots/` folder in this repository.

---

## 📦 Requirements

- MIT App Inventor (or .aia project file)
- Arduino + Sensors:
  - Ultrasonic Sensor
  - pH Sensor
  - TDS Sensor
  - Bluetooth HC-05
  - Relay Module
- Android device for app installation

---

## 🚀 How to Use

1. Upload the `.aia` file to MIT App Inventor.
2. Connect the Arduino system with sensors.
3. Install the `.apk` file on your mobile.
4. Turn on Bluetooth and pair with Arduino.
5. Start monitoring and control!

---

## 📂 File Structure

```plaintext
.
├── screenshots/
│   ├── designer_view.png
│   ├── bluetooth_blocks.png
│   ├── auto_mode_blocks.png
│   ├── sensor_blocks.png
├── Aquapylot.aia
├── Aquapylot.apk
└── README.md
