const int led = 13;
int input = 0;
void setup()
{
  pinMode(led, OUTPUT); // Declaramos que utilizaremos el pin 13 como salida
  Serial.begin(9600);
}
void loop()
{
  if (Serial.available() > 0)
  {
    input = Serial.read();
    if (input == '1')
    {
      digitalWrite(led, HIGH); //Si el valor de input es 1, se enciende el led
      delay(1000);
    }
    else
    {
      digitalWrite(led, LOW); //Si el valor de input es diferente de 1, se apaga el LED
    }
  }
}
