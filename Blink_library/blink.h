#ifndef blink_h
#define blink_h
 
#include <Arduino.h>
 
#define ON true
#define OFF false
 
class Blink
{
public:
  Blink(int pin);
  void blink(bool value);
  void blink(bool value, int blinkLength);
  void blink(bool value, int blinkLength, int blinkLoops);
private:
  uint8_t pinNumber;
};
 
#endif
