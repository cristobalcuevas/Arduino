void setup() {
   Serial.begin(9600);
}
long readTimer = 0;
float voltage;
void loop(){
  if(millis() - readTimer > 500){
    voltage = analogRead(A0)/1023.0*5;
    Serial.println(voltage);
    readTimer = millis();
  }
}
