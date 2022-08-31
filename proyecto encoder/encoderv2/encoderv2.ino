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
}
/************************************************* LOOP *************************************************/
void loop() {
  ahora = rtc.now();
  if (counter != ISRCounter) {
    counter = ISRCounter;
    String dataMessage = String(printDate()) + " " + String(counter) + " " + String(distanceCalculator()) + "\r\n";
    printDataBT(dataMessage);
    saveDataSD(dataMessage);
  }
}
/*********************************************** INICIO SD ***********************************************/
void initSD() {
  SD.begin();
  File file = SD.open("/encoder.csv");
  writeFile(SD, "/encoder.csv", "Date Time Counter Value");
  file.close();
}
/*********************************************** INICIO RTC ***********************************************/
void initRTC() {
  rtc.begin();
  rtc.isrunning();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  Serial.flush();
}
/******************************************** INICIO BLUETOOTH ********************************************/
void initBT() {
  SerialBT.begin("BT001");
}
/********************************************** INICIO ENCODER ********************************************/
void initEncoder() {
  pinMode(pinA, INPUT_PULLUP);
  pinMode(pinB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pinA), EncoderA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinB), EncoderB, CHANGE);
}
/*********************************************** ENCODER A ************************************************/
void EncoderA() {
  if (micros() > timeCounter + timeThreshold) {
    (digitalRead(pinA) == digitalRead(pinB)) ? ISRCounter++ : ISRCounter--;
    timeCounter = micros();
  }
}
/*********************************************** ENCODER B ************************************************/
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
/**************************************** IMPRIMIR DATOS BLUETOOTH ***************************************/
void printDataBT(String dataMessage) {
  SerialBT.print(dataMessage);
}
/********************************************* GUARDAR DATOS SD *******************************************/
void saveDataSD(String dataMessage) {
  appendFile(SD, "/encoder.csv", dataMessage.c_str());
}
/********************************************* ESCRIBIR ARCHIVO *******************************************/
void writeFile(fs::FS &fs, const char * path, const char * message) {
  File file = fs.open(path, FILE_WRITE);
  file.print(message);
  file.close();
}
/***************************************** AÑADIR TEXTO A ARCHIVO *****************************************/
void appendFile(fs::FS &fs, const char * path, const char * message) {
  File file = fs.open(path, FILE_APPEND);
  file.print(message);
  file.close();
}
/***************************************** CONVERSION PUNTO A COMA *****************************************/
String pointTocomma(float number) {
  int ival = (int)number;
  int frac = (number - ival) * 100;
  String dataMessage = String(ival) + "," + String(frac);
  return dataMessage;
}
