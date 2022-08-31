/*
  Cristóbal Cuevas Lagos ~ 30-06-2022
  Envío de estos datos a traves de conexion bluetooth
*/
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth no esta activado, abrir 'menuconfig' y activarlo.
#endif

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  checkBT();
  SerialBT.register_callback(callback_function);
}

void loop() {
  SerialBT.println("prueba");
  delay(5000);
}


void checkBT() {
  // Revisar si bluetooth ha iniciado
  Serial.println(!SerialBT.begin("BT001") ? "Error al inicializar el bluetooth" : "Bluetooth iniciado");
}

// Funcion para revisar conexion y desconexion de dispositivo bluetooth
void callback_function(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
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
