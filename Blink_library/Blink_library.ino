/*
 * Archivo: Blink_library.ino
 * Autor: Cristobal Cuevas
 * Comentarios: Blink led with a library :)
 * Fecha: 07-07-2022
 *
 */
#include "blink.h"
Blink led (13);
void setup() {}
void loop() {
  led.blink(ON, 1000);
}
