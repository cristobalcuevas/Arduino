const uint8_t pinLDR = 35;
/* Functions -----------------------------------------------------------------*/
uint16_t getLDR()
{
  uint16_t raw_data = analogRead(pinLDR);
  return raw_data;
}
