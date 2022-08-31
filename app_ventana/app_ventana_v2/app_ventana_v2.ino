/************************************* LIBRERIAS *************************************/
#include "BluetoothSerial.h"   // BLUETOOTH
#include <DHT.h>               // DHT11
#include <OneWire.h>           // DS18B20
#include <DallasTemperature.h> // DS18B20
#include "RTClib.h"            // RTC
#include "FS.h"                // MICROSD
#include <SD.h>                // MICROSD
#include <SPI.h>               // MICROSD
#include <Servo.h>             // SERVOS
/*************************************** PINES ***************************************/
#define DHTtype DHT11
const int sensorLuz = A7;
const int DHTpin = 15;
const int pinPersiana = 14;
const int pinVentila = 13;
const int pinCamaraArriba = 27;
const int pinCamaraAbajo = 26;
/************************************* INSTANCIAS *************************************/
BluetoothSerial SerialBT;
RTC_DS1307 rtc;
DHT dht(DHTpin, DHTtype);
OneWire CamaraArriba(pinCamaraArriba);
OneWire CamaraAbajo(pinCamaraAbajo);
DallasTemperature camaraArriba(&CamaraArriba);
DallasTemperature camaraAbajo(&CamaraAbajo);
Servo servoPersiana;
Servo servoVentila;
/************************************* VARIABLES *************************************/
// DS18B20
float temperaturaCamaraArriba = 0, temperaturaCamaraAbajo = 0, temperaturaCamara = 0;
// DHT11
int temperaturaInteriorDeseada = 25;
float temperaturaInterior = 0, humedadInterior = 0;
// LDR
int luz = 0, setLuz = 600;
// RTC
String fechaFormateada = "";
// VENTILA Y PERSIANA
bool estadoVentila, estadoPersiana;
int servoPersianaCerrada = 50, servoPersianaAbierta = 170, servoVentilaCerrada = 35, servoVentilaAbierta = 5;
// MODO DE VENTANA
int modoVentana = 10;
String comando = "";
// DATOS
String datosSD = "", datosBT = "";
/************************************* SETUP *************************************/
void setup() {
  Serial.begin(115200);
  initSD();
  initRTC();
  initDS18B20();
  initDHT();
  initBT();
  initServos();
}
/************************************* LOOP **************************************/
void loop() {
  // OBTENCION DE DATOS
  fechaFormateada = getDate();
  temperaturaInterior = getTempe();
  humedadInterior = getHumi();
  temperaturaCamaraArriba = getDS18B20Arriba();
  temperaturaCamaraAbajo = getDS18B20Abajo();
  temperaturaCamara = (temperaturaCamaraArriba + temperaturaCamaraAbajo) / 2;
  luz = getLDR(sensorLuz);
  datosSD = String(fechaFormateada) + " " + String(temperaturaInterior) + " " + String(humedadInterior) + " " + String(estadoPersiana) + " " + String(estadoVentila) + " " + String(modoVentana) + " " + String(luz) + "_" + String(temperaturaCamaraArriba) + " " + String(temperaturaCamaraAbajo) + " " + String(setLuz) + " " + String(temperaturaInteriorDeseada) + "\r\n";
  datosBT = String(temperaturaInterior) + "_" + String(humedadInterior) + "_" + String(estadoPersiana) + "_" + String(estadoVentila) + "_" + String(modoVentana) + "_" + String(luz) + "_" + String(temperaturaCamaraArriba) + "_" + String(temperaturaCamaraAbajo) + "_" + String(setLuz) + "\r\n";
  // REVISION DE MODO DE LA VENTANA
  // MODO AUTOMATICO
  if (modoVentana == 10) {
    if (luz >= setLuz) {
      abrirPersiana();
    }
    else if (luz < setLuz) {
      cerrarPersiana();
    }
    if (temperaturaCamara > temperaturaInteriorDeseada || temperaturaInterior < temperaturaInteriorDeseada || temperaturaCamara > temperaturaInterior) {
      abrirVentila();
    } else {
      cerrarVentila();
    }
  }
  // MODO MANUAL
  else if (modoVentana == 20) {
  }
  // VERIFICAR BLUETOOTH DISPONIBLE Y LEER COMANDO
  while (SerialBT.available()) {
    comando = SerialBT.readString();
  }
  // REALIZAR ACCION DE ACUERDO AL COMANDO LEIDO
  if (comando == "4") {
    modoVentana = 10;
    // MODO AUTOMATICO

  }
  if (comando == "5") {
    modoVentana = 20;
    // MODO MANUAL
  }
  if (comando == "1" && modoVentana == 20) {
    estadoPersiana = true;
    abrirPersiana();
  }
  else if (comando == "0" && modoVentana == 20) {
    estadoPersiana = false;
    cerrarPersiana();
  }
  else if (comando == "2" && modoVentana == 20) {
    estadoVentila = true;
    abrirVentila();
  }
  else if (comando == "3" && modoVentana == 20) {
    estadoVentila = false;
    cerrarVentila();
  }
  printDataSerial(modoVentana, fechaFormateada, temperaturaInterior, humedadInterior, temperaturaCamaraArriba, temperaturaCamaraAbajo, luz, estadoVentila, estadoPersiana);
  printDataBT(datosBT);
  logSDCard(datosSD);
  delay(2000);
}
/*********************************** FIN LOOP ************************************/
void initSD() {
  if (!SD.begin()) {
    Serial.println("No se puede encontrar la SD");
  }
  File file = SD.open("/dataESP32.txt");
  if (!file) {
    Serial.println("El archivo no existe");
    Serial.println("Creando el archivo");
    writeFile(SD, "/dataESP32.txt", "Fecha,Temperatura,Humedad,TemperaturaSuperior,TemperaturaInferior,Luz \r\n");
  }
  else {
    Serial.println("El archivo ya existe");

  }
  file.close();
}
void initBT() {
  SerialBT.begin("ESP32-2");
  Serial.println("El dispositivo se ha iniciado, ahora puedes emparejarlo");
}
void initDS18B20() {
  camaraArriba.begin();
  camaraAbajo.begin();
}
void initRTC() {
  if (!rtc.begin()) {
    Serial.println("No se puede encontrar el RTC");
    Serial.flush();
  }
  if (!rtc.isrunning()) {
    Serial.println("El RTC no está corriendo, ¡pongamos la hora!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}
void initDHT() {
  dht.begin();
}
void initServos() {
  servoPersiana.attach(pinPersiana);
  servoVentila.attach(pinVentila);
}
void printDataBT(String dataMessage) {
  SerialBT.print(dataMessage);
}
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
  Serial.print("Luz : ");
  Serial.println(luz);
  if (persiana == true) {
    Serial.println("Persiana abierta");
  } else {
    Serial.println("Persiana cerrada");
  }
  if (ventila == true) {
    Serial.println("Ventila abierta");
  } else {
    Serial.println("Ventila cerrada");
  }
}
int getLDR(int pin) {
  int luz = (analogRead(pin));
  return luz;
}
String getDate() {
  DateTime now = rtc.now();
  char buf[] = "DD/MM/YYYY, hh:mm:ss";
  String fechaHora = String(now.toString(buf));
  return fechaHora;
}
float getTempe() {
  float temperatura = dht.readTemperature();
  if (isnan(temperatura)) {
    temperatura = 0;
  }
  return temperatura;
}
float getHumi() {
  float humedad = dht.readHumidity();
  if (isnan(humedad)) {
    humedad = 0;
  }
  return humedad;
}
float getDS18B20Arriba() {
  camaraArriba.requestTemperatures();
  float tempArriba = camaraArriba.getTempCByIndex(0);
  if (tempArriba == -127) {
    tempArriba = 0;
  }
  return tempArriba;
}
float getDS18B20Abajo() {
  camaraAbajo.requestTemperatures();
  float tempAbajo = camaraAbajo.getTempCByIndex(0);
  if (tempAbajo == -127) {
    tempAbajo = 0;
  }
  return tempAbajo;
}
void cerrarPersiana() {
  estadoPersiana = false;
  servoPersiana.write(servoPersianaCerrada);
}
void abrirPersiana() {
  estadoPersiana = true;
  servoPersiana.write(servoPersianaAbierta);
}
void cerrarVentila() {
  estadoVentila = false;
  servoVentila.write(servoVentilaCerrada);
}
void abrirVentila() {
  estadoVentila = true;
  servoVentila.write(servoVentilaAbierta);
}
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
