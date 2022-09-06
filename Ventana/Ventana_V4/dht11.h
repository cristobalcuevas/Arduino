#define DHTtype DHT11
struct dhtSensor {
  const uint8_t pin;
  float temp;
  float hum;
};
dhtSensor dhtSensor = {15, 0, 0};

#include <DHT.h>

DHT dht(dhtSensor.pin, DHTtype);

void DHT_init()
{
  dht.begin();
}

float getTempe()
{
  dhtSensor.temp = dht.readTemperature();
  dhtSensor.temp = isnan(dhtSensor.temp) ? 0 : dhtSensor.temp;
  return dhtSensor.temp;
}

float getHumi()
{
  dhtSensor.hum = dht.readHumidity();
  dhtSensor.hum = isnan(dhtSensor.hum) ? 0 : dhtSensor.hum;
  return dhtSensor.hum;
}
