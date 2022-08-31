/*
 * Archivo: Led_RGB.ino
 * Autor: Cristobal Cuevas
 * Comentarios: Led RGB with classes
 * Fecha: 26-02-2021
 *
 */
#include "ledRGB.h"

ledRGB miLed(6,5,3);
void setup() {
}

void loop() {
  miLed.randomColor();
  delay(1000);
}
