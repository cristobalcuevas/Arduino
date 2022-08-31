int getLDR(int pin) {
  uint16_t raw_data = analogRead(pin);
  return raw_data;
}
