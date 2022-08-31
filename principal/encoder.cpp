#include "encoder.h"

// Variables para debouncing
volatile long timeCounter = 0;
const uint8_t timeThreshold = 5;

Encoder::Encoder(uint8_t pinA, uint8_t pinB){ 
  _pinA = pinA;
  _pinB = pinB;
}
void Encoder::begin(void) {
  pinMode(_pinA, INPUT_PULLUP);
  pinMode(_pinB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(_pinA), EncoderA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(_pinB), EncoderB, CHANGE);
}
void Encoder::EncoderA(void) {
  if (micros() > timeCounter + timeThreshold) {
    (digitalRead(_pinA) == digitalRead(_pinB)) ? ISRCounter++ : ISRCounter--;
    timeCounter = micros();
  }
}
void Encoder::EncoderB(void) {
  if (micros() > timeCounter + timeThreshold) {
    digitalRead(_pinA) != digitalRead(_pinB) ? ISRCounter++ : ISRCounter--;
    timeCounter = micros();
  }
}
String Encoder::distanceCalculator(void) {
  float perimeter = PI * diameter;
  float distance = perimeter / 360;
  float totalDistance = counter * distance;
  String dataMessage = pointTocomma(totalDistance);
  return dataMessage;
}
String Encoder::pointTocomma(float number) {
  int ival = (int)number;
  int frac = (number - ival) * 100;
  String dataMessage = String(ival) + "," + String(frac);
  return dataMessage;
}
