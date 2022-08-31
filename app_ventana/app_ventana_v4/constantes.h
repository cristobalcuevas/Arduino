/************************** PINES **************************/
#define DHTtype DHT11
const uint8_t pinLDR = 35;
const uint8_t pinDHT = 15;
const uint8_t pinCamaraArriba = 27; // TEMPERATURA 2
const uint8_t pinCamaraAbajo = 26;  // TEMPERATURA 1
/************************ VARIABLES ************************/
float temperaturaCamara = 0;
uint8_t temperaturaInteriorDeseada = 25;
uint8_t setLuz = 3;
