/*
  Cristobal Cuevas Lagos
  Conversión de vueltas de encoder a desplazamiento
  23-06-2022
*/
// Librerias
#include "BluetoothSerial.h"
#include "RTClib.h"
#include "FS.h"
#include "SD.h"
#include "SPI.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth no esta activado, abrir 'menuconfig' y activarlo.
#endif

// Pins de encoder
const uint8_t pinA = 12;
const uint8_t pinB = 13;

// Contador encoder
volatile long ISRCounter = 0;
long counter = 0;

// Diametro de la rueda
#define diameter 4.9

// Variables para debouncing
volatile long timeCounter = 0;
const uint8_t timeThreshold = 5;

BluetoothSerial SerialBT;
RTC_DS1307 rtc;
DateTime ahora;
/************************************************* SETUP ************************************************/
void setup() {
  Serial.begin(115200);
  initSD();
  initRTC();
  initBT();
  initEncoder();
  writeFile(SD, "/encoder.csv", "Date Time Value\r\n");
}
/************************************************* LOOP *************************************************/
void loop() {
  ahora = rtc.now();
  if (counter != ISRCounter) {
    counter = ISRCounter;
    printDataBT();
    String dataMessage = String(printDate()) + " " + String(distanceCalculator()) + "\r\n";
    appendFile(SD, "/encoder.csv", dataMessage.c_str());
  }
}
/*********************************************** INICIO SD ***********************************************/
void initSD() {
  if (!SD.begin()) {
    Serial.println("Fallo al montar la SD");
    return;
  }
  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE) {
    Serial.println("SD no insertada");
    return;
  }
  // If the data.txt file doesn't exist
  // Create a file on the SD card and write the data labels
  File file = SD.open("/encoder.csv");
  if (!file) {
    Serial.println("El archivo no existe");
    Serial.println("Creando el archivo ");
    writeFile(SD, "/encoder.csv", "Date Time Value\r\n");
  }
  else {
    Serial.println("El archivo ya existe");
  }
  file.close();
}
/*********************************************** INICIO RTC ***********************************************/
void initRTC() {
  Serial.println(!rtc.begin() ? "No se encontro RTC" : "RTC conectado");
  Serial.println(!rtc.isrunning() ? "Error al inicializar el RTC" : "RTC iniciado");
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  Serial.flush();
}
/********************************************** INICIO BLUETOOTH **********************************************/
void initBT() {
  Serial.println(!SerialBT.begin("BT001") ? "Error al inicializar el bluetooth" : "Bluetooth iniciado");
}
/************************************************ INICIO ENCODER **********************************************/
void initEncoder() {
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinA), EncoderA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinB), EncoderB, CHANGE);
}
/*********************************************** ENCODER A ***********************************************/
void EncoderA() {
  if (micros() > timeCounter + timeThreshold) {
    (digitalRead(pinA) == digitalRead(pinB)) ? ISRCounter++ : ISRCounter--;
    timeCounter = micros();
  }
}
/*********************************************** ENCODER B ***********************************************/
void EncoderB() {
  if (micros() > timeCounter + timeThreshold) {
    digitalRead(pinA) != digitalRead(pinB) ? ISRCounter++ : ISRCounter--;
    timeCounter = micros();
  }
}
/******************************************** OBTENER DISTANCIA *******************************************/
String distanceCalculator() {
  float perimeter = PI * diameter;
  float distance = perimeter / 360;
  float totalDistance = counter * distance;
  String dataMessage = pointTocomma(totalDistance);
  return dataMessage;
}
/********************************************* IMPRIMIR FECHA *********************************************/
String printDate() {
  DateTime now = rtc.now();
  char buf[] = "DD-MM-YYYY hh:mm:ss";
  String bufDate = String(now.toString(buf));
  return bufDate;
}
/**************************************** IMOPRIMIR DATOS BLUETOOTH ***************************************/
void printDataBT() {
  SerialBT.print("F: ");
  SerialBT.print(printDate());
  SerialBT.print(" ");
  SerialBT.print("C: ");
  SerialBT.print(counter);
  SerialBT.print(" ");
  SerialBT.print("D: ");
  SerialBT.print(distanceCalculator());
  SerialBT.println(" cm");
}
/********************************************* ESCRIBIR ARCHIVO *******************************************/
void writeFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Escribiendo archivo: %s\n", path);
  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Fallo al abrir el archivo para escribir");
    return;
  }
  if (file.print(message)) {
    Serial.println("Archivo escrito");
  } else {
    Serial.println("Fallo al escribir");
  }
  file.close();
}
/***************************************** AÑADIR TEXTO A ARCHIVO *****************************************/
void appendFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Añadiendo a: %s\n", path);
  File file = fs.open(path, FILE_APPEND);
  if (!file) {
    Serial.println("Fallo al abrir el archivo para añadir mensaje");
    return;
  }
  if (file.print(message)) {
    Serial.println("Mensaje añadido");
  } else {
    Serial.println("Fallo al añadir");
  }
  file.close();
}
/***************************************** CONVERSION PUNTO A COMA *****************************************/
String pointTocomma(float number) {
  int ival = (int)number;
  int frac = (number - ival) * 100;
  String dataMessage = String(ival) + "," + String(frac);
  return dataMessage;
}
