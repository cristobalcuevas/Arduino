#ifndef encoder_h
#define encoder_h

#include <Arduino.h>

class Encoder {
  private:
    volatile long ISRCounter = 0;
    long contador = 0;
    uint8_t _pinA, _pinB;

  public:
    Encoder(uint8_t pinA, uint8_t pinB);
    void begin(void);
    void EncoderA(void);
    void EncoderB(void);
    float distanceCalculator(void);
    String pointTocomma(float number);
};

#endif
