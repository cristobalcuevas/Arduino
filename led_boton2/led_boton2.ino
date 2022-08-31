const int boton = 2;
const int led =  13;

int estado = 0; // Almacena estado actual del boton
int valorActual = 0;  // Si es "0" led apagado, mientras que si es "1" led encendido
int valorAnterior = 0; // Almacena estado anterior del boton

void setup()
{
  pinMode(led, OUTPUT); // Led como una salida
  pinMode(boton, INPUT); // Boton como una entrada
}

void loop()
{
  valorActual = digitalRead(boton); // Leemos estado actual del boton
  if (valorActual == HIGH && valorAnterior == LOW)
  {
    estado = 1 - estado;
    delay(10);
  }
  valorAnterior = valorActual;
  if (estado == 1)
  {
    digitalWrite(led, HIGH);
  }
  else
  {
    digitalWrite(led, LOW);
  }
}
