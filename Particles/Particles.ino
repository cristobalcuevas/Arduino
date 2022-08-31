#include <SoftwareSerial.h>     // Libreria para utilizar otros pines para comunicacion serial

SoftwareSerial pmsSerial(2, 3); // Pines comunicacion serial

void setup() {
  Serial.begin(115200);   // Configuracion puerto serial
  pmsSerial.begin(9600);  // Baud rate del sensor es 9600
}

struct pms5003data {
  uint16_t framelen;
  uint16_t pm10_standard, pm25_standard, pm100_standard;
  uint16_t pm10_env, pm25_env, pm100_env;
  uint16_t particles_03um, particles_05um, particles_10um, particles_25um, particles_50um, particles_100um;
  uint16_t unused;
  uint16_t checksum;
};

struct pms5003data data;

void loop() {
  if (readPMSdata(&pmsSerial)) {
    Serial.println("---------------------------------------------------------");
    Serial.println("Unidades de concentración (estándar)");
    Serial.print("PM 1.0: "); Serial.print(data.pm10_standard);
    Serial.print("\t\tPM 2.5: "); Serial.print(data.pm25_standard);
    Serial.print("\t\tPM 10: "); Serial.println(data.pm100_standard);
    Serial.println("---------------------------------------------------------");
    Serial.println("Unidades de concentración (ambientales)");
    Serial.print("PM 1.0: "); Serial.print(data.pm10_env);
    Serial.print("\t\tPM 2.5: "); Serial.print(data.pm25_env);
    Serial.print("\t\tPM 10: "); Serial.println(data.pm100_env);
    Serial.println("---------------------------------------------------------");
    Serial.println("Partículas en el aire");
    Serial.print("Partículas > 0.3um  / 0.1L aire: "); Serial.println(data.particles_03um);
    Serial.print("Partículas > 0.5um  / 0.1L aire: "); Serial.println(data.particles_05um);
    Serial.print("Partículas > 1.0um  / 0.1L aire: "); Serial.println(data.particles_10um);
    Serial.print("Partículas > 2.5um  / 0.1L aire: "); Serial.println(data.particles_25um);
    Serial.print("Partículas > 5.0um  / 0.1L aire: "); Serial.println(data.particles_50um);
    Serial.print("Partículas > 10.0um / 0.1L aire: "); Serial.println(data.particles_100um);
  }
}
// Funcion que devuelve true o false al leer
boolean readPMSdata(Stream *s) {

  //Revisa si comunicacion serial no esta disponible
  if (!s->available()) {
    return false;
  }

  // Leer un byte a la vez hasta que lleguemos al byte de inicio especial '0x42'
  if (s->peek() != 0x42) {
    s->read();
    return false;
  }
  // Ahora lee los 32 bytes
  if (s->available() < 32) {
    return false;
  }

  uint8_t buffer[32];
  uint16_t sum = 0;
  s->readBytes(buffer, 32);

  // Obtener checksum listo
  for (uint8_t i = 0; i < 30; i++) {
    sum += buffer[i];
  }

  // Se acomodan los datos para que funcione en todas las plataformas
  uint16_t buffer_u16[15];
  for (uint8_t i = 0; i < 15; i++) {
    buffer_u16[i] = buffer[2 + i * 2 + 1];
    buffer_u16[i] += (buffer[2 + i * 2] << 8);
  }

  // Agregar datos obtenidos a estructura
  memcpy((void *)&data, (void *)buffer_u16, 30);

  // Verificacion de checksum
  if (sum != data.checksum) {
    Serial.println("Checksum failure");
    return false;
  }

  // Si todo funciono devuelve true
  return true;
}
