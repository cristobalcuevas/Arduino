#define led = 9;  // Nombramos el pin 9 como led
const int dato = A0;  // Pin analogo entrada de dato del potenciometro
int valorDato = 0;  // Variable que tomara lectura de A0

void setup()
{
  pinMode(led, OUTPUT); // Declaramos el pin 9 como salida, aunque no es necesario
  Serial.begin(9600);
}

void loop()
{
  valorDato = analogRead(dato); // Leemos el valor analogico de entrada de A0
  analogWrite(led, valorDato / 4); // Determinamos el valor de salia y lo pasamos al pin 9
  Serial.println(valorDato);
  delay(50);
}
