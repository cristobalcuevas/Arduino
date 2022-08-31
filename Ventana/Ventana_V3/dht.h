#include <DHT.h>

DHT dht(DHTpin, DHTtype);

void initDHT() {
  dht.begin();
}
float getTempe() {
  float temperatura = dht.readTemperature();
  if (isnan(temperatura)) {
    temperatura = 0;
  }
  return temperatura;
}
float getHumi() {
  float humedad = dht.readHumidity();
  if (isnan(humedad)) {
    humedad = 0;
  }
  return humedad;
}
