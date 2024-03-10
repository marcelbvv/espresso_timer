# Espresso_timer
Development of a machine-independent espresso timer with a round display driven by a ESP8266 or ESP32 microcontroller. 


## Components:
 * 1.28" TFT screen (GC9A01)
 * ESP32 or ESP8266
 * 220V to 3.3V converter
 * Magnetic sensor
 * 3D printed parts
 * 7 wire cable

## Connections:
GC9A01 to ESP8266 NodeMCU V3
* RST ==> Not connected
* CS ==> D8
* DC ==> D3
* SDA/DIN ==> D7
* SCL/CLK ==> D5
* GND ==> GND
* VCC ==> 3V3

GC9A01 to ESP8266 Adafruit Huzzah
* RST ==> Not connected
* CS ==> 15
* DC ==> 2
* SDA/DIN ==> 4
* SCL/CLK ==> 5
* GND ==> GND
* VCC ==> 3V3

## Setup steps:
1. Open Arduino IDE
2. Configure the board
3. Upload sketch

## Installation in machine:
1. Open espresso machine
2. Locate water pump
3. Attach magnetic sensor to pump
4. Route screen cable to desired position
