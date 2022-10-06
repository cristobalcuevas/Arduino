/* Variables -----------------------------------------------------------------*/
uint8_t temperaturaCamara = 0;
uint8_t temperaturaDeseada = 25;
uint16_t luzDeseada = 2040;
/* Structures ----------------------------------------------------------------*/
struct vent {
  uint8_t   windowMode;
  String    dateFormatted;
  float     tempIndoor;
  float     humIndoor;
  float     avgTemp;
  uint16_t  ldr;
};

struct servo {
  const uint8_t pin;
  uint8_t state;
  uint8_t degreesOpen;
  uint8_t degreesClosed;
};
struct dht {
  const uint8_t pin;
  float temp;
  float hum;
};
struct ds18b20 {
  const uint8_t pin;
  float temp;
};
