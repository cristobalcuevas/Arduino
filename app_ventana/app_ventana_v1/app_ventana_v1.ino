//librerias
#include <Arduino.h>
#include "BluetoothSerial.h"
#include <Servo.h>
#include <DHT11.h>
#include "SD.h"
#include "SPI.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#include <EEPROM.h>
#include <string.h>
#include <Separador.h>
#include "RTClib.h"
#include "FS.h"
Separador s;

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define EEPROM_SIZE 5
BluetoothSerial SerialBT;
//DHTesp dht;
// DHTesp dht2;
Servo myservo;
Servo myservo2;
RTC_DS1307 rtc;

////Pines
const int servoPin = 14;
const int servoPin2 = 13;
const int enablePin2 = 0;
//const int lm35pin1 = A6;  //34 fuera de uso
//const int lm33pin2 = A0;  //sp fuera de uso
OneWire ourWire1(27);                  //arriba
OneWire ourWire2(26);                  //abajo
DallasTemperature sensors1(&ourWire1); //Camara arriba
DallasTemperature sensors2(&ourWire2); //abajo
const int sensorLuz = A7;              //35
const int DHTpin = 15;
DHT11 dht11(DHTpin);
////funciones

int boolPersiana;
int boolVentila;

float Ds18b20Arriba()
{ ///devulve valor de temperatura
  sensors1.requestTemperatures();
  float temp1 = sensors1.getTempCByIndex(0);
  Serial.print("Temperatura camara arriba: ");
  Serial.println(temp1);
  return temp1;
}
float Ds18b20Abajo()
{ ///devulve valor de temperatura abajo
  sensors2.requestTemperatures();
  float temp2 = sensors2.getTempCByIndex(0);
  Serial.print("Temperatura camara abajo: ");
  Serial.println(temp2);
  return temp2;
}

int LDR(int pin)
{ ///devulve valor de Luminosidad
  Serial.print("luz : ");
  int luz = (analogRead(pin));
  Serial.println(luz);
  return luz;
}

//float DHTtemp1()
//{

// delay(dht.getMinimumSamplingPeriod());
//float temperature = dht.getTemperature();
//Serial.println(dht.getStatusString());
//Serial.print("Temperatura ");
//Serial.println(temperature, 1);
// return temperature;
//}
// float DHThr1()
// {

//   float humidity = dht.getHumidity();
//   Serial.println(dht2.getStatusString());
//   Serial.print("Humedad: ");
//   Serial.println(humidity, 1);
//   return humidity;
// }
////movimietno de las ventilas
void cerrarVentila()
{
  boolVentila = 0;
  Serial.println("cierre de ventila '0'");
  // myservo2.write(0); 23-8 cambiar a 45
  myservo2.write(35);
}

void abrirVentila()
{
  boolVentila = 1;
  Serial.println("Abriendo ventila '90'");
  //myservo2.write(90);
  //myservo2.write(45); //2 feb//30 grados...45 grados 23-8 cambiar a 0
  myservo2.write(5);
  myservo2.write(5);

}
bool errorVentila()
{
  //esperar sensor de corriente
}

//movimiento de las persinanas
void cerrarPersiana()
{
  boolPersiana = 0;
  Serial.println("cierre de Persiana '0'");
  myservo.write(150);
}

