#include <RTClib.h>
RTC_DS1307 rtc;
void RTC_init() {
  Serial.print(!rtc.begin() ? "No se puede encontrar el RTC" : "Se encontro el RTC");
  Serial.flush();
  Serial.print(!rtc.isrunning() ? "El RTC no está corriendo" : "RTC corriendo");
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}
String getDate() {
  DateTime now = rtc.now();
  char timeStamp[] = "DD/MM/YYYY, hh:mm:ss";
  String dateTime = now.toString(timeStamp);
  return dateTime;
}
