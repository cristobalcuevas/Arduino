const int xPin = A1;
const int yPin = A0;
const byte buttonPin = 2;

int xPosition = 0;
int yPosition = 0;
int buttonState = 0;

void setup() {
  Serial.begin(9600); 
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);

  //Activar resistencia pull-up en el pin pulsador 
  pinMode(buttonPin, INPUT_PULLUP);  
}

void loop() {
  xPosition = analogRead(xPin);
  yPosition = analogRead(yPin);
  buttonState = digitalRead(buttonPin);
  
  Serial.print("X: ");
  Serial.print(xPosition);
  Serial.print(" | Y: ");
  Serial.print(yPosition);
  Serial.print(" | Boton: ");
  Serial.println(buttonState);

  delay(100);
}
