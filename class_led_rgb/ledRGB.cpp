#include "ledRGB.h"

ledRGB::ledRGB(byte pinRed, byte pinGreen, byte pinBlue){
  _pinRed   =   pinRed;
  _pinGreen =   pinGreen;
  _pinBlue  =   pinBlue;

  pinMode(_pinRed, OUTPUT);
  pinMode(_pinGreen, OUTPUT);
  pinMode(_pinBlue, OUTPUT);
  
  digitalWrite(_pinRed, LOW);
  digitalWrite(_pinGreen, LOW);
  digitalWrite(_pinBlue, LOW);
}

void ledRGB::setColor(byte red, byte green, byte blue){
  digitalWrite(_pinRed, red);
  digitalWrite(_pinGreen,green);
  digitalWrite(_pinBlue, blue);
}
void ledRGB::randomColor(){
  digitalWrite(_pinRed, random(0,2));
  digitalWrite(_pinGreen, random(0,2));
  digitalWrite(_pinBlue, random(0,2));
}
