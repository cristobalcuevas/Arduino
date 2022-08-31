#ifndef microsd_h
#define microsd_h

#include <Arduino.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"

class microSD {
  private:
  public:
    microSD();
    void begin(void);
    void saveDataSD(String dataMessage);
    void writeFile(fs::FS &fs, const char * path, const char * message);
    void appendFile(fs::FS &fs, const char * path, const char * message);
};

#endif
