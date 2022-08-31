/******************************** LIBRERIAS *******************************/
#include "FS.h"
#include "SD.h"
#include "SPI.h"
/********************************* SETUP **********************************/
void setup()
{
  Serial.begin(115200);
  initSD();
}
/********************************** LOOP **********************************/
void loop()
{
}
/***************************** INICIALIZAR SD *****************************/
void initSD()
{
  SD.begin();
  File file = SD.open("/prueba.txt");
  writeFile(SD, "/prueba.txt", "Hola ");
  appendFile(SD, "/prueba.txt", "Mundo\n");
  file.close();
}
/***************************** ESCRIBIR TEXTO *****************************/
void writeFile(fs::FS &fs, const char * path, const char * message)
{
  File file = fs.open(path, FILE_WRITE);
  file.print(message);
  file.close();
}
/****************************** AÑADIR TEXTO ******************************/
void appendFile(fs::FS &fs, const char * path, const char * message)
{
  File file = fs.open(path, FILE_APPEND);
  file.print(message);
  file.close();
}
