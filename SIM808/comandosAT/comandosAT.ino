void setup()
{
  Serial1.begin(19200);
  Serial.begin(19200);
}

void loop()
{
  if (Serial.available() > 0)
    Serial1.write(Serial.read());
  if (Serial1.available() > 0)
    Serial.write(Serial1.read());
}
