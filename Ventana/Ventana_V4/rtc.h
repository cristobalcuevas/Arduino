/* Includes ------------------------------------------------------------------*/
#include <RTClib.h>
/* Instances -----------------------------------------------------------------*/
RTC_DS1307 DS1307_RTC;
/* Functions -----------------------------------------------------------------*/
void RTC_init() {
  Serial.println(!DS1307_RTC.begin() ? "RTC no encontrado" : "RTC encontrado");
  Serial.println(!DS1307_RTC.isrunning() ? "RTC no funciona" : "RTC funcionando");
  DS1307_RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
  Serial.flush();
}
String getDate() {
  DateTime currentDateTime = DS1307_RTC.now();
  char timeStamp[] = "DD/MM/YYYY, hh:mm:ss";
  String dateTime = currentDateTime.toString(timeStamp);
  return dateTime;
}
