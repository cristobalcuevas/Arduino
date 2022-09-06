#include <RTClib.h>

RTC_DS1307 rtc;

void RTC_init()
{
  Serial.println(!rtc.begin() ? "RTC no encontrado" : "RTC encontrado");
  Serial.flush();
  Serial.println(!rtc.isrunning() ? "RTC no funciona" : "RTC funcionando");
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

String getDate()
{
  DateTime now = rtc.now();
  char timeStamp[] = "DD/MM/YYYY, hh:mm:ss";
  String dateTime = now.toString(timeStamp);
  return dateTime;
}
