/* Includes ----------------------------------------------------------------*/
#include "def.h"
#include "DS18B20.h"
#include "servo.h"
#include "dht11.h"
#include "ldr.h"
#include "rtc.h"
#include "bluetooth.h"
#include "microsd.h"
#include "print_data.h"
/* Structures ----------------------------------------------------------------*/
vent ventana = {
  .windowMode = 10,
  .dateFormatted = "",
  .tempIndoor = 0,
  .humIndoor = 0,
  .avgTemp = 0,
  .ldr = 0
};
/* Setup -------------------------------------------------------------------*/
void setup() {
  Serial.begin(115200);
  SD_init();
  RTC_init();
  BT_init();
  DS18B20_init();
  DHT_init();
  servo_init();
}
/* Loop -------------------------------------------------------------------*/
void loop() {
  /* Obtención de datos ---------------------------------------------------*/
  ventana.dateFormatted = getDate();
  ventana.tempIndoor =    getTempe();
  ventana.humIndoor =     getHumi();
  ventana.avgTemp =       getAvgTemp();
  ventana.ldr =           getLDR();
  /* Modo automático por defecto ------------------------------------------*/
  if (ventana.windowMode == 10) {
    if (ventana.ldr >= luzDeseada) {
      persianaState(true);
    }
    else if (ventana.ldr < luzDeseada) {
      persianaState(false);
    }
    if (ventana.avgTemp > temperaturaDeseada || ventana.tempIndoor < temperaturaDeseada || ventana.avgTemp > ventana.tempIndoor) {
      ventilaState(true);
    } else {
      ventilaState(false);
    }
  }
  String comando = "";
  while (SerialBT.available()) {
    comando = SerialBT.readString();
    comando.trim();
  }
  /* Modo automático app  --------------------------------------------------*/
  if (comando == "4") {
    ventana.windowMode = 10;
  }
  else if (comando == "5") {
    ventana.windowMode = 20;
  }
  else if (comando == "1" && ventana.windowMode == 20) {
    persianaState(true);
  }
  else if (comando == "0" && ventana.windowMode == 20) {
    persianaState(false);
  }
  else if (comando == "2" && ventana.windowMode == 20) {
    ventilaState(true);
  }
  else if (comando == "3" && ventana.windowMode == 20) {
    ventilaState(false);
  }
  printDataSerial(&dht11, &persiana, &ventila, &ventana, &camaraSuperior, &camaraInferior, &luzDeseada, &temperaturaDeseada);
  printDataBT(&dht11, &persiana, &ventila, &ventana, &camaraSuperior, &camaraInferior, &luzDeseada, &temperaturaDeseada);
  logSDCard(&dht11, &persiana, &ventila, &ventana, &camaraSuperior, &camaraInferior, &luzDeseada, &temperaturaDeseada);
  delay(2000);
}
