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
