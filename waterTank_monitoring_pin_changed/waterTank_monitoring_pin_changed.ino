#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial bluetooth(4, 5); // RX, TX

// Define pins
#define TRIG_PIN 3
#define ECHO_PIN 2
#define PH_PIN A0
#define TDS_PIN A1
#define motor 7

#define EEPROM_HEIGHT_ADDR 0

// Variables for sensor readings
long duration;
float distance;
int phValue;
float ph;
int tdsValue;
float tds;
bool motorState=false;
int tankHeight = 150;

void readSensors() {
  phValue = analogRead(PH_PIN);
  ph = ((phValue/1023.0)*14.0);
  tdsValue = analogRead(TDS_PIN);
  tds = (tdsValue / 1023.0) * 1000.0;
}


// float previousDistance = -1;  // Stores the previous good reading
// const float SPIKE_THRESHOLD = 10.0; // Max allowed sudden change in cm
float currentReading;

float readDistance() {
  float readings[3];
  for (int i = 0; i < 3; i++) {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    long d = pulseIn(ECHO_PIN, HIGH);
    readings[i] = (d / 2.0)*0.0344;
    delay(50);
  }

  if ((readings[0] > readings[1]) != (readings[0] > readings[2]))
  currentReading= readings[0];
  else if ((readings[1] > readings[0]) != (readings[1] > readings[2]))
  currentReading=readings[1];
  else
  currentReading=readings[2];

  // if (previousDistance > 0 && abs(currentReading - previousDistance) > SPIKE_THRESHOLD) {
  //   return previousDistance; // Reject sudden jump, return last good reading
  // }

  // previousDistance = currentReading;
  return currentReading;

}



// float previousDistance = -1;  // Stores the previous good reading
// const float SPIKE_THRESHOLD = 10.0; // Max allowed sudden change in cm
// const int NUM_READINGS = 7; // More readings = smoother result

// float readDistance() {
//   float readings[NUM_READINGS];
//   int validCount = 0;
//   float sum = 0;

//   for (int i = 0; i < NUM_READINGS; i++) {
//     // Trigger the ultrasonic pulse
//     digitalWrite(TRIG_PIN, LOW);
//     delayMicroseconds(2);
//     digitalWrite(TRIG_PIN, HIGH);
//     delayMicroseconds(10);
//     digitalWrite(TRIG_PIN, LOW);

//     // Read echo duration with timeout
//     long duration = pulseIn(ECHO_PIN, HIGH, 25000); // timeout at ~4.3m
//     float distance = (duration > 0) ? (duration / 2.0) / 29.1 : -1;

//     // Filter out readings that are too short/long (invalid)
//     if (distance >= 2 && distance <= 400) {
//       readings[validCount++] = distance;
//     }

//     delay(50); // Short delay before next reading
//   }

//   // If no valid readings found, return -1
//   if (validCount == 0) return -1;

//   // Remove min and max (simple outlier rejection)
//   float minVal = readings[0], maxVal = readings[0];
//   for (int i = 1; i < validCount; i++) {
//     if (readings[i] < minVal) minVal = readings[i];
//     if (readings[i] > maxVal) maxVal = readings[i];
//   }

//   for (int i = 0; i < validCount; i++) {
//     if (readings[i] != minVal && readings[i] != maxVal) {
//       sum += readings[i];
//     }
//   }

//   int averageCount = validCount - 2; // Excluding min and max
//   float average = (averageCount > 0) ? (sum / averageCount) : (sum / validCount);

//   // Debounce sudden spikes by comparing with previous reading
//   if (previousDistance > 0 && abs(average - previousDistance) > SPIKE_THRESHOLD) {
//     return previousDistance; // Reject sudden jump, return last good reading
//   }

//   previousDistance = average;
//   return average;
// }

void updateLCD(float tankLevelPercent) {
  lcd.setCursor(0, 0);
  lcd.print("TankLvl:");
  lcd.print((int)tankLevelPercent);
  lcd.print("%     ");
  lcd.setCursor(0, 1);
  lcd.print("pH:");
  lcd.print(ph, 1);
  lcd.setCursor(9, 1);
  lcd.print("Imp:");
  lcd.print((int)tds);
}

void handleBluetoothCommand(String command) {
  command.trim();
  if (command == "GiveConf") {
    bluetooth.println("height:"+String(tankHeight)+":motorState:"+String(motorState? "ON": "OFF"));
  } 
  else if (command.startsWith("SetHeight:")) {
    int colonIndex = command.indexOf(':');
    if (colonIndex != -1) {
      String valueStr = command.substring(colonIndex + 1);
      int height = valueStr.toInt();

      // Store in EEPROM (int takes 2 bytes)
      EEPROM.put(EEPROM_HEIGHT_ADDR, height);

      Serial.print("Height set to: ");
      Serial.println(height);
    }
  } 
  else if (command == "MotorOn") {
    motorState = true;
    digitalWrite(motor, LOW);
  } 
  else if (command == "MotorOff") {
    motorState=false;
    digitalWrite(motor, HIGH);
  }
}

void setup() {
  pinMode(motor, OUTPUT);
  digitalWrite(motor, HIGH);
  motorState=false;

  Serial.begin(9600);  // For debugging through the serial monitor
  bluetooth.begin(9600);  // The Bluetooth module typically communicates at 9600 baud rate
  
  // Initialize pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(PH_PIN, INPUT);
  pinMode(TDS_PIN, INPUT);
  
  lcd.init();             // Initialize the LCD
  lcd.backlight();        // Turn on the backlight

  EEPROM.get(EEPROM_HEIGHT_ADDR, tankHeight);
  if (tankHeight <= 0 || tankHeight > 500) tankHeight = 150;
}

void loop() {
  distance = readDistance();
  float waterLevel = tankHeight - distance;
  float tankLevelPercent = constrain((waterLevel / tankHeight) * 100, 0, 100);

  readSensors();

  // 4. Prepare data to send via Bluetooth
  String data = String(tankLevelPercent) + "," + String(ph) + "," + String(tds);
  Serial.println(data);
  bluetooth.println(data);
  updateLCD(tankLevelPercent);

  // 6. Check if data was received from Bluetooth (using Serial for debugging)
  if (bluetooth.available()) {
    String command = bluetooth.readStringUntil('\n');
    Serial.println(command);
    handleBluetoothCommand(command);
  }

   if (waterLevel >= tankHeight - 5) {
    motorState = false;
    digitalWrite(motor, HIGH);
    bluetooth.println("height:"+String(tankHeight)+":motorState:"+String(motorState? "ON": "OFF"));
  }

  if (waterLevel <= 5 && waterLevel>0) {
    motorState = true;
    digitalWrite(motor, LOW);
    bluetooth.println("height:"+String(tankHeight)+":motorState:"+String(motorState? "ON": "OFF"));
  }

  // Wait for 1 seconds before sending next data
  delay(1000);
}
