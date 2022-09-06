void printDataSerial(vent* ventana)
{
  if (ventana->modoVentana == 10) {
    Serial.println("---------- AUTOMATICO ----------");
  } else if (ventana->modoVentana == 20) {
    Serial.println("------------ MANUAL ------------");
  }
  Serial.println(ventana->fechaFormateada);
  Serial.print("Temperatura interior: ");
  Serial.print(ventana->temperaturaInterior);
  Serial.println("ºC");
  Serial.print("Humedad interior: ");
  Serial.print(ventana->humedadInterior);
  Serial.println("%");
  Serial.print("Temperatura superior: ");
  Serial.print(ventana->temperaturaCamaraArriba);
  Serial.println("ºC");
  Serial.print("Temperatura inferior: ");
  Serial.print(ventana->temperaturaCamaraAbajo);
  Serial.println("ºC");
  Serial.print("Temperatura deseada: ");
  Serial.print(temperaturaInteriorDeseada);
  Serial.println("ºC");
  Serial.print("Nivel de luz : ");
  Serial.println(ventana->luz);
  Serial.print("Luz deseada: ");
  Serial.println(setLuz);
  Serial.print(persiana.estado == true ? "Persiana abierta y " : "Persiana cerrada y ");
  Serial.println(ventila.estado == true ? "ventila abierta" : "ventila cerrada");
}
