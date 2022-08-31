#include <DHT.h>
DHT dht(pinDHT, DHTtype);
void DHT_init() {
  dht.begin();
}
float getTempe() {
  float temperatura = dht.readTemperature();
  temperatura = isnan(temperatura) ? 0 : temperatura;
  return temperatura;
}
float getHumi() {
  float humedad = dht.readHumidity();
  humedad = isnan(humedad) ? 0 : humedad;
  return humedad;
}
