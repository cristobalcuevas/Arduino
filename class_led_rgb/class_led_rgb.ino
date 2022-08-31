#include "ledRGB.h"

ledRGB miLed(6,5,3);
void setup() {
}

void loop() {
  miLed.randomColor();
  delay(1000);
}
