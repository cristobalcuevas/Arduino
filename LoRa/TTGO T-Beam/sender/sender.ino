// T-Beam Board
// Libraries for LoRa
#include <SPI.h>
#include <LoRa.h>

// Define the pins used by the LoRa transceiver module
#define SCK   5   // GPIO5  -- SX1278's SCK
#define MISO  19  // GPIO19 -- SX1278's MISO
#define MOSI  27  // GPIO27 -- SX1278's MOSI
#define SS    18  // GPIO18 -- SX1278's CS
#define RST   14  // GPIO14 -- SX1278's RESET
#define DIO0  26  // GPIO26 -- SX1278's IRQ(Interrupt Request)

// 433E6 for Asia
// 866E6 for Europe
// 915E6 for North America
#define BAND  915E6

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  // Agregar verificacion puerto serial
  Serial.println("LoRa sender");
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
  Serial.println("hola");
  LoRa.beginPacket();
  LoRa.print("hola");
  LoRa.endPacket();
  delay(2000);
}
