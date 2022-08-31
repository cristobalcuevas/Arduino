#include "heltec.h"
void setup() {
  Heltec.begin(true, false, false); // Display, LoRa, Serial
  // heltec begin incluye display: init, flipScreenVertically, setFont, drawString y display
  Heltec.display->clear(); // con esto borramos el mensaje que manda la libreria (OLED initial done)
}
void loop() {
  Heltec.display->drawString(0, 0, "Hello world");
  Heltec.display->display();
}
