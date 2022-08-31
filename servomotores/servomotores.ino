#include <Servo.h>
Servo myservo1;
Servo myservo2;
int pos = 0;
void setup() {
  myservo1.attach(13);
  myservo2.attach(14);
}
void loop() {
  for (pos = 0; pos <= 180; pos += 1) {
    myservo1.write(pos);
    myservo2.write(pos);
    delay(15);
  }
  for (pos = 180; pos >= 0; pos -= 1) {
    myservo1.write(pos);
    myservo2.write(pos);
    delay(15);
  }
}
