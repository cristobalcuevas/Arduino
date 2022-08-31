/*
 * Archivo: Blink_millis.ino
 * Autor: Cristobal Cuevas
 * Comentarios: Blink led with millis function
 * Fecha: 07-07-2022
 *
 */
const byte pinLed = 13;
boolean estadoLed = false;
unsigned long tiempo = 0;

void setup() {
 pinMode(pinLed, OUTPUT);
 digitalWrite(pinLed, estadoLed);
}

void loop() {
  if(millis() - tiempo >= 500){
    estadoLed = !estadoLed;
    digitalWrite(pinLed, estadoLed);
    tiempo = millis();
  }
}
