/*********************************** LIBRERIAS ***********************************/
#include "const_var.h"
#include "DS18B20.h"
#include "bluetooth.h"
#include "dht.h"
#include "microsd.h"
#include "rtc.h"
#include "servos.h"
#include "ldr.h"
#include "imprimirDatos.h"
/************************************* SETUP *************************************/
void setup() {
  Serial.begin(115200);
  initSD();
  initRTC();
  initBT();
  initDS18B20();
  initDHT();
  initServos();
}
/************************************* LOOP **************************************/
void loop() {
  // OBTENCION DE DATOS
  fechaFormateada = getDate();
  temperaturaInterior = getTempe();
  humedadInterior = getHumi();
  temperaturaCamaraArriba = getDS18B20Arriba();
  temperaturaCamaraAbajo = getDS18B20Abajo();
  temperaturaCamara = (temperaturaCamaraArriba + temperaturaCamaraAbajo) / 2;
  luz = getLDR(sensorLuz);
  datosSD = String(fechaFormateada) + " " + String(temperaturaInterior) + " " + String(humedadInterior) + " " + String(estadoPersiana) + " " + String(estadoVentila) + " " + String(modoVentana) + " " + String(luz) + "_" + String(temperaturaCamaraArriba) + " " + String(temperaturaCamaraAbajo) + " " + String(setLuz) + " " + String(temperaturaInteriorDeseada) + "\r\n";
  datosBT = String(temperaturaInterior) + "_" + String(humedadInterior) + "_" + String(estadoPersiana) + "_" + String(estadoVentila) + "_" + String(modoVentana) + "_" + String(luz) + "_" + String(temperaturaCamaraArriba) + "_" + String(temperaturaCamaraAbajo) + "_" + String(setLuz) + "\r\n";
  // REVISION DE MODO DE LA VENTANA
  // MODO AUTOMATICO
  if (modoVentana == 10) {
    if (luz >= setLuz) {
      abrirPersiana();
    }
    else if (luz < setLuz) {
      cerrarPersiana();
    }
    if (temperaturaCamara > temperaturaInteriorDeseada || temperaturaInterior < temperaturaInteriorDeseada || temperaturaCamara > temperaturaInterior) {
      abrirVentila();
    } else {
      cerrarVentila();
    }
  }
  // MODO MANUAL
  else if (modoVentana == 20) {
  }
  // VERIFICAR BLUETOOTH DISPONIBLE Y LEER COMANDO
  while (SerialBT.available()) {
    comando = SerialBT.readString();
  }
  // REALIZAR ACCION DE ACUERDO AL COMANDO LEIDO
  if (comando == "4") {
    modoVentana = 10;
    // MODO AUTOMATICO

  }
  if (comando == "5") {
    modoVentana = 20;
    // MODO MANUAL
  }
  if (comando == "1" && modoVentana == 20) {
    estadoPersiana = true;
    abrirPersiana();
  }
  else if (comando == "0" && modoVentana == 20) {
    estadoPersiana = false;
    cerrarPersiana();
  }
  else if (comando == "2" && modoVentana == 20) {
    estadoVentila = true;
    abrirVentila();
  }
  else if (comando == "3" && modoVentana == 20) {
    estadoVentila = false;
    cerrarVentila();
  }
  printDataSerial(modoVentana, fechaFormateada, temperaturaInterior, humedadInterior, temperaturaCamaraArriba, temperaturaCamaraAbajo, luz, estadoVentila, estadoPersiana);
  printDataBT(datosBT);
  logSDCard(datosSD);
  delay(2000);
}
