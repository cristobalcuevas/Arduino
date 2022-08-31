#include "GY_91.h"

#define AK8963_ADDRESS  0x0C
#define AK8963_RA_HXL   0x03
#define AK8963_RA_CNTL1 0x0A
#define AK8963_RA_ASAX  0x10

#define MPU9250_ADDR_ACCELCONFIG  0x1C
#define MPU9250_ADDR_INT_PIN_CFG  0x37
#define MPU9250_ADDR_ACCEL_XOUT_H 0x3B
#define MPU9250_ADDR_GYRO_XOUT_H  0x43
#define MPU9250_ADDR_PWR_MGMT_1   0x6B
#define MPU9250_ADDR_WHOAMI       0x75

//Funcion auxiliar lectura
uint8_t GY_91::i2cRead(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data)
{
  myWire->beginTransmission(Address);
  myWire->write(Register);
  myWire->endTransmission();
  myWire->requestFrom(Address, Nbytes);
  uint8_t index = 0;
  while (myWire->available())
    Data[index++] = myWire->read();
}

// Funcion auxiliar de escritura
uint8_t GY_91::i2cWriteByte(uint8_t Address, uint8_t Register, uint8_t Data)
{
  myWire->beginTransmission(Address);
  myWire->write(Register);
  myWire->write(Data);
  myWire->endTransmission();
}

GY_91::GY_91(uint8_t Address):
  Address(Address) {
  accelRange = 0;
  gyroRange  = 0;
  myWire = NULL;
}

void GY_91::setWire(TwoWire* wire) {
  myWire = wire;
}

// Leer id
uint8_t GY_91::readId(uint8_t *id) {
  beginWireIfNull();
  return i2cRead(Address, MPU9250_ADDR_WHOAMI, 1, id);
}

// Revisar inicializacion de la libreria Wire
void GY_91::beginWireIfNull() {
  if (myWire == NULL) {
    myWire = &Wire;
    myWire->begin();
  }
}

// Inicializacion del acelerometro
void GY_91::beginAccel(uint8_t mode) {
  beginWireIfNull();
  switch (mode) {
    case ACC_FULL_SCALE_2_G:
      accelRange = 2.0;
      break;
    case ACC_FULL_SCALE_4_G:
      accelRange = 4.0;
      break;
    case ACC_FULL_SCALE_8_G:
      accelRange = 8.0;
      break;
    case ACC_FULL_SCALE_16_G:
      accelRange = 16.0;
      break;
    default:
      return; // Return without writing invalid mode
  }
  i2cWriteByte(Address, MPU9250_ADDR_ACCELCONFIG, mode);
  delay(10);
}

uint8_t GY_91::accelUpdate() {
  return i2cRead(Address, MPU9250_ADDR_ACCEL_XOUT_H, 6, accelBuff);
}

float GY_91::accelGet(uint8_t highIndex, uint8_t lowIndex) {
  int16_t v = ((int16_t) accelBuff[highIndex]) << 8 | accelBuff[lowIndex];
  return ((float) - v) * accelRange / (float) 0x8000; // (float) 0x8000 == 32768.0
}

float GY_91::accelX() {
  return accelGet(0, 1);
}

float GY_91::accelY() {
  return accelGet(2, 3);
}

float GY_91::accelZ() {
  return accelGet(4, 5);
}

//Inicializacion del giroscopio
void GY_91::beginGyro(uint8_t mode) {
  beginWireIfNull();
  switch (mode) {
    case GYRO_FULL_SCALE_250_DPS:
      gyroRange = 250.0;
      break;
    case GYRO_FULL_SCALE_500_DPS:
      gyroRange = 500.0;
      break;
    case GYRO_FULL_SCALE_1000_DPS:
      gyroRange = 1000.0;
      break;
    case GYRO_FULL_SCALE_2000_DPS:
      gyroRange = 2000.0;
      break;
    default:
      return; // Return without writing invalid mode
  }
  i2cWriteByte(Address, 27, mode);
  delay(10);
}

uint8_t GY_91::gyroUpdate() {
  return i2cRead(Address, MPU9250_ADDR_GYRO_XOUT_H, 6, gyroBuff);
}

float GY_91::gyroGet(uint8_t highIndex, uint8_t lowIndex) {
  int16_t v = ((int16_t) gyroBuff[highIndex]) << 8 | gyroBuff[lowIndex];
  return ((float) - v) * gyroRange / (float) 0x8000;
}

float GY_91::gyroX() {
  return gyroGet(0, 1);
}

float GY_91::gyroY() {
  return gyroGet(2, 3);
}

float GY_91::gyroZ() {
  return gyroGet(4, 5);
}
