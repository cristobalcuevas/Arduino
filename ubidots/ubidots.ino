
#include "Ubidots.h"

/****************************************
 * Define Instances and Constants
 ****************************************/

const char* UBIDOTS_TOKEN = "BBFF-TdovJ36LsDm6lpq1ZdwshPpWk8s1Um";  // Put here your Ubidots TOKEN
const char* WIFI_SSID = "CLAGOS";      // Put here your Wi-Fi SSID
const char* WIFI_PASS = "50863835";      // Put here your Wi-Fi password
Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);
// Ubidots ubidots(UBIDOTS_TOKEN, UBI_TCP); // Uncomment to use TCP
// Ubidots ubidots(UBIDOTS_TOKEN, UBI_UDP); // Uncomment to use UDP

/****************************************
 * Auxiliar Functions
 ****************************************/

// Put here your auxiliar functions

/****************************************
 * Main Functions
 ****************************************/

void setup() {
  Serial.begin(115200);
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);
  // ubidots.setDebug(true);  // Uncomment this line for printing debug messages
}

void loop() {
  float value1 = random(7, 30);
  float value2 = random(30, 50);
  float value3 = random(300, 400);
  ubidots.add("Variable_Name_One", value1);  // Change for your variable name
  ubidots.add("Variable_Name_Two", value2);
  ubidots.add("Variable_Name_Three", value3);

  bool bufferSent = false;
  bufferSent = ubidots.send();  // Will send data to a device label that matches the device Id

  if (bufferSent) {
    // Do something if values were sent properly
    Serial.println("Values sent by the device");
  }

  delay(5000);
}
