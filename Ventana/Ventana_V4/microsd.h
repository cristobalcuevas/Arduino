/* Includes ------------------------------------------------------------------*/
#include <FS.h>
#include <SD.h>
#include <SPI.h>
/* Functions -----------------------------------------------------------------*/
void writeFile(fs::FS &fs, const char * path, const char * message) {
  File file = fs.open(path, FILE_WRITE);

  Serial.println(!file ? "Archivo no se pudo abrir" : "Archivo abierto");
  Serial.println(file.print(message) ? "Archivo escrito" : "No se ha podido escribir");
  file.close();
}
void appendFile(fs::FS &fs, const char * path, const char * message) {
  File file = fs.open(path, FILE_APPEND);
  Serial.println(!file ? "Archivo no se pudo abrir" : "Archivo abierto");
  Serial.println(file.print(message) ? "Archivo añadido" : "No se ha podido añadir");
  file.close();
}
void SD_init() {
  Serial.println(!SD.begin() ? "No se puede encontrar la SD" : "Se encontro la SD");
  File file = SD.open("/dataESP32.txt");
  Serial.println(!file ? "El archivo no existe, se creara uno" : "El archivo ya existe");
  if (!file) {
    writeFile(SD, "/dataESP32.txt", "ESP32-4\r\n");
    writeFile(SD, "/dataESP32.txt", "Fecha,TemperaturaInterior,HumedadInterior,EstadoPersiana,EstadoVentila,ModoVentana,Luz,TemperaturaCamaraArriba,temperaturaCamaraAbajo,LuzDeseada,TemperaturaDeseada\r\n");
  } else if (file) {
    writeFile(SD, "/dataESP32.txt", "ESP32-4\r\n");
    writeFile(SD, "/dataESP32.txt", "Fecha,TemperaturaInterior,HumedadInterior,EstadoPersiana,EstadoVentila,ModoVentana,Luz,TemperaturaCamaraArriba,temperaturaCamaraAbajo,LuzDeseada,TemperaturaDeseada\r\n");
  }
  file.close();
}
void logSDCard(dht* dht11, servo* persiana, servo* ventila, vent* ventana, ds18b20* camaraSuperior, ds18b20* camaraInferior, uint16_t *luzDeseada, uint8_t *temperaturaDeseada) {
  String datosSD =  String(ventana->dateFormatted) + "," +
                    String(dht11->temp) + "," +
                    String(dht11->hum) + "," +
                    String(persiana->state) + "," +
                    String(ventila->state) + "," +
                    String(ventana->windowMode) + "," +
                    String(ventana->ldr) + "," +
                    String(camaraSuperior->temp) + "," +
                    String(camaraInferior->temp) + "," +
                    String(*luzDeseada) + "," +
                    String(*temperaturaDeseada) + "\r\n";
  appendFile(SD, "/dataESP32.txt", datosSD.c_str());
}
