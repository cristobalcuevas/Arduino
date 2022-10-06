/*
 * Archivo: .ino
 * Autor: Cristobal Cuevas
 * Comentarios: Blink led with timer
 * Fecha: 07-07-2022
 *
 */

#include <Arduino.h>

#define LED_PIN 13

void setup() {
  pinMode(LED_PIN, OUTPUT);
  //Registros
  TCCR1A = 0; // Limpiar registro y trabajr en modo normal
  
  TCCR1B = _BV(WGM12); // WGM12 en 1 para usar modo CTC
  TCCR1B |= _BV(CS12)|_BV(CS10); // CS12 y CS10 en 1 para usar prescaler a 1024
  
  TIMSK1 |= _BV(OCIE1A); // enable Timer1 COMPA interrupt   Timer/Counter1 compare match A
  
  OCR1A = 7812; // set value for Fx=1Hz, OCRnx = (16Mhz/(Fx * 2 * 1024) + 1)
  
  interrupts(); // Activar interrupciones globales
}

void loop(){
  // No hace nada
}

ISR(TIMER1_COMPA_vect){
  digitalWrite(LED_PIN, !digitalRead(LED_PIN)); // Toggle LED pin -> led = ~led
}
