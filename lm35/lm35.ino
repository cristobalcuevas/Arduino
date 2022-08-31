#include<LiquidCrystal.h>
int lectura = 0;
float temperatura = 0, suma;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
const int alto = 9, normal = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  lcd.begin(16, 2);
  pinMode(alto, OUTPUT);
  pinMode(normal, OUTPUT);
}
void loop() {
  suma = 0;
  for (int i = 0; i < 5; i++) {
    lectura = analogRead(A0);
    temperatura = ((lectura * 5000.0) / 1024) / 10;
    suma = temperatura + suma;
    delay(200);
  }
  if (suma / 5.0 > 50.0) {
    digitalWrite(alto, HIGH);
    digitalWrite(normal, LOW);
  }
  else {
    digitalWrite(alto, LOW);
    digitalWrite(normal, HIGH);
  }

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(suma / 5.0, 1);
  lcd.print(" C");
}
