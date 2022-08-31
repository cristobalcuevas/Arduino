const int boton = 2;
const int led =  13;
int estado = 0;

void setup()
{
  pinMode(led, OUTPUT);
  pinMode(boton, INPUT);
  digitalWrite(led, LOW);
}

void loop()
{
  estado = digitalRead(boton);
  if (estado == HIGH)
  {
    digitalWrite(led, HIGH);
  }
  else
  {
    digitalWrite(led, LOW);
  }
}
