import serial
import time
import collections

import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.lines import Line2D

def getSerialData(self,samples,numData,serialConnection,lines):
    for i in range(numData):
        value = float(serialConnection.readline().decode())
        data[i].append(value)
        lines[i].set_data(range(samples),data[i])


serialPort = 'COM7'
baudRate = 115200
try:
    serialConnection = serial.Serial(serialPort, baudRate)
except:
    print("No se pudo conectar al puerto")

samples = 100
sampleTime = 200
numData = 4

#limites grafica

xmin = 0
xmax = samples
ymin = [1,10]
ymax = [5,15]
lines = []
data = []

for i in range(numData):
    data.append(collections.deque([0]*samples, maxlen=samples))
    lines.append(Line2D([],[],color='blue'))


fig = plt.figure('MPU9250')

#ax0 = matplotlib.pyplot.figure.add_subplot

ax0 = fig.add_subplot(1,2,1,xlim=(xmin,xmax),ylim=(ymin[0],ymax[0]))
ax0.title.set_text('Eje X')
ax0.set_xlabel('Muestras')
ax0.set_ylabel('Nivel')
ax0.grid()
ax0.add_line(lines[0])

ax1 = fig.add_subplot(1,2,2,xlim=(xmin,xmax),ylim=(ymin[1],ymax[1]))
ax1.title.set_text('Eje Y')
ax1.set_xlabel('Muestras')
ax1.set_ylabel('Nivel')
ax1.grid()
ax1.add_line(lines[1])

fig.set_size_inches(10,6)

anim = animation.FuncAnimation(fig,getSerialData,fargs=(samples,numData,serialConnection,lines),interval=sampleTime)
plt.show()
