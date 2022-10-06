/* Functions -----------------------------------------------------------------*/
void printDataSerial(dht* dht11, servo* persiana, servo* ventila, vent* ventana, ds18b20* camaraSuperior, ds18b20* camaraInferior, uint16_t *luzDeseada, uint8_t *temperaturaDeseada)
{
  if (ventana->windowMode == 10) {
    Serial.println("---------- AUTOMATICO ----------");
  } else if (ventana->windowMode == 20) {
    Serial.println("------------ MANUAL ------------");
  }
  Serial.println(ventana->dateFormatted);
  Serial.print("Temperatura interior: ");
  Serial.print(dht11->temp);
  Serial.println("ºC");
  Serial.print("Humedad interior: ");
  Serial.print(dht11->hum);
  Serial.println("%");
  Serial.print("Temperatura superior: ");
  Serial.print(camaraSuperior->temp);
  Serial.println("ºC");
  Serial.print("Temperatura inferior: ");
  Serial.print(camaraInferior->temp);
  Serial.println("ºC");
  Serial.print("Temperatura deseada: ");
  Serial.print(*temperaturaDeseada);
  Serial.println("ºC");
  Serial.print("Nivel de luz : ");
  Serial.println(ventana->ldr);
  Serial.print("Luz deseada: ");
  Serial.println(*luzDeseada);
  Serial.print(persiana->state == true ? "Persiana abierta y " : "Persiana cerrada y ");
  Serial.println(ventila->state == true ? "ventila abierta" : "ventila cerrada");
}
