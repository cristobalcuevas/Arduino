/* Includes ------------------------------------------------------------------*/
#include <Servo.h>
/* Structures ----------------------------------------------------------------*/
servo persiana = {
  .pin = 14,
  .state = true,
  .degreesOpen = 120,
  .degreesClosed = 170
};
servo ventila = {
  .pin = 13,
  .state = true,
  .degreesOpen = 35,
  .degreesClosed = 5
};
/* Instances -----------------------------------------------------------------*/
Servo servoPersiana;
Servo servoVentila;
/* Functions -----------------------------------------------------------------*/
void servo_init() {
  servoPersiana.attach(persiana.pin);
  servoVentila.attach(ventila.pin);
}
void persianaState(uint8_t state) {
  persiana.state = state;
  persiana.state ? servoPersiana.write(persiana.degreesOpen) : servoPersiana.write(persiana.degreesClosed);
}
void ventilaState(uint8_t state) {
  ventila.state = state;
  ventila.state ? servoVentila.write(ventila.degreesOpen) : servoVentila.write(ventila.degreesClosed);
}
