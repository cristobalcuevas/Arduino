/*
  Cristóbal Cuevas Lagos ~ 30-06-2022
  Lectura de fecha y hora de RTC
*/
#include "RTClib.h"

RTC_DS1307 rtc;

void setup() {
  Serial.begin(115200);
  checkRTC();
}

void loop() {
  printDate();
  delay(3000);
}

void checkRTC() {
  Serial.println(!rtc.begin() ? "No se encontro RTC" : "RTC iniciado");
  Serial.println(!rtc.isrunning() ? "Error al inicializar el RTC" : "RTC corriendo");
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  Serial.flush();
}

void printDate() {
  DateTime now = rtc.now();
  char buf[] = "DD-MM-YYYY hh:mm:ss";
  Serial.println(now.toString(buf));
}
