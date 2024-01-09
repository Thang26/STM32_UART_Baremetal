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
serial.PARITY_NONE
serial.EIGHTBITS
serial.STOPBITS_ONE

# Function to read data from COM5 port.
def DECODE_FUNC():

    #   Expand on this later cause I'm tired. But basically, it read the second transmission FIRST,
    #   then paired it up with the first transmission of the NEXT packet.
    #   Was very hard to detect because between 690 and 693, the second packet does not differ.
    binary_list = []
    first_transmission = []
    second_transmission = []
    ADC_value = []


    flag = 0
    firstTransmit_NOT_EMPTY = 0
    
    while flag != 2:
        data = bin(int((COMvalue.read()).hex(), 16))[2:].zfill(8)

        # @Debug Code
        print("\n" + "Data is obtained.")
        print(data)

        # Splits the binary data into individual bits within a list. This is so each individual bit can be accessed.
        binary_list = [int(x) for x in str(data)]
        
        if (binary_list[0] == 0):
            first_transmission = binary_list[0:8]
            
            # @Debug Code
            print("First transmission got assigned.")
            print(first_transmission)

            # TODO add description
            if(firstTransmit_NOT_EMPTY == 0):
                flag += 1
                firstTransmit_NOT_EMPTY = 1

        elif(firstTransmit_NOT_EMPTY == 1):
            second_transmission = binary_list[0:8]
            
            # @Debug Code
            print("Second transmission got assigned.")
            print(second_transmission)

            flag += 1
            firstTransmit_NOT_EMPTY = 0

    # @Debug Code
    # For syntax of list[-1:-9:-1], it's actually [-9, -8, -7, -6 ... -1] and it's interating thu by doing element -1 + (-1)
    print("\n" + "Printing first_transmission[-1:-4:-1]: " + str(first_transmission[-1:-4:-1]))
    print("\n" + "Printing second_transmission[-1:-8:-1]: " + str(second_transmission[-1:-8:-1]))
    
    ADC_value = convert((second_transmission[-1:-8:-1] + first_transmission[-1:-4:-1]))

    # @Debug Code
    print("\n" + "Printing ADC value")
    print(ADC_value)

    return ADC_value

# Function to join together the list of individual binary values into a singular binary.
def convert(list):
     
    # Converting integer list to string list
    s = [str(i) for i in list]
     
    # Join list items then convert them into base 10.
    result = int("".join(s), base=2)
     
    return(result)

# @Debug Code
def main():
    while True:
        DECODE_FUNC()
main()


# # This portion of the code is responsible for graphing the ADC values.
# # This uses matplotlib to do the graphing.
# # It also has an animation portion that moves the x-axis dynamically with the data.
# style.use('fivethirtyeight')

# # Counts upward by 1, serves as our x-axis basis
# index = count()
# max_length = 1000 # Max length defines the size of the x-axis.
# xs, ys = [], []

# # Creating the intial plot figure.
# fig = plt.figure()
# ax = fig.add_subplot(1,1,1)
# ax.set_xlim([0, max_length])
# ax.set_ylim([0,1024])

# image, = ax.plot([],[])

# # Update function to update the plot, required by matplotlib FuncAnimation.
# # Not sure, but I think "i" is the frame # that the animation is on.
# def update(i):

#     # Gets our next values for the x and y axis.
#     xs.append(next(index))
#     ys.append(DECODE_FUNC())

#     # Set those new values to be plotted.
#     image.set_data(xs, ys)

#     # Control code to move the x-axis when it exceeds the defined max length.
#     if i > max_length:
#         ax.set_xlim(i-max_length, i)
#     else:
#         ax.set_xlim(0, max_length)

#     return image,

# ani = FuncAnimation(fig, update, interval = 10, blit=False)

# plt.tight_layout()
# plt.show()
