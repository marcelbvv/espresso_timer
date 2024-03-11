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

int seconds = 0;
int w = 20;
int rx = 120;
int ry = 120;

void setup() {
  Serial.begin (9600);
  // Initialize the display
  tft.begin();
  tft.setRotation(0);  // Adjust the rotation if needed
  tft.fillScreen(GC9A01A_BLACK);
  tft.setTextColor(GC9A01A_WHITE, GC9A01A_BLACK);
  tft.setTextSize(10);
}

void loop() {
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

  // If the seconds count reaches 60, reset it to 0
  if (seconds == 60) {
    tft.fillScreen(GC9A01A_BLACK);
    seconds = 0;
  }
  // Increment the seconds count
  seconds++;
  delay(1000);
}

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
