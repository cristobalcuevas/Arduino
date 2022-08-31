#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

void initBT() {
  SerialBT.begin("ESP32-2");
  Serial.println("El dispositivo se ha iniciado, ahora puedes emparejarlo");
}
void printDataBT(String dataMessage) {
  SerialBT.print(dataMessage);
}
