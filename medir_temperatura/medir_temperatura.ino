#include <DHT.h>
const int sensor = 2;
int temp = 0;
int hum = 0;

DHT dht(sensor,DHT11);

void setup(){
  Serial.begin(9600);
  dht.begin();
}

void loop(){
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.print("°C");
  Serial.println();
  Serial.print("Humedad: ");
  Serial.print(hum);
  Serial.print("%");
  Serial.println();
  delay(1000);
}
