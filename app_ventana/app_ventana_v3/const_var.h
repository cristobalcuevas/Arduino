/*************************************** PINES ***************************************/
#define DHTtype DHT11
const uint8_t sensorLuz = 35;
const uint8_t DHTpin = 15;
const uint8_t pinPersiana = 14;     // SERVO
const uint8_t pinVentila = 13;      // SERVO
const uint8_t pinCamaraArriba = 27; // TEMPERATURA 2
const uint8_t pinCamaraAbajo = 26;  // TEMPERATURA 1

/************************************* VARIABLES *************************************/

// DS18B20
float temperaturaCamaraArriba = 0, temperaturaCamaraAbajo = 0, temperaturaCamara = 0;
// DHT11
uint8_t temperaturaInteriorDeseada = 25;
float temperaturaInterior = 0, humedadInterior = 0;
// LDR
uint16_t luz = 0, setLuz = 2040;
// RTC
String fechaFormateada = "";
// VENTILA Y PERSIANA
bool estadoVentila, estadoPersiana;
uint8_t servoPersianaCerrada = 50, servoPersianaAbierta = 170, servoVentilaCerrada = 35, servoVentilaAbierta = 5;
// MODO DE VENTANA
uint8_t modoVentana = 10;
String comando = "";
// DATOS
String datosSD = "", datosBT = "";
