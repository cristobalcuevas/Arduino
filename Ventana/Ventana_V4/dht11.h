/* Includes ------------------------------------------------------------------*/
#include <DHT.h>
/* Structures ----------------------------------------------------------------*/
dht dht11 = {
  .pin = 15,
  .temp = 0,
  .hum = 0
};
/* Instances -----------------------------------------------------------------*/
DHT dhtSensor(dht11.pin, DHT11);
/* Functions -----------------------------------------------------------------*/
void DHT_init() {
  dhtSensor.begin();
}
float getTempe() {
  dht11.temp = dhtSensor.readTemperature();
  dht11.temp = isnan(dht11.temp) ? 0 : dht11.temp;
  return dht11.temp;
}
float getHumi() {
  dht11.hum = dhtSensor.readHumidity();
  dht11.hum = isnan(dht11.hum) ? 0 : dht11.hum;
  return dht11.hum;
}
