/* 
 * Archivo: 7_segmentos.ino
 * Autor: Cristobal Cuevas
 * Comentarios: Mostrar conversión del ADC por un display de 7 segmentos de 4 digitos (0 a 1023)
 * Fecha: 26-04-2021
 * 
 * A0 -> Potenciometro
 * 0 -> A with resistor
 * 1 -> B with resistor
 * 2 -> C with resistor
 * 3 -> D with resistor
 * 4 -> E with resistor
 * 5 -> F with resistor
 * 6 -> G with resistor
 * 7 -> DP
 * 8 -> D1
 * 9 -> D2
 * 10 -> D3
 * 11 -> D4
 * 
 */

/********************* VARIABLES ********************/
byte current_digit;
int  value;
bool converted;
/*********************** SETUP **********************/
void setup()
{
  DDRD = 0b01111111; // Configurar pines (0 al 6) puerto D como salidas
  DDRB = 0b00001111; // Configurar pines (8 al 11) puerto B como salidas
  disp_off();
  adc_setup();
  timer1_setup();
}
/******************* FUNCION ISR ********************/
ISR(TIMER1_OVF_vect)
{
  disp_off();
  switch (current_digit) {
    case 1: // Calcular primer número y encender digito 1
      disp(value / 1000);
      PORTB &= ~ bit(0);
      break;
    case 2: // Calcular segundo número y encender digito 4
      disp( (value / 100) % 10);
      PORTB &= ~ bit(1);
      break;
    case 3: // Calcular tercer número y encender digito 3
      disp( (value / 10) % 10);
      PORTB &= ~ bit(2);
      break;
    case 4: // Calcular cuarto número y encender digito 4
      disp(value % 10);
      PORTB &= ~ bit(3);
  }
  current_digit = (current_digit % 4) + 1;
}
/*********************** LOOP ***********************/
void loop()
{
  if (converted) {
    ADCSRA |= bit(ADSC);  // Conversión analoga a digital
    converted = false;
  }
  if (bit_is_clear(ADCSRA, ADSC)) {
    value = ADC;          // Cuando ADSC = 0 leer resultado
    converted = true;
    delay (100);          // Tiempo para ver la salida
  }
}
/****************** NUMEROS 1 AL 9 ******************/
void disp(byte number)
{
  switch (number) {
    case 0:
      PORTD = 0b00111111;
      break;
    case 1:
      PORTD = 0b00000110;
      break;
    case 2:
      PORTD = 0b01011011;
      break;
    case 3:
      PORTD = 0b01001111;
      break;
    case 4:
      PORTD = 0b01100110;
      break;
    case 5:
      PORTD = 0b01101101;
      break;
    case 6:
      PORTD = 0b01111101;
      break;
    case 7:
      PORTD = 0b00000111;
      break;
    case 8:
      PORTD = 0b01111111;
      break;
    case 9:
      PORTD = 0b01101111;
      break;
  }
}
/********************** LIMPIAR PANTALLA *********************/
void disp_off()
{
  PORTB = B00001111;
}
/******************* CONFIGURACION TIMER 1 *******************/
void timer1_setup()
{
  TCCR1A |= 0;          // Limpiar registro y trabajr en modo normal
  TCCR1B |= bit(WGM12); // Modo CTC
  TCCR1B |= bit(CS10);  // Prescaler en 1
  TCNT1  |= 0;          // Timer1 precargado con 0 (reset)
  TIMSK1 |= bit(TOIE1); // Habilitar  interrupción por desbordamiento del Timer
}
/******************** CONFIGURACION ADC ********************/
void adc_setup()
{
  ADMUX |= bit(REFS0);     // Referencia ADC = AVCC
  ADCSRA |= bit(ADEN)      // Activar ADC
           | bit(ADPS2)   // Prescaler en 128
           | bit(ADPS1)   // idem
           | bit(ADPS0);  // idem
  converted = true;
}
