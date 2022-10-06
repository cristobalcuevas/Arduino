#include <Servo.h>

#define ARDUINO

Servo servo;

#ifdef ESP32
uint8_t pinValvula = 13, pinServo = 12, pinKuka = 2;
#endif /* ESP32 */

#ifdef ARDUINO
uint8_t pinValvula = 5, pinServo = 6, pinKuka = 7;
#endif /* ARDUINO */

bool valor;

void setup() {
  pinMode(pinKuka, INPUT_PULLUP);
  pinMode(pinValvula, OUTPUT);
  servo.attach(pinServo);
  servo.write(0);
}
void loop() {
  valor = digitalRead(pinKuka);
  if (valor == true) {
    digitalWrite(pinValvula, false);
    servo.write(0);
  }
  else if (valor == false) {
    digitalWrite(pinValvula, true);
    servo.write(180);
  }
}
