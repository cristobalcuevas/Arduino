struct vent {
  uint8_t modoVentana = 10;
  String fechaFormateada = "";
  float temperaturaInterior = 0;
  float humedadInterior = 0;
  float temperaturaCamaraArriba = 0;
  float temperaturaCamaraAbajo = 0;
  uint8_t luz = 0;
};
vent ventana;
/*********************************** LIBRERIAS ***********************************/
#include "constantes.h"
#include "DS18B20.h"
#include "servos.h"
#include "bluetooth.h"
#include "dht11.h"
#include "microsd.h"
#include "rtc.h"
#include "ldr.h"
#include "imprimirDatos.h"

/************************************* SETUP *************************************/
void setup() {
  Serial.begin(115200);
  SD_init();
  RTC_init();
  BT_init();
  DS18B20_init();
  DHT_init();
  servo_init();
}
/************************************* LOOP **************************************/
void loop() {
  // OBTENCION DE DATOS
  ventana.fechaFormateada = getDate();
  ventana.temperaturaInterior = getTempe();
  ventana.humedadInterior = getHumi();
  ventana.temperaturaCamaraArriba = getUpTemp();
  ventana.temperaturaCamaraAbajo = getDownTemp();
  float temperaturaCamara = (ventana.temperaturaCamaraArriba + ventana.temperaturaCamaraAbajo) / 2;
  ventana.luz = getLDR(pinLDR);
  // REVISION DE MODO DE LA VENTANA
  // MODO AUTOMATICO
  if (ventana.modoVentana == 10) {
    if (ventana.luz >= setLuz) {
      estadoPersiana(true);
    }
    else if (ventana.luz < setLuz) {
      estadoPersiana(false);
    }
    if (temperaturaCamara > temperaturaInteriorDeseada || ventana.temperaturaInterior < temperaturaInteriorDeseada || temperaturaCamara > ventana.temperaturaInterior) {
      estadoVentila(true);
    } else {
      estadoVentila(false);
    }
  }
  // MODO MANUAL

  else if (ventana.modoVentana == 20) {
  }
  // VERIFICAR BLUETOOTH DISPONIBLE Y LEER COMANDO
  String comando = "";
  while (SerialBT.available()) {
    comando = SerialBT.readString();
    comando.trim();
  }
  // REALIZAR ACCION DE ACUERDO AL COMANDO LEIDO
  // MODO AUTOMATICO
  if (comando == "4") {
    ventana.modoVentana = 10;
  }
  // MODO MANUAL
  if (comando == "5") {
    ventana.modoVentana = 20;
  }
  if (comando == "1" && ventana.modoVentana == 20) {
    estadoPersiana(true);
  }
  else if (comando == "0" && ventana.modoVentana == 20) {
    estadoPersiana(false);
  }
  else if (comando == "2" && ventana.modoVentana == 20) {
    estadoVentila(true);
  }
  else if (comando == "3" && ventana.modoVentana == 20) {
    estadoVentila(false);
  }
  printDataSerial(&ventana);
  printDataBT(&ventana, &persiana, &ventila, setLuz);
  logSDCard(&ventana, &persiana, &ventila, setLuz, temperaturaInteriorDeseada);
  delay(5000);
}
