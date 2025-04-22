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
| D3          | HC-SR04 Trigger        |
| D2          | HC-SR04 Echo           |
| A0          | pH Sensor Output       |
| A1          | TDS Sensor Output      |
| D5 (TX)    | HC-05 RX               |
| D4 (RX)    | HC-05 TX               |
| D7          | Relay IN               |
| I2C (A4/A5) | LCD I2C SDA/SCL        |

### 💻 Arduino Code

You can find the full Arduino code in [arduino_code.ino](WaterTankMonitoring/WaterTankMonitoring.ino) in this repository. It includes:

- Water level calculation using ultrasonic sensor
- Reading and mapping pH and TDS sensor values
- Sending sensor data via Bluetooth to mobile app (AquaPylot)
- LCD output
- Relay control logic for auto filling of water. Also auto off.

---

## 📱 Part 2: Aquapylot Mobile App (MIT App Inventor)

Aquapylot is a mobile app that connects to the Arduino system via Bluetooth and provides a modern UI for:

- 🌊 Viewing water tank level
- ⚙️ Switching between Auto and Manual motor control
- 🧪 Viewing pH and TDS values

### 📲 Download APK

You can download the app here: [Download Aquapylot APK](AquaPylot.apk)

---
## 📷 Project Images

<h3>🔌Unassemble project with different parts</h3>
<img src="Images/project_description.jpg" width="400"/>

<h3>🔧 Final Assembled project</h3>
<img src="Images/assembled_project.jpg" width="400"/>

<h3>AquaPylot app interface:</h3>
<img src="Images/aquapylot_ui2.jpg" width="400"/>


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

## 🙏 Acknowledgements

We would like to thank our course instructor, Prof. Arup lal Chakroborty, for designing this curriculum for theoretical learning along with hands on experience through this project
and other lab tasks. Our TA Shouharda Ghosh for guiding us
throughout the learning process, simplifying the concepts in really easier way, providing right resources to learn from. Our thanks also extend to the
lab staff for making available the necessary resources at right
time. This project wouldn’t have been possible without their
help
Their insights and motivation were instrumental in helping us bring **Aquapylot** to life.


---
