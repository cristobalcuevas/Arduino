#include "heltec.h"

//433E6 for Asia
//866E6 for Europe
//915E6 for North America
#define BAND    915E6

int counter = 0;

void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  Heltec.display->drawString(0, 0, "LoRa transmisor");
  Heltec.display->drawString(0, 12, "LoRa iniciado");
  Heltec.display->display();
  Serial.print("LoRa transmisor");
  Serial.print("LoRa iniciado");
  delay(2000);
}

void loop() {
  Serial.print("Paquete ");
  Serial.println(counter);
  Heltec.display->clear();
  Heltec.display->drawString(0, 0, "Paquete ");
  Heltec.display->drawString(0, 12, String(counter));
  Heltec.display->display();
  // send packet
  LoRa.beginPacket();
  /*
    LoRa.setTxPower(txPower,RFOUT_pin);
    txPower -- 0 ~ 20
    RFOUT_pin could be RF_PACONFIG_PASELECT_PABOOST or RF_PACONFIG_PASELECT_RFO
      - RF_PACONFIG_PASELECT_PABOOST -- LoRa single output via PABOOST, maximum output 20dBm
      - RF_PACONFIG_PASELECT_RFO     -- LoRa single output via RFO_HF / RFO_LF, maximum output 14dBm
  */
  LoRa.setTxPower(14, RF_PACONFIG_PASELECT_PABOOST);
  LoRa.print("Paquete ");
  LoRa.print(counter);
  LoRa.endPacket();
  counter++;
  delay(2000);
}
