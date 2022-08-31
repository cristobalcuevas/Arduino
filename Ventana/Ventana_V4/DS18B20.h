#include <OneWire.h>
#include <DallasTemperature.h>
OneWire CamaraArriba(pinCamaraArriba);
OneWire CamaraAbajo(pinCamaraAbajo);
DallasTemperature camaraArriba(&CamaraArriba);
DallasTemperature camaraAbajo(&CamaraAbajo);
struct ds18b20 {
  float temperatura;
};
ds18b20 camaraSuperior = {0};
ds18b20 camaraInferior = {0};
void DS18B20_init() {
  camaraArriba.begin();
  camaraAbajo.begin();
}
float getUpTemp() {
  camaraArriba.requestTemperatures();
  camaraSuperior.temperatura = camaraArriba.getTempCByIndex(0);
  camaraSuperior.temperatura = camaraSuperior.temperatura == -127 ? 0 : camaraSuperior.temperatura;
  return camaraSuperior.temperatura;
}
float getDownTemp() {
  camaraAbajo.requestTemperatures();
  camaraInferior.temperatura = camaraAbajo.getTempCByIndex(0);
  camaraInferior.temperatura = camaraInferior.temperatura == -127 ? 0 : camaraInferior.temperatura;
  return camaraInferior.temperatura;
}
