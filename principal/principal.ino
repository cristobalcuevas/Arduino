/*
  Cristobal Cuevas Lagos
  Conversión de vueltas de encoder a desplazamiento
  23-06-2022
*/
#include "bluetooth.h"
#include "encoder.h"
#include "microsd.h"
#include "rtc.h"

bt bluetooth;
Encoder encoder(12, 13);
microSD microsd;
RTC rtc2;

void setup() {
  Serial.begin(115200);
  bluetooth.begin();
  encoder.begin();
  microsd.begin();
  rtc2.begin();
}
void loop() {
  ahora = rtc.now();
  if (counter != ISRCounter) {
    counter = ISRCounter;
    String dataMessage = String(rtc2.printDate()) + " " + String(counter) + " " + String(encoder.distanceCalculator()) + "\r\n";
    bluetooth.printDataBT(dataMessage);
    microsd.saveDataSD(dataMessage);
  }
}
