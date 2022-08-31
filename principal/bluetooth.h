#ifndef bluetooth_h
#define bluetooth_h

#include <Arduino.h>

class bt {
  private:
  public:
    bt();
    void begin(void);
    void printDataBT(String dataMessage);
};

#endif
