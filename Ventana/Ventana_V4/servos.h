#include <Servo.h>

Servo servoPersiana;
Servo servoVentila;

struct servo {
  const uint8_t pin;
  bool estado;
  uint8_t gradosCerrada;
  uint8_t gradosAbierta;
};

servo persiana = {14, true, 0, 70}; // SERVO 1
servo ventila = {13, true, 35, 5};  // SERVO 2

void servo_init()
{
  servoPersiana.attach(persiana.pin);
  servoVentila.attach(ventila.pin);
}

void estadoPersiana(bool estado)
{
  persiana.estado = estado;
  persiana.estado ? servoPersiana.write(persiana.gradosAbierta) : servoPersiana.write(persiana.gradosCerrada);
}

void estadoVentila(bool estado)
{
  ventila.estado = estado;
  ventila.estado ? servoVentila.write(ventila.gradosAbierta) : servoVentila.write(ventila.gradosCerrada);
}
