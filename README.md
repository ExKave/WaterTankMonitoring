# Aquapylot 🚰📲
A smart water tank monitoring system using Arduino and a custom mobile app built with MIT App Inventor.

---

## 🔧 Part 1: Arduino-Based Water Monitoring System

### 🧰 Components Used

| Component         | Purpose                        |
|------------------|--------------------------------|
| Arduino UNO      | Main microcontroller            |
| Ultrasonic Sensor (HC-SR04) | Water level measurement     |
| pH Sensor        | Water acidity measurement       |
| TDS Sensor       | Water quality measurement       |
| HC-05 Bluetooth Module | Communication with mobile app |
| 16x2 LCD with I2C| Display readings                |
| Relay Module     | Motor ON/OFF control            |
| Power Supply     | 5V regulated source             |

### 🔌 Circuit Connection Overview

| Arduino Pin | Connected To           |
|-------------|------------------------|
| D2          | HC-SR04 Trigger        |
| D3          | HC-SR04 Echo           |
| A0          | pH Sensor Output       |
| A1          | TDS Sensor Output      |
| D10 (TX)    | HC-05 RX               |
| D11 (RX)    | HC-05 TX               |
| D8          | Relay IN               |
| I2C (A4/A5) | LCD I2C SDA/SCL        |

### 💻 Arduino Code

You can find the full Arduino code in [arduino_code.ino](WaterTankMonitoring/WaterTankMonitoring.ino) in this repository. It includes:

- Water level calculation using ultrasonic sensor
- Reading and mapping pH and TDS sensor values
- Sending sensor data via Bluetooth
- EEPROM flag for Auto mode
- LCD output and relay control logic

---

## 📱 Part 2: Aquapylot Mobile App (MIT App Inventor)

Aquapylot is a mobile app that connects to the Arduino system via Bluetooth and provides a modern UI for:

- 🌊 Viewing water tank level
- ⚙️ Switching between Auto and Manual motor control
- 🧪 Viewing pH and TDS values

### 📲 Download APK

You can download the app here: [Download Aquapylot APK](Aquapylot.apk)

---

### 📸 App Screenshots

#### 🎨 UI Designer View
![Designer View](screenshots/designer_view.png)

#### 📡 Bluetooth Connection Logic
![Bluetooth Blocks](screenshots/bluetooth_blocks.png)

#### 🤖 Auto Mode Control Logic
![Auto Mode Blocks](screenshots/auto_mode_blocks.png)

#### 📈 Sensor Data Display and Parsing
![Sensor Blocks](screenshots/sensor_blocks.png)

> All screenshots are available in the `/screenshots` folder of this repo.

---

## 🧠 How to Use

1. Upload the Arduino code to your board.
2. Set up the hardware as per the connections above.
3. Install the Aquapylot APK on your Android phone.
4. Turn on Bluetooth and pair with HC-05 module.
5. Launch the app and start monitoring/control.

---

## 👨‍🔧 Authors

- **Bhakti Prasad Swain** – IIT Gandhinagar
- **Beerela Arun Kumar** – Collaborator

---

## 📃 License

MIT License
