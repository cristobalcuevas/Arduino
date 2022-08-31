void setup() {
  Serial1.begin(19200);
  Serial.begin(19200);
  llamar();
}

void loop() {}

void llamar() {
  Serial1.print("ATD");
  Serial1.print("+56950863835");
  Serial1.println(";");
  Serial.println("Llamando...");
  delay(20000);
  Serial1.println("ATH");
  Serial.println("Llamada finalizada");
}
