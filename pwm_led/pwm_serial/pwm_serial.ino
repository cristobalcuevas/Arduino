int led = 13;
int input = 0;
void setup()
{
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  if (Serial.available() > 0)
  {
    input = Serial.read();
    while (input == '1')
    {
      if (int i=0; i<=255; i++)
      {
        analogWrite(led, i);
        delay(10);
      }
    }
  }
}
