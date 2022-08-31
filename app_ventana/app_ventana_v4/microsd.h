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
void logSDCard(vent* ventana, servo* persiana, servo* ventila, uint8_t setLuz, uint8_t temperaturaInteriorDeseada) {
  String datosSD = String(ventana->fechaFormateada) + " " + String(ventana->temperaturaInterior) + " " + String(ventana->humedadInterior) + " " + String(persiana->estado) + " " + String(ventila->estado) + " " + String(ventana->modoVentana) + " " + String(ventana->luz) + "_" + String(ventana->temperaturaCamaraArriba) + " " + String(ventana->temperaturaCamaraAbajo) + " " + String(setLuz) + " " + String(temperaturaInteriorDeseada) + "\r\n";
  appendFile(SD, "/dataESP32.txt", datosSD.c_str());
}
void SD_init() {
  Serial.print(!SD.begin() ? "No se puede encontrar la SD" : "Se encontro la SD");
  File file = SD.open("/dataESP32.txt");
  Serial.print(!file ? "El archivo no existe, se creara uno" : "El archivo ya existe");
  if (!file) {
    writeFile(SD, "/dataESP32.txt", "fecha,temperaturaInterior,humedadInterior,estadoPersiana,estadoVentila,modoVentana,luz,temperaturaCamaraArriba,temperaturaCamaraAbajo,setLuz,temperaturaInteriorDeseada \r\n");
  }
  file.close();
}
