#include <Wire.h>
#include "SSD1306Wire.h"

#define OLED_DIR  0x3c
#define OLED_SDA  4
#define OLED_SCL  15
#define OLED_RST  16

SSD1306Wire display(OLED_DIR, OLED_SDA, OLED_SCL, GEOMETRY_64_32);

void setup() {
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(50);
  digitalWrite(OLED_RST, HIGH);
  display.init();
  display.flipScreenVertically();
  display.clear();
}
void loop() {
  display.drawString(0, 0, "Hola mundo");
  display.display();
}
