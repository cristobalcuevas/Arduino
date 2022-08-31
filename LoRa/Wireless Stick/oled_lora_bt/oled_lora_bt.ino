// Heltec Wireless Stick Board
// Libraries for LoRa
#include <SPI.h>
#include <LoRa.h>

//Libraries for OLED
#include <Wire.h>
#include "SSD1306Wire.h"

// Define the pins used by the LoRa transceiver module
#define SCK   5   // GPIO5  -- SX1278 SCK
#define MISO  19  // GPIO19 -- SX1278 MISO
#define MOSI  27  // GPIO27 -- SX1278 MOSI
#define SS    18  // GPIO18 -- SX1278 CS
#define RST   14  // GPIO14 -- SX1278 RESET
#define DIO0  26  // GPIO26 -- SX1278 IRQ(Interrupt Request)

// Pins used by OLED
#define OLED_DIR  0x3c
#define OLED_SDA  4
#define OLED_SCL  15
#define OLED_RST  16

#define BAND    915E6 // 433E6 for Asia, 866E6 for Europe or 915E6 for North America

SSD1306Wire display(OLED_DIR, OLED_SDA, OLED_SCL, GEOMETRY_64_32);

String LoRaData;

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  Serial.println("LoRa receiver");
  Serial.println(__FILE__);

  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(50);
  digitalWrite(OLED_RST, HIGH);
  display.init();
  display.flipScreenVertically();
  display.clear();

  // SPI LoRa pins
  SPI.begin(SCK, MISO, MOSI, SS);
  // Setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(BAND)) {
    Serial.println("LoRa has failed");
    while (1);
  }
  Serial.println("LoRa has started");
  delay(2000);
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    Serial.print("Receiver packet '");
    display.drawString(0, 0, "RP");
    while (LoRa.available()) {
      LoRaData = LoRa.readString();
      Serial.print(LoRaData);
      display.drawString(20, 0, String(LoRaData));
    }
    int rssi = LoRa.packetRssi();
    Serial.print("' with RSSI ");
    display.drawString(0, 12, "RSSI");
    Serial.print(rssi);
    display.drawString(30, 12, String(rssi));
    Serial.println("");
    display.display();
    display.clear();
  }
}
