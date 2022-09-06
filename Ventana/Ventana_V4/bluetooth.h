#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

void BT_init()
{
  SerialBT.begin("ESP32-2");
  Serial.println("El dispositivo se ha iniciado, ahora puedes emparejarlo");
}

void printDataBT(vent* ventana, servo* persiana, servo* ventila, uint8_t setLuz)
{
  String datosBT = String(ventana->temperaturaInterior) + "_" + String(ventana->humedadInterior) + "_" + String(persiana->estado) + "_" + String(ventila->estado) + "_" + String(ventana->modoVentana) + "_" + String(ventana->luz) + "_" + String(ventana->temperaturaCamaraArriba) + "_" + String(ventana->temperaturaCamaraAbajo) + "_" + String(setLuz) + "\r\n";
  SerialBT.print(datosBT);
}
