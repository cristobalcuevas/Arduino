#include <OneWire.h>
#include <DallasTemperature.h>

OneWire CamaraArriba(pinCamaraArriba);
OneWire CamaraAbajo(pinCamaraAbajo);
DallasTemperature camaraArriba(&CamaraArriba);
DallasTemperature camaraAbajo(&CamaraAbajo);

void initDS18B20() {
  camaraArriba.begin();
  camaraAbajo.begin();
}
float getDS18B20Arriba() {
  camaraArriba.requestTemperatures();
  float tempArriba = camaraArriba.getTempCByIndex(0);
  if (tempArriba == -127) {
    tempArriba = 0;
  }
  return tempArriba;
}
float getDS18B20Abajo() {
  camaraAbajo.requestTemperatures();
  float tempAbajo = camaraAbajo.getTempCByIndex(0);
  if (tempAbajo == -127) {
    tempAbajo = 0;
  }
  return tempAbajo;
}
