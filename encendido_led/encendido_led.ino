const int led = 8;                // Ponemos nombre al pin 7

void setup()
{
  pinMode(led, OUTPUT);     // Declaramos el led (pin 7) como salida
}

void loop()
{
  digitalWrite(led, LOW);   // Apagamos el led
  delay(1000);              // Tiempo de 1 segundo
  digitalWrite(led, HIGH);  // Encendemos el led
  delay(1000);              // Tiempo de 1 segundo
}
