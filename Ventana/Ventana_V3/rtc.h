#include <RTClib.h>

RTC_DS1307 rtc;

void initRTC() {
  if (!rtc.begin()) {
    Serial.println("No se puede encontrar el RTC");
    Serial.flush();
  }
  if (!rtc.isrunning()) {
    Serial.println("El RTC no está corriendo, ¡pongamos la hora!");
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

String getDate() {
  DateTime now = rtc.now();
  char buf[] = "DD/MM/YYYY, hh:mm:ss";
  String fechaHora = String(now.toString(buf));
  return fechaHora;
}
