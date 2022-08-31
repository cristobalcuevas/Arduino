#include "Arduino.h"
#include "rtc.h"
#include "RTClib.h"

RTC_DS1307 rtc;

RTC::RTC(){ 
}

void RTC::begin(void) {
  rtc.begin();
  rtc.isrunning();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  Serial.flush();
}

String printDate(void) {
  DateTime now = rtc.now();
  char buf[] = "DD-MM-YYYY hh:mm:ss";
  String bufDate = String(now.toString(buf));
  return bufDate;
}
