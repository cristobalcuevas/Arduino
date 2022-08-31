#include <Arduino.h>
#include "bluetooth.h"
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void BT::BT() {
  Serial.println(!SerialBT.begin("BT001") ? "Error al inicializar el bluetooth" : "Bluetooth iniciado");
}
void BT::printText(char *texto) {
  SerialBT.print(texto);
}
// Funcion para revisar conexion y desconexion de dispositivo bluetooth
void conexion_y_desconexion(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
  if (event == ESP_SPP_SRV_OPEN_EVT ) {
    Serial.println("Cliente conectado");
    // Imprimir dirección MAC del dispositivo conectado
    for (int i = 0; i < 6; i++) {
      Serial.printf("%02X", param->srv_open.rem_bda[i]);
      if (i < 5) {
        Serial.print(":");
      }
    }
    Serial.println();
  }
  else if (event == ESP_SPP_CLOSE_EVT  ) {
    Serial.println("Cliente desconectado");
  }
}
