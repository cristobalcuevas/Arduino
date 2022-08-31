#include "BluetoothSerial.h"

BluetoothSerial BT; // Objeto Bluetooth

void setup() {
  Serial.begin(115200);
  BT.begin("T-Beam"); // Nombre de su dispositivo Bluetooth y en modo esclavo
}

void loop() {
  if (Serial.available()) {
    BT.write(Serial.read());
  }
  if (BT.available()) {
    Serial.write(BT.read());
  }
  delay(20);
}
