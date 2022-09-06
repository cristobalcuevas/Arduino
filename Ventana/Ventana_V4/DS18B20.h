#define ARRIBA 0
#define ABAJO 1

struct ds18b20 {
  const uint8_t pin;
  float temperatura;
};
ds18b20 camaraSuperior = {27, 0}; // TEMPERATURA 2
ds18b20 camaraInferior = {26, 0};  // TEMPERATURA 1

#include <OneWire.h>
#include <DallasTemperature.h>

OneWire CamaraArriba(camaraSuperior.pin);
OneWire CamaraAbajo(camaraInferior.pin);
DallasTemperature camaraArriba(&CamaraArriba);
DallasTemperature camaraAbajo(&CamaraAbajo);

void DS18B20_init() {
  camaraArriba.begin();
  camaraAbajo.begin();
}

float getDS18B20(bool positionSensor) {
  if (positionSensor == ARRIBA) {
    camaraArriba.requestTemperatures();
    camaraSuperior.temperatura = camaraArriba.getTempCByIndex(0);
    camaraSuperior.temperatura = camaraSuperior.temperatura == -127 ? 0 : camaraSuperior.temperatura;
    return camaraSuperior.temperatura;
  }
  else if (positionSensor == ABAJO) {
    camaraAbajo.requestTemperatures();
    camaraInferior.temperatura = camaraAbajo.getTempCByIndex(0);
    camaraInferior.temperatura = camaraInferior.temperatura == -127 ? 0 : camaraInferior.temperatura;
    return camaraInferior.temperatura;
  }
}
