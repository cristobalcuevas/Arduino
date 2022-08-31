// Heltec Wireless Stick
// Libraries para LoRa
#include <SPI.h>
#include <LoRa.h>

// Define los pines usados por modulo LoRa
#define SCK   5   // GPIO5  -- SX1278 SCK
#define MISO  19  // GPIO19 -- SX1278 MISO
#define MOSI  27  // GPIO27 -- SX1278 MOSI
#define SS    18  // GPIO18 -- SX1278 CS
#define RST   14  // GPIO14 -- SX1278 RESET
#define DIO0  26  // GPIO26 -- SX1278 IRQ(Interrupt Request)

#define BAND    915E6 // 433E6 para Asia, 866E6 para Europa o 915E6 para Norteamerica

String LoRaData;

void setup() {
  // Inicializa el Monitor Serial
  Serial.begin(115200);
  Serial.println("LoRa recibir");
  Serial.println(__FILE__);
  
  // Pines SPI LoRa
  SPI.begin(SCK, MISO, MOSI, SS);
  
  // Configuracion modulo LoRa
  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(BAND)) {
    Serial.println("LoRa ha fallado");
    while (1);
  }
  Serial.println("LoRa ha iniciado");
  delay(2000);
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    Serial.print("Paquete recibido '");
    while (LoRa.available()) {
      LoRaData = LoRa.readString();
      Serial.print(LoRaData);
    }
    int rssi = LoRa.packetRssi();
    Serial.print("' con RSSI ");
    Serial.print(rssi);
    Serial.println("");
  }
}
