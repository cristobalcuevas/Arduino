#ifndef ledRGB_h
#define ledRGB_h

#include <Arduino.h>

class ledRGB{
  public:
    ledRGB(byte pinRed, byte pinGreen, byte pinBlue);
    void setColor(byte red, byte green, byte blue);
    void randomColor();
  private:
    byte _pinRed;
    byte _pinGreen;
    byte _pinBlue;
};

#endif
