// https://www.aeq-web.com/ttgo-esp32-lora-neo-6-gps-board-setup-serial-read/

#include <HardwareSerial.h>
#include "BluetoothSerial.h"

BluetoothSerial BT; // Objeto Bluetooth

#define RXPin 34
#define TXPin 12
#define GPSBaud 9600

HardwareSerial GPS(2);

String leerString;

void setup() {
  Serial.begin(9600); // Inicia puerto Serial
  BT.begin("T-Beam"); // Nombre de su dispositivo Bluetooth y en modo esclavo
  GPS.begin(GPSBaud, SERIAL_8N1, RXPin, TXPin); // Inicia otro puerto serial para el GPS
}

void loop() {
  leerString = GPS.readStringUntil(13); // NMEA 0183 retorno de carro = 13
  leerString.trim(); // Elimina espacios en blanco

  if (leerString.startsWith("$GPGGA")) {

    String gps_lat_g = separarString(leerString, 2);  // Latitud en grados y minutos
    String gps_lat_o = separarString(leerString, 3);  // Orientacion (N o S)
    String gps_lon_g = separarString(leerString, 4);  // Longitud en grados y minutos
    String gps_lon_o = separarString(leerString, 5);  // Orientacion (E o W)
    String gps_sat = separarString(leerString, 7);    // Numero de satelites
    String gps_hgt = separarString(leerString, 9);    // Altura

    Serial.print(leerString);
    BT.println(leerString);
    Serial.println("");
    Serial.print("LAT: ");
    Serial.print(gps_lat_g);
    Serial.print(" LON: ");
    Serial.print(gps_lon_g);
    Serial.print(" HEIGHT: ");
    Serial.print(gps_hgt);
    Serial.print(" SAT: ");
    Serial.println(gps_sat);

    float latitude = convertirCoordenadas(gps_lat_g.toFloat(), gps_lat_o);
    float longitude = convertirCoordenadas(gps_lon_g.toFloat(), gps_lon_o);

    Serial.print(latitude, 6);
    BT.print(latitude);
    Serial.print(",");
    BT.print(",");
    Serial.println(longitude, 6);
    BT.println(longitude);
  }
}

String separarString(String input, int index) {
  int finder = 0; // Bandera que aumenta al encontrar una coma
  int strIndex[] = { 0, -1 }; // Limites del string encontrado
  int maxIndex = input.length() - 1; // Indice maximo de la cadena
  Serial.println(maxIndex);
  BT.println(maxIndex);
  for (int i = 0; i <= maxIndex && finder <= index; i++) { // Este ciclo recorre la cadena por completo
    if (input.charAt(i) == ',' || i == maxIndex) { // Se cumple cuando se encuentra una coma
      finder++;
      strIndex[0] = strIndex[1] + 1;
      if (i == maxIndex) {
        strIndex[1] = i + 1;
      } else {
        strIndex[1] = i;
      }
    }
  }
  if (finder > index) {
    return input.substring(strIndex[0], strIndex[1]); // devuelve la cadena con indice minimo y maximo
  } else {
    return "";
  }
}

float convertirCoordenadas(float deg_min, String orientation) {
  double gps_min = fmod((double)deg_min, 100.0);
  int gps_deg = deg_min / 100;
  double dec_deg = gps_deg + ( gps_min / 60 );
  if (orientation == "W" || orientation == "S") {
    dec_deg = 0 - dec_deg;
  }
  return dec_deg;
}
