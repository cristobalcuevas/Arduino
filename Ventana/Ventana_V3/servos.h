#include <Servo.h>

Servo servoPersiana;
Servo servoVentila;

void initServos() {
  servoPersiana.attach(pinPersiana);
  servoVentila.attach(pinVentila);
}
void cerrarPersiana() {
  estadoPersiana = false;
  servoPersiana.write(servoPersianaCerrada);
}
void abrirPersiana() {
  estadoPersiana = true;
  servoPersiana.write(servoPersianaAbierta);
}
void cerrarVentila() {
  estadoVentila = false;
  servoVentila.write(servoVentilaCerrada);
}
void abrirVentila() {
  estadoVentila = true;
  servoVentila.write(servoVentilaAbierta);
}
