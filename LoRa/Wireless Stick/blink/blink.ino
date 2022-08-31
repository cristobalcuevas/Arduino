#include "heltec.h"

void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, false /*Heltec.Heltec.Heltec.LoRa Disable*/, false /*Serial Enable*/);

}

void loop() {
  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
  delay(1000);
}
