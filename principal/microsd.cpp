#include "microsd.h"

microSD::microSD() {
}
void microSD::begin(void) {
  SD.begin();
  File file = SD.open("/encoder.csv");
  writeFile(SD, "/encoder.csv", "Date Time Value");
  file.close();
}
void microSD::saveDataSD(String dataMessage) {
  appendFile(SD, "/encoder.csv", dataMessage.c_str());
}
void microSD::writeFile(fs::FS &fs, const char * path, const char * message) {
  File file = fs.open(path, FILE_WRITE);
  file.print(message);
  file.close();
}
void microSD::appendFile(fs::FS &fs, const char * path, const char * message) {
  File file = fs.open(path, FILE_APPEND);
  file.print(message);
  file.close();
}
