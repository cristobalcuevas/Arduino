#include <Arduino.h>
#include "bluetooth.h"
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth no esta activado, abrir 'menuconfig' y activarlo.
#endif

BluetoothSerial SerialBT;

bt::bt(){
}
void bt::begin(void) {
  SerialBT.begin("BT001");
}
void bt::printDataBT(String dataMessage) {
  SerialBT.print(dataMessage);
}
