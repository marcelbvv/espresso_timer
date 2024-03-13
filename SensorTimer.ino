// Screen setup
#include "Adafruit_GFX.h"
#include "Adafruit_GC9A01A.h"

#define TFT_DC D3
#define TFT_CS D8
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 240
#define RED         0xF800
#define GREEN       0x07E0
#define YELLOW      0xFFE0
#define DEG2RAD 0.0174532925

Adafruit_GC9A01A tft(TFT_CS, TFT_DC);

// Screen variables
int w = 20;
int rx = 120;
int ry = 120;

// Sensor Settings
const int pump_input = A0;  // ESP8266 Analog Pin ADC0 = A0
const int numReadings = 10; // Number of readings to average
int pumpValue = 0;  // value read from the pot
int readings[numReadings];  // the readings from the analog input
int readIndex = 0;          // the index of the current reading
int total = 0;              // the running total
int average = 0;        
int threshold_sensor = 50;  

// General variables
uint32_t startTime;
bool running = false;
bool last_running = false;
int seconds = 0;
int last_seconds = 0;
bool counting = false;

void setup() {
  Serial.begin(9600);
  // Initiate sensor readings
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  // Initiate screen
  tft.begin();
  tft.setRotation(0);  // Adjust the rotation if needed
  tft.fillScreen(GC9A01A_BLACK);
  tft.setTextColor(GC9A01A_WHITE, GC9A01A_BLACK);
  tft.setTextSize(10);

  // Initate counter
  displaySeconds();
}

void loop() {
  // Read input value and update moving average
  total = total - readings[readIndex];  // subtract the last reading
  readings[readIndex] = analogRead(pump_input); // read from the sensor
  total = total + readings[readIndex];  // add the reading to the total
  readIndex = readIndex + 1;  // advance to the next position in the array
  if (readIndex >= numReadings) { // if we're at the end of the array...
    readIndex = 0;
  }
  average = total / numReadings;  // Calculate sliding average
  
  if (average > threshold_sensor) {
    running = true;
  }
  else {
    running = false;
  }

  if (running) {
    if (counting) {
      if (seconds == 60) {
        tft.fillScreen(GC9A01A_BLACK);
        seconds = 0;
      }
      // Update time
      if (millis() - startTime >= 1000) {
        startTime = millis();
        seconds++;  // Update time
        displaySeconds();
        if (seconds > 0 && seconds < 15) {
        fillArc(120, 120, 180 + (6 * (seconds - 1)), 2, rx, ry, w, RED);
        }
        if (seconds >= 15 && seconds < 25) {
          fillArc(120, 120, 180 + (6 * (seconds - 1)), 2, rx, ry, w, YELLOW);
        }
        if (seconds >= 25 && seconds < 35) {
          fillArc(120, 120, 180 + (6 * (seconds - 1)), 2, rx, ry, w, GREEN);
        }
          if (seconds >= 35 && seconds < 45) {
          fillArc(120, 120, 180 + (6 * (seconds - 1)), 2, rx, ry, w, YELLOW);
        }
          if (seconds >= 45 && seconds <= 60) {
          fillArc(120, 120, 180 + (6 * (seconds - 1)), 2, rx, ry, w, RED);
        }
      }
    }
    else {
      counting = true;
      startTime = millis();
      seconds = 0;
      displaySeconds();
    }
  }

  else {
    counting = false;
  }

  // TESTING: Update values in Serial Monitor
  Serial.print("SensorVal:");
  Serial.println(analogRead(pump_input));
  Serial.print(",");
  Serial.print("Pump:");
  if (running) {
    Serial.println(500);
  }
  else {
    Serial.println(0);
  }
  Serial.print("Average:");
  Serial.println(average);
  

  delay(5);
}

// Function to draw segments
void fillArc(int x, int y, int start_angle, int seg_count, int rx, int ry, int w, uint16_t colour) {
  // x,y == coords of centre of arc
  // start_angle = 0 - 359
  // seg_count = number of 3 degree segments to draw (120 => 360 degree arc)
  // rx = x axis radius
  // yx = y axis radius
  // w  = width (thickness) of arc in pixels
  // colour = 16 bit colour value
  // Note if rx and ry are the same an arc of a circle is drawn
  byte seg = 3;  // Segments are 3 degrees wide = 120 segments for 360 degrees
  byte inc = 3;  // Draw segments every 3 degrees, increase to 6 for segmented ring
  // Draw colour blocks every inc degrees
  for (int i = start_angle; i < start_angle + seg * seg_count; i += inc) {
    // Calculate pair of coordinates for segment start
    float sx = cos((i - 90) * DEG2RAD);
    float sy = sin((i - 90) * DEG2RAD);
    uint16_t x0 = sx * (rx - w) + x;
    uint16_t y0 = sy * (ry - w) + y;
    uint16_t x1 = sx * rx + x;
    uint16_t y1 = sy * ry + y;

    // Calculate pair of coordinates for segment end
    float sx2 = cos((i + seg - 90) * DEG2RAD);
    float sy2 = sin((i + seg - 90) * DEG2RAD);
    int x2 = sx2 * (rx - w) + x;
    int y2 = sy2 * (ry - w) + y;
    int x3 = sx2 * rx + x;
    int y3 = sy2 * ry + y;

    tft.fillTriangle(x0, y0, x1, y1, x2, y2, colour);
    tft.fillTriangle(x1, y1, x2, y2, x3, y3, colour);
  }
}

// Function to update the seconds
void displaySeconds() {
  // Reset screen at begining and end of cycle
  if (seconds == 0) {
    tft.fillScreen(GC9A01A_BLACK);  // Clear the screen
  }
  // Set location for single digit numbers
  if (seconds < 10) {
    tft.setCursor(90, 80);
  }
  // Set location for double digit numbers
  else {
    tft.setCursor(60, 80);
  }
  tft.print(seconds);
}