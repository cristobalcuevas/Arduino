const int micPin  = A0;

int micVal  = 0;

void readMicrophone();
void setup() {
  Serial.begin(9600);
  pinMode(micPin, INPUT);
}

void loop() {
  readMicrophone();
  delay(100);
}

void readMicrophone() {
  micVal = analogRead(micPin);
  Serial.print("Valor Microfono: ");
  Serial.println(micVal);
}