void abrirPersiana()
{
  boolPersiana = 1;
  Serial.println("Abriendo Persiana '180'");
  myservo.write(90);
}
bool errorPersiana()
{
  //esperar sensor de corriente
}
///escribir en SD
void appendFile(fs::FS &fs, const char *path, const char *message)
{
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if (!file)
  {
    Serial.println("Failed to open file for appending");
    return;
  }
  if (file.print(message))
  {
    Serial.println("................................................Message appended");
  }
  else
  {
    Serial.println("................................................Append failed");
  }
  file.close();
}
void writeFile(fs::FS &fs, const char *path, const char *message)
{
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file)
  {
    Serial.println("Failed to open file for writing");
    return;
  }
  if (file.print(message))
  {
    Serial.println("................................................File written");
  }
  else
  {
    Serial.println("................................................Write failed");
  }
  file.close();
}
void readFile(fs::FS &fs, const char *path)
{
  delay(2000);
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if (!file)
  {
    Serial.println("Failed to open file for reading");
    writeFile(SD, "/dataESP32.txt", "fecha,hora, temperaturaInterior, temperaturaCamaraArriba,temperaturaCamaraAbajo,humedadDHT,luz,persiana,ventila,modo \r\n");

    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.print("Read from file: ");
  //while(file.available()){
  //   Serial.write(file.read());
  //}
  file.close();
}
//variables de sensores
float temperaturaInterior;
float temperaturaCamaraArriba;
float temperaturaCamaraAbajo;
float temperaturaDHT;
float humedadDHT;
int luz;

//variable modo
int modov = 10;
int temperaturaInteriorDeseada = 20;

//variables offset
int offSetTemperaturaInterior = 0;
int offSetTemperaturaCamaraArriba = 0;
int offSetTemperaturaCamaraAbajo = 0;
int offSetHumedad = 0;
int SetLuz = 200; //dato de corte para mover persiana

//vaiables informacion y aaux
float deltaT = 0;
int fecha;
String fecha2 = "";
//String dataString = "";
int AUX;
String datos = "";
float auxOS0;
float auxOS1;
float auxOS2;
float auxOS3;
float auxOS4;


String fecha_hora()
{
  DateTime now = rtc.now();

  int i_dia = now.day();
  int i_mes = now.month();
  int i_hora = now.hour();
  int i_minuto = now.minute();
  int i_segundo = now.second();
  String dia;
  String mes;
  String hora;
  String minuto;
  String segundo;
  if (i_dia < 10)
  {
    dia = "0" + String(now.day());
  }
  else
  {
    dia = String(now.day());
  }
  if (i_mes < 10)
  {
    mes = "0" + String(now.month());
  }
  else
  {
    mes = String(now.month());
  }

  if (i_hora < 10)
  {
    hora = "0" + String(now.hour());
  }
  else
  {
    hora = String(now.hour());
  }
  if (i_minuto < 10)
  {
    minuto = "0" + String(now.minute());
  }
  else
  {
    minuto = String(now.minute());
  }
  if (i_segundo < 10)
  {
    segundo = "0" + String(now.second());
  }
  else
  {
    segundo = String(now.second());
  }

  String fecha_hora = String(dia) + "/" + String(mes) + "/" + String(now.year()) + "," + String(hora) + ":" + String(minuto) + ":" + String(segundo) + " ";
  return fecha_hora;
}

void setup()
{
  Serial.begin(115200);
  SerialBT.begin("ESP32-2"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

  EEPROM.begin(EEPROM_SIZE);
  sensors1.begin(); //Se inicia el sensor 1
  sensors2.begin(); //Se inicia el sensor 2
  // iniciamos SD y RTC
  if (!rtc.begin())
  {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  if (!rtc.isrunning())
  {
    Serial.println("RTC is NOT running, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  // set
  if (!SD.begin())
  {
    Serial.println("Card Mount Failed");
    return;
  }
  readFile(SD, "/dataESP32.txt");

  auxOS0 = EEPROM.read(0);
  Serial.println("valor eprom: ");
  Serial.println(auxOS0);
  if (auxOS0 != NULL)
  {

    if (auxOS0 > 150)
    {
      auxOS0 = auxOS0 - 256;
    }
    offSetTemperaturaInterior = auxOS0;
    Serial.println(auxOS0);
  }

  auxOS1 = EEPROM.read(1);
  Serial.println("valor eprom: ");
  Serial.println(auxOS1);
  if (auxOS1 != NULL)
  {
    if (auxOS1 > 150)
    {
      auxOS1 = auxOS1 - 256;
    }
    Serial.println(auxOS1);
    offSetTemperaturaCamaraArriba = auxOS1;
  }

  auxOS2 = EEPROM.read(2);
  Serial.println("valor eprom: ");
  Serial.println(auxOS2);
  if (auxOS2 != NULL)
  {
    if (auxOS2 > 150)
    {
      auxOS2 = auxOS2 - 256;
    }
    Serial.println(auxOS2);
    offSetTemperaturaCamaraAbajo = auxOS2;
  }

  auxOS3 = EEPROM.read(3);
  Serial.println("valor eprom: ");
  Serial.println(auxOS3);
  if (auxOS3 != NULL)
  {
    if (auxOS3 > 150)
    {
      auxOS3 = auxOS3 - 256;
    }
    Serial.println(auxOS3);
    offSetHumedad = auxOS3;
  }

  auxOS4 = EEPROM.read(4);
  Serial.println("valor eprom: ");
  Serial.println(auxOS4);
  if (auxOS4 != NULL)
  {
    Serial.println(auxOS4);
    SetLuz = EEPROM.read(4);
    Serial.println(SetLuz);
  }


  //definimos servos de la ventila y de la persiana
  myservo.attach(servoPin);
  myservo2.attach(servoPin2);

  //definimos e instanciamos hora
  DateTime now = rtc.now();
  fecha = now.unixtime();
  fecha2 = fecha_hora();
  Serial.print("........................." + fecha2);
  AUX = fecha;
}
void grabarSD(float temperaturaInterior, float temperaturaCamaraArriba, float temperaturaCamaraAbajo, float humedadDHT, int luz, String fecha, int boolPersiana, int boolVentila)
{

  String dataString;
  dataString += String(fecha);
  dataString += ",";
  dataString += String(temperaturaInterior);
  dataString += ",";
  dataString += String(temperaturaCamaraArriba);
  dataString += ",";
  dataString += String(temperaturaCamaraAbajo);
  dataString += ",";
  dataString += String(humedadDHT);
  dataString += ",";
  dataString += String(luz);
  dataString += ",";
  dataString += String(boolPersiana);
  dataString += ",";
  dataString += String(boolVentila);
  dataString += ",";
  dataString += String(modov);
  dataString += "\r\n";
  Serial.println(dataString);

  appendFile(SD, "/dataESP32.txt", dataString.c_str());
}
void loop()
{ //
  int err;
  float temp, humi;
  if ((err = dht11.read(humi, temp)) == 0)
  {
    Serial.print("temperature:");
    Serial.print(temp);
    Serial.print(" humidity:");
    Serial.print(humi);
    Serial.println();
  }
  else
  {
    Serial.println();
    Serial.print("Error No :");
    Serial.print(err);
    Serial.println();
  }
  delay(DHT11_RETRY_DELAY); //delay for reread

  temperaturaInterior = temp;
  temperaturaInterior = temperaturaInterior + offSetTemperaturaInterior;

  humedadDHT = humi;
  humedadDHT = humedadDHT + offSetHumedad;
  if (isnan(humedadDHT)) {
    humedadDHT = 0;
  }
  if (isnan(temperaturaInterior)) {
    temperaturaInterior = 0;
  }

  temperaturaCamaraArriba = Ds18b20Arriba();

  temperaturaCamaraArriba = temperaturaCamaraArriba + offSetTemperaturaCamaraArriba;
  temperaturaCamaraAbajo = Ds18b20Abajo();

  temperaturaCamaraAbajo = temperaturaCamaraAbajo + offSetTemperaturaCamaraAbajo;
  luz = LDR(sensorLuz);

  datos = (String(int(temperaturaInterior)) + "_" +
           String(int(humedadDHT)) + "_" +
           String(int(boolPersiana)) + "_" +
           String(int(boolVentila)) + "_" +
           String(int(modov)) + "_" +
           String(int(luz)) + "_" +
           String(int(temperaturaCamaraArriba)) + "_" +
           String(int(temperaturaCamaraAbajo)) + "_" +
           String(int(offSetTemperaturaInterior)) + "_" +
           String(int(offSetTemperaturaCamaraArriba)) + "_" +
           String(int(offSetTemperaturaCamaraAbajo)) + "_" +
           String(int(offSetHumedad)) + "_" +
           String(int(offSetHumedad)) + "_" +
           String(int(SetLuz)) + "_");

  SerialBT.print(datos);
  delay(200);

  delay(1000);
  DateTime now = rtc.now();

  fecha2 = fecha_hora();
  Serial.print("......................... fecha");
  Serial.println(fecha2);
  fecha = now.unixtime();
  Serial.println(fecha);
  if ((fecha - 30) > AUX)
  {
    AUX = fecha;
    grabarSD(temperaturaInterior, temperaturaCamaraArriba, temperaturaCamaraAbajo, humedadDHT, luz, fecha2, boolPersiana, boolVentila);
  }

  //SerialBT.print(datos);

  if (modov == 10)
  {

    Serial.println("............AUTOMATICO...........");
    if (luz >= SetLuz)
    {
      Serial.println("luz mayor se abrira persiana");
      abrirPersiana();
    }
    else if (luz < SetLuz)
    {
      Serial.println("luz menor se cerrara persiana");
      cerrarPersiana();
    }
    // Serial.println("temperatura camara" + String(temperaturaCamaraLM35));
    // Serial.println("temperatura interior" + String(temperaturaInterior));
    //zona ventila
    // if (temperaturaCamaraArriba > temperaturaInterior + deltaT && temperaturaInterior < temperaturaInteriorDeseada && temperaturaCamaraArriba >= temperaturaInteriorDeseada)
    // {
    //   Serial.println("mayor se abrira Ventila 1");
    //   abrirVentila();
    // }
    // else if (temperaturaCamaraArriba < temperaturaInterior + deltaT && temperaturaInterior > temperaturaInteriorDeseada && temperaturaCamaraArriba >= temperaturaInteriorDeseada)
    // {
    //   Serial.println("mayor se abrira Ventila 4");
    //   abrirVentila();
    // }
    // else if (temperaturaCamaraArriba < temperaturaInterior + deltaT && temperaturaInterior > temperaturaInteriorDeseada)
    // {
    //   Serial.println("mayor se abrira Ventila 2");
    //   abrirVentila();
    // }
    // else if (temperaturaCamaraArriba >= temperaturaInterior + deltaT && temperaturaCamaraArriba >= temperaturaInteriorDeseada && temperaturaInterior >= temperaturaInteriorDeseada)
    // {
    //   Serial.println("mayor se  cerrara ventila 3");
    //   cerrarVentila();
    // }
    // else if (temperaturaCamaraArriba >=temperaturaCamaraAbajo && temperaturaCamaraArriba> temperaturaInteriorDeseada)
    // {
    //   Serial.println("mayor se  cerrara ventila 3");
    //   cerrarVentila();
    // }
    // else if (temperaturaCamaraArriba >=temperaturaCamaraAbajo && temperaturaCamaraArriba <temperaturaInteriorDeseada)
    // {
    //   Serial.println("mayor se  abrira ventila 3");
    //   abrirVentila();
    // }
    // else
    // {
    //   Serial.println("mayor se  cerrara ventila");

    // }

    ///////28-04
    if (
      ((temperaturaCamaraArriba - 2 > temperaturaInteriorDeseada) && (temperaturaCamaraAbajo - 2 > temperaturaInteriorDeseada)) &&
      (temperaturaCamaraArriba - temperaturaCamaraAbajo >= -2 || temperaturaCamaraArriba - temperaturaCamaraAbajo <= 2) && temperaturaCamaraArriba >= 18 && temperaturaInterior + 2 < temperaturaInteriorDeseada)
    {
      Serial.println("mayor se  abrira ventila 3");
      abrirVentila();
    }
    else
    {
      cerrarVentila();
    }
  }
  else if (modov == 20)
  {
    Serial.println("............MANUAL...........");
  }
  while (SerialBT.available())
  {
    String comando = SerialBT.readString();
    Serial.println(comando);
    if (comando.length() >= 4)
    {
      String tipoOffSet = s.separa(comando, '_', 0);
      if (tipoOffSet == "ti")
      {
        offSetTemperaturaInterior = s.separa(comando, '_', 1).toInt();
        Serial.println(offSetTemperaturaInterior);
        EEPROM.write(0, offSetTemperaturaInterior);
        EEPROM.commit();
        Serial.println(offSetTemperaturaInterior);
      }
      if (tipoOffSet == "cr")
      {
        offSetTemperaturaCamaraArriba = s.separa(comando, '_', 1).toInt();
        Serial.println(offSetTemperaturaCamaraArriba);
        EEPROM.write(1, offSetTemperaturaCamaraArriba);
        EEPROM.commit();
        Serial.println(offSetTemperaturaCamaraArriba);
      }
      if (tipoOffSet == "cb")
      {
        offSetTemperaturaCamaraAbajo = s.separa(comando, '_', 1).toInt();
        Serial.println(offSetTemperaturaCamaraAbajo);
        EEPROM.write(2, offSetTemperaturaCamaraAbajo);
        EEPROM.commit();
        Serial.println(offSetTemperaturaCamaraAbajo);
      }
      if (tipoOffSet == "h")
      {
        offSetHumedad = s.separa(comando, '_', 1).toInt();
        Serial.println(offSetHumedad);
        EEPROM.write(3, offSetHumedad);
        EEPROM.commit();
        Serial.println(offSetHumedad);
      }
      if (tipoOffSet == "l")
      {
        SetLuz = s.separa(comando, '_', 1).toInt();
        Serial.println(SetLuz);
        EEPROM.write(4, SetLuz);
        EEPROM.commit();
        Serial.println(SetLuz);
      }
    }
    if (comando == "4")
    {
      modov = 10;
      Serial.println("............AUTOMATICO...........");
    }
    if (comando == "5")
    {
      modov = 20;
      datos = (String(int(temperaturaInterior)) + "_" +
               String(int(humedadDHT)) + "_" +
               String(int(boolPersiana)) + "_" +
               String(int(boolVentila)) + "_" +
               String(int(modov)) + "_" +
               String(int(luz)) + "_" +
               String(int(temperaturaCamaraArriba)) + "_" +
               String(int(temperaturaCamaraAbajo)) + "_" +
               String(int(offSetTemperaturaInterior)) + "_" +
               String(int(offSetTemperaturaCamaraArriba)) + "_" +
               String(int(offSetTemperaturaCamaraAbajo)) + "_" +
               String(int(offSetHumedad)) + "_" +
               String(int(SetLuz)) + "_");

      SerialBT.print(datos);

      delay(200);

      Serial.println("............MANUAL...........");
    }
    if (comando == "9")
    {
      Serial.println("............Datos...........");
      datos = (String(int(temperaturaInterior)) + "_" +
               String(int(humedadDHT)) + "_" +
               String(int(boolPersiana)) + "_" +
               String(int(boolVentila)) + "_" +
               String(int(modov)) + "_" +
               String(int(luz)) + "_" +
               String(int(temperaturaCamaraArriba)) + "_" +
               String(int(temperaturaCamaraAbajo)) + "_" +
               String(int(offSetTemperaturaInterior)) + "_" +
               String(int(offSetTemperaturaCamaraArriba)) + "_" +
               String(int(offSetTemperaturaCamaraAbajo)) + "_" +
               String(int(offSetHumedad)) + "_" +
               String(int(SetLuz)) + "_");

      SerialBT.print(datos);

      delay(200);
    }

    if (comando == "1" && modov == 20)
    {
      boolPersiana = 1;
      datos = (String(int(temperaturaInterior)) + "_" +
               String(int(humedadDHT)) + "_" +
               String(int(boolPersiana)) + "_" +
               String(int(boolVentila)) + "_" +
               String(int(modov)) + "_" +
               String(int(luz)) + "_" +
               String(int(temperaturaCamaraArriba)) + "_" +
               String(int(temperaturaCamaraAbajo)) + "_" +
               String(int(offSetTemperaturaInterior)) + "_" +
               String(int(offSetTemperaturaCamaraArriba)) + "_" +
               String(int(offSetTemperaturaCamaraAbajo)) + "_" +
               String(int(offSetHumedad)) + "_" +
               String(int(SetLuz)) + "_");

      abrirPersiana();

      SerialBT.print(datos);

      delay(200);
    }
    else if (comando == "0" && modov == 20)
    {
      boolPersiana = 0;
      datos = (String(int(temperaturaInterior)) + "_" +
               String(int(humedadDHT)) + "_" +
               String(int(boolPersiana)) + "_" +
               String(int(boolVentila)) + "_" +
               String(int(modov)) + "_" +
               String(int(luz)) + "_" +
               String(int(temperaturaCamaraArriba)) + "_" +
               String(int(temperaturaCamaraAbajo)) + "_" +
               String(int(offSetTemperaturaInterior)) + "_" +
               String(int(offSetTemperaturaCamaraArriba)) + "_" +
               String(int(offSetTemperaturaCamaraAbajo)) + "_" +
               String(int(offSetHumedad)) + "_" +
               String(int(SetLuz)) + "_");

      cerrarPersiana();

      SerialBT.print(datos);

      delay(200);
    }
    else if (comando == "2" && modov == 20)
    {
      boolVentila = 1;
      datos = (String(int(temperaturaInterior)) + "_" +
               String(int(humedadDHT)) + "_" +
               String(int(boolPersiana)) + "_" +
               String(int(boolVentila)) + "_" +
               String(int(modov)) + "_" +
               String(int(luz)) + "_" +
               String(int(temperaturaCamaraArriba)) + "_" +
               String(int(temperaturaCamaraAbajo)) + "_" +
               String(int(offSetTemperaturaInterior)) + "_" +
               String(int(offSetTemperaturaCamaraArriba)) + "_" +
               String(int(offSetTemperaturaCamaraAbajo)) + "_" +
               String(int(offSetHumedad)) + "_" +
               String(int(SetLuz)) + "_");

      abrirVentila();

      SerialBT.print(datos);

      delay(200);
    }
    else if (comando == "3" && modov == 20)
    {
      boolVentila = 0;
      datos = (String(int(temperaturaInterior)) + "_" +
               String(int(humedadDHT)) + "_" +
               String(int(boolPersiana)) + "_" +
               String(int(boolVentila)) + "_" +
               String(int(modov)) + "_" +
               String(int(luz)) + "_" +
               String(int(temperaturaCamaraArriba)) + "_" +
               String(int(temperaturaCamaraAbajo)) + "_" +
               String(int(offSetTemperaturaInterior)) + "_" +
               String(int(offSetTemperaturaCamaraArriba)) + "_" +
               String(int(offSetTemperaturaCamaraAbajo)) + "_" +
               String(int(offSetHumedad)) + "_" +
               String(int(SetLuz)) + "_");
      cerrarVentila();

      SerialBT.print(datos);

      delay(200);
    }
  }
  datos = (String(int(temperaturaInterior)) + "_" +
           String(int(humedadDHT)) + "_" +
           String(int(boolPersiana)) + "_" +
           String(int(boolVentila)) + "_" +
           String(int(modov)) + "_" +
           String(int(luz)) + "_" +
           String(int(temperaturaCamaraArriba)) + "_" +
           String(int(temperaturaCamaraAbajo)) + "_" +
           String(int(offSetTemperaturaInterior)) + "_" +
           String(int(offSetTemperaturaCamaraArriba)) + "_" +
           String(int(offSetTemperaturaCamaraAbajo)) + "_" +
           String(int(offSetHumedad)) + "_" +
           String(int(SetLuz)) + "_");

  delay(1000);
}
