/*
  Cristóbal Cuevas Lagos ~ 30-06-2022
  Envío de estos datos a traves de conexion bluetooth
*/
#include "BluetoothSerial.h"
#include "bluetooth.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth no esta activado, abrir 'menuconfig' y activarlo.
#endif

BT bt;

void setup() {
  Serial.begin(115200);
  SerialBT.register_callback(conexion_y_desconexion);
}

void loop() {
  bt.printText("prueba");
  delay(5000);
}


void checkBT() {
  // Revisar si bluetooth ha iniciado
  Serial.println(!SerialBT.begin("BT001") ? "Error al inicializar el bluetooth" : "Bluetooth iniciado");
}
