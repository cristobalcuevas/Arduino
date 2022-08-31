#mostrar valores leidos de puerto serial
import serial

arduinoData = serial.Serial('COM7', 115200);

while True:
    arduinoString = float(arduinoData.readline().decode())
    print (arduinoString)
