@echo OFF 
title Copiar librerias
:: Section 1: Librerias en Documentos
echo ===========
echo DOCUMENTOS
echo ===========
robocopy /e /v %cd%\OneWire %USERPROFILE%\Documents\Arduino\libraries\OneWire
robocopy /e /v %cd%\DallasTemperature %USERPROFILE%\Documents\Arduino\libraries\DallasTemperature
robocopy /e /v %cd%\ServoESP32 %USERPROFILE%\Documents\Arduino\libraries\ServoESP32
robocopy /e /v %cd%\DHT_sensor_library %USERPROFILE%\Documents\Arduino\libraries\DHT_sensor_library
robocopy /e /v %cd%\RTClib %USERPROFILE%\Documents\Arduino\libraries\RTClib
robocopy /e /v %cd%\Adafruit_BusIO %USERPROFILE%\Documents\Arduino\libraries\Adafruit_BusIO
robocopy /e /v %cd%\Adafruit_Unified_Sensor %USERPROFILE%\Documents\Arduino\libraries\Adafruit_Unified_Sensor
:: Section 2: Librerias en AppData
echo ===========
echo APPDATA
echo ===========
robocopy /e /v %cd%\Wire %LOCALAPPDATA%\Arduino15\libraries\Wire
robocopy /e /v %cd%\BluetoothSerial %LOCALAPPDATA%\Arduino15\libraries\BluetoothSerial
robocopy /e /v %cd%\FS %LOCALAPPDATA%\Arduino15\libraries\FS
robocopy /e /v %cd%\SD %LOCALAPPDATA%\Arduino15\libraries\SD
robocopy /e /v %cd%\SPI %LOCALAPPDATA%\Arduino15\libraries\SPI
PAUSE