#include "blink.h"
Blink led (13);
void setup() {}
void loop() {
  led.blink(ON, 1000);
}
