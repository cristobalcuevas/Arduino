void printDataSerial(int modoVentana, String fecha, float temp, float humi, float temperaturaCamaraArriba, float temperaturaCamaraAbajo, int luz, bool ventila, bool persiana) {
  if (modoVentana == 10) {
    Serial.println("--------- AUTOMATICO ---------");
  } else if (modoVentana == 20) {
    Serial.println("----------- MANUAL -----------");
  }
  Serial.println(fecha);
  Serial.print("Temperatura interior: ");
  Serial.print(temp);
  Serial.println("ºC");
  Serial.print("Humedad interior: ");
  Serial.print(humi);
  Serial.println("%");
  Serial.print("Temperatura superior: ");
  Serial.print(temperaturaCamaraArriba);
  Serial.println("ºC");
  Serial.print("Temperatura inferior: ");
  Serial.print(temperaturaCamaraAbajo);
  Serial.println("ºC");
  Serial.print("Temperatura deseada: ");
  Serial.print(temperaturaInteriorDeseada);
  Serial.println("ºC");
  Serial.print("Nivel de luz : ");
  Serial.println(luz);
  Serial.print("Setpoint luz: ");
  Serial.println(setLuz);
  if (persiana == true) {
    Serial.print("Persiana abierta y ");
  } else {
    Serial.print("Persiana cerrada y ");
  }
  if (ventila == true) {
    Serial.println("ventila abierta");
  } else {
    Serial.println("ventila cerrada");
  }
}
