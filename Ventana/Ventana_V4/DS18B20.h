/* Includes ------------------------------------------------------------------*/
#include <OneWire.h>
#include <DallasTemperature.h>
/* Structures ----------------------------------------------------------------*/
ds18b20 camaraSuperior = {  // TEMPERATURA 2
  .pin = 27,
  .temp = 0
};
ds18b20 camaraInferior = {  // TEMPERATURA 1
  .pin = 26,
  .temp = 0
};
/* Instances -----------------------------------------------------------------*/
OneWire CamaraArriba(camaraSuperior.pin);
OneWire CamaraAbajo(camaraInferior.pin);
DallasTemperature camaraArriba(&CamaraArriba);
DallasTemperature camaraAbajo(&CamaraAbajo);
/* Functions -----------------------------------------------------------------*/
void DS18B20_init() {
  camaraArriba.begin();
  camaraAbajo.begin();
}

float getAvgTemp() {
  camaraArriba.requestTemperatures();
  camaraAbajo.requestTemperatures();

  camaraSuperior.temp = camaraArriba.getTempCByIndex(0);
  camaraInferior.temp = camaraAbajo.getTempCByIndex(0);

  camaraSuperior.temp = camaraSuperior.temp == -127 ? 0 : camaraSuperior.temp;
  camaraInferior.temp = camaraInferior.temp == -127 ? 0 : camaraInferior.temp;

  return ((camaraSuperior.temp + camaraInferior.temp) / 2);
}
