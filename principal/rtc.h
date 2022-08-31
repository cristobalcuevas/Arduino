#ifndef rtc_h
#define rtc_h

#include <Arduino.h>

class RTC {
  private:
  public:
    RTC();
    void begin(void);
    String printDate(void);
};
#endif
