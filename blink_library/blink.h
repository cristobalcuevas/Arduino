#ifndef blink_h
#define blink_h
 
#include <Arduino.h>
 
#define ON true
#define OFF false
 
class Blink
{
public:
  Blink(int pin);  //Constructor. attach pin to blink
  void blink(bool value);  //enable blinking with 1s duration
  void blink(bool value, int blinkLength);   //enable blinking with blink duration
  void blink(bool value, int blinkLength, int blinkLoops);  //enable blinking with blink duration and number of loops
private:
  uint8_t pinNumber;
};
 
#endif
