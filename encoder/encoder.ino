/*
 * Archivo: Encoder.ino
 * Autor: Cristobal Cuevas
 * Comentarios: Read encoder of a motor
 * Fecha: 23-06-2022
 *
 */
// Pins de encoder
const uint8_t pinA = 12;
const uint8_t pinB = 13;

// Contador encoder
#define N 98 // Cantidad de pistas de encoder incremental
volatile long ISRCounter = 0;
long contador = 0;

// Diametro de la rueda
#define diametro 4.9

// Variables para debouncing
volatile long timeCounter = 0;
const uint8_t timeThreshold = 5;

void setup() {
  // Puerto serial para debug
  Serial.begin(115200);
  // Pin A y B de encoder como entrada y pull up
  //DDRD |= B00000000;
  pinMode(pinA, INPUT_PULLUP);
  //PORTD |= 0b00001100;
  pinMode(pinB, INPUT_PULLUP);
  // Interrupciones para pines A y B
  attachInterrupt(digitalPinToInterrupt(pinA), EncoderA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinB), EncoderB, CHANGE);

}

void loop() {
  if (contador != ISRCounter) {
    contador = ISRCounter;
    Serial.print("Cuentas: ");
    Serial.print(contador);
    Serial.print("\t\t");
    Serial.print("Distancia: ");
    Serial.print(calculoDistancia(), 4);
    Serial.println(" cm");
  }
}

// Función que mide variaciones en Encoder A
void EncoderA() {
  if (micros() > timeCounter + timeThreshold) {
    (digitalRead(pinA) == digitalRead(pinB)) ? ISRCounter++ : ISRCounter--;
    timeCounter = micros();
  }
}

// Función que mide variaciones en Encoder B
void EncoderB() {
  if (micros() > timeCounter + timeThreshold) {
    digitalRead(pinA) != digitalRead(pinB) ? ISRCounter++ : ISRCounter--;
    timeCounter = micros();
  }
}

// Función para calcular la distancia recorrida
float calculoDistancia() {
  float perimetro = PI * diametro;
  float distancia = perimetro / 360;
  float distanciaRecorrida = contador * distancia;
  return distanciaRecorrida;
}
