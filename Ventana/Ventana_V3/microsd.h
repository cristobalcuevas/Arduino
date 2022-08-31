#include <FS.h>
#include <SD.h>
#include <SPI.h>

void writeFile(fs::FS &fs, const char * path, const char * message) {
  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("No se ha podido abrir el archivo para escribir");
    return;
  }
  if (file.print(message)) {
  } else {
    Serial.println("No se ha podido escribir");
  }
  file.close();
}
void appendFile(fs::FS &fs, const char * path, const char * message) {
  File file = fs.open(path, FILE_APPEND);
  if (!file) {
    Serial.println("No se ha podido abrir el archivo para añadirlo");
    return;
  }
  if (file.print(message)) {
  } else {
    Serial.println("Fallo al añadir");
  }
  file.close();
}
void logSDCard(String dataMessage) {
  appendFile(SD, "/dataESP32.txt", dataMessage.c_str());
}

void initSD() {
  if (!SD.begin()) {
    Serial.println("No se puede encontrar la SD");
  }
  File file = SD.open("/dataESP32.txt");
  if (!file) {
    Serial.println("El archivo no existe");
    Serial.println("Creando el archivo");
    writeFile(SD, "/dataESP32.txt", "fecha,temperaturaInterior,humedadInterior,estadoPersiana,estadoVentila,modoVentana,luz,temperaturaCamaraArriba,temperaturaCamaraAbajo,setLuz,temperaturaInteriorDeseada \r\n");
  }
  else {
    Serial.println("El archivo ya existe");

  }
  file.close();
}
