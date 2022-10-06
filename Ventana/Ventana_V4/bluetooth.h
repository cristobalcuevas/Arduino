/* Includes ----------------------------------------------------------------*/
#include <BluetoothSerial.h>
/* Instances ----------------------------------------------------------------*/
BluetoothSerial SerialBT;
/* Functions -----------------------------------------------------------------*/
void BT_init() {
  SerialBT.begin("ESP32-4");
  Serial.println("El dispositivo se ha iniciado, ahora puedes emparejarlo");
}
void printDataBT(dht* dht11, servo* persiana, servo* ventila, vent* ventana, ds18b20* camaraSuperior, ds18b20* camaraInferior, uint16_t *luzDeseada, uint8_t *temperaturaDeseada) {
  String datosBT =  String(dht11->temp) + "_" +
                    String(dht11->hum) + "_" +
                    String(persiana->state) + "_" +
                    String(ventila->state) + "_" +
                    String(ventana->windowMode) + "_" +
                    String(ventana->ldr) + "_" +
                    String(camaraSuperior->temp) + "_" +
                    String(camaraInferior->temp) + "_" +
                    String(*luzDeseada) + "_" +
                    String(*temperaturaDeseada) + "\r\n";
  SerialBT.print(datosBT);
}
