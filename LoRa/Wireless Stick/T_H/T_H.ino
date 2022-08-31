#include "DHTesp.h"
#include "heltec.h"

DHTesp dht;

float currentTemp;
float currentHumidity;

void displayReadingsOnOled() {
  String temperatureDisplay = "T: " + (String)currentTemp +  "°C";
  String humidityDisplay = "H: " + (String)currentHumidity + "%";
  Heltec.display->clear();
  Heltec.display->drawString(0, 0, temperatureDisplay);
  Heltec.display->drawString(0, 12, humidityDisplay);
  Heltec.display->display();
}

void setup() {
  dht.setup(27, DHTesp::DHT22);
  currentTemp = dht.getTemperature();
  currentHumidity = dht.getHumidity();
  Heltec.begin(true /*DisplayEnable Enable*/, false /*Heltec.Heltec.Heltec.LoRa Disable*/, false /*Serial Enable*/);
  displayReadingsOnOled();
}

void loop() {
  float temperature = dht.getTemperature();
  float humidity = dht.getHumidity();
  if (temperature != currentTemp || humidity != currentHumidity) {
    currentTemp = temperature;
    currentHumidity = humidity;
    if (isnan(humidity) || isnan(temperature)) {
      currentTemp = 0;
      currentHumidity = 0;
    }
    displayReadingsOnOled();
  }
  delay(2000);
}
