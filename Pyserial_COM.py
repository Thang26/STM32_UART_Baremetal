# Overall purpose of this program is to graph the data that is being transmitted from the STM32F446RE micro.
# This program reads the data present at the PC's COM port.
# This data is transmitted from the TTL CP2102 chip UART->USB.
# The TTL CP2102's job is to receive the data from STM32F446RE via UART, and output it to the PC via USB.

import serial
import matplotlib.pyplot as plt
from itertools import count
from matplotlib.animation import FuncAnimation
from matplotlib import style

# Read the UART data being streamed by CP2102 into COM5.
COMvalue = serial.Serial('COM5', 9600)

# Function to read data from COM5 port.
def getData():
    data = COMvalue.read()
    return data

style.use('fivethirtyeight')

# Counts upward by 1, serves as our x-axis basis
index = count()
max_length = 50 # Max length defines the size of the x-axis.
xs, ys = [], []

# Creating the intial plot figure.
fig = plt.figure()
ax = fig.add_subplot(1,1,1)
ax.set_xlim([0, max_length])
ax.set_ylim([0,15])

image, = ax.plot([],[])

# Update function to update the plot, required by matplotlib FuncAnimation.
# Not sure, but I think "i" is the frame # that the animation is on.
def update(i):

    # Gets our next values for the x and y axis.
    xs.append(next(index))
    ys.append(int(getData()))

    # Set those new values to be plotted.
    image.set_data(xs, ys)

    # Control code to move the x-axis when it exceeds the defined max length.
    if i > max_length:
        ax.set_xlim(i-max_length, i)
    else:
        ax.set_xlim(0, max_length)

    return image,

ani = FuncAnimation(fig, update, interval = 30, blit=False)

plt.tight_layout()
plt.show()
