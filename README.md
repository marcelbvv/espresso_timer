# Espresso timer and PID
Development of a machine-independent espresso timer with a round display driven by a ESP8266 or ESP32 microcontroller. 


## Components:
 * 1.28" TFT screen (GC9A01)
 * ESP32 or ESP8266
 * 220V to 3.3V converter
 * Magnetic sensor
 * 3D printed parts
 * 7 wire cable
 * K-type temperature probe
 * MAX6675 Amplifier
 * SSR40-DA
 * KY-040

## Connections:
GC9A01 to ESP8266 NodeMCU V3
* RST ==> Not connected
* CS ==> D8
* DC ==> D3
* SDA/DIN ==> D7
* SCL/CLK ==> D5
* GND ==> GND
* VCC ==> 3V3

Reed Sensor to ESP8266 NodeMCU V3
* Lead1 ==> 3V3
* Lead2 ==> A0

MAX6675 probe to ESP8266
* VCC ==> 3V3
* GND ==> GND
* CLK ==> D5
* CS ==> D4
* SO ==> D7

SSR40 to ESP8266
* + ==> D1
* - ==> GND

KY-040 to ESP8266



## Setup steps:
1. Open Arduino IDE
2. Configure the board
3. Upload SensorTimer.ino file

## Installation in machine:
1. Open espresso machine
2. Locate water pump
3. Attach magnetic sensor to pump
4. Route screen cable to desired position
