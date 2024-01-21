# Overall purpose of this program is to graph the data that is being transmitted from the STM32F446RE micro.
# This program reads the data present at the PC's COM port.
# This data is transmitted from the TTL CP2102 chip UART->USB.
# The TTL CP2102's job is to receive the data from STM32F446RE via UART, and output it to the PC via USB.

# The purpose of this DEBUG file is to test the probability of an error transmission in the following two cases:
# a) The STM32 & CP2102 chip is transmitting in a noisy environment.
# b) The varying baud rates for UART transmission that the STM32 is capable of.
# 
# This program does two things:
# 1) Provide print statements for dev to see received values in real time.
# 2) Provide a file of # of wrong transmissions after x amount of samples received.

import serial
from bisect import bisect_left

#
#   OBTAIN ADC VALUE FROM UART PORTION
#

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
    global FAIL_COUNTER


    flag = 0
    firstTransmit_NOT_EMPTY = 0
    
    while flag != 2:
        data = bin(int((COMvalue.read()).hex(), 16))[2:].zfill(8)

        # @Debug Code
        # print("\n" + f"Data is obtained = {data}")

        # Splits the binary data into individual bits within a list. This is so each individual bit can be accessed.
        binary_list = [int(x) for x in str(data)]
        
        if (binary_list[0] == 0):
            first_transmission = binary_list[0:8]
            
            # @Debug Code
            # print("First transmission got assigned.")
            # print(first_transmission)

            # TODO add description
            if(firstTransmit_NOT_EMPTY == 0):
                flag += 1
                firstTransmit_NOT_EMPTY = 1

            else:
                print("Previous first transmit was overwritten!")
                FAIL_COUNTER += 1

        elif(firstTransmit_NOT_EMPTY == 1):
            second_transmission = binary_list[0:8]
            
            # @Debug Code
            # print("Second transmission got assigned.")
            # print(second_transmission)

            flag += 1
            firstTransmit_NOT_EMPTY = 0

        else:
            print("Second transmit was received prematurely and was skipped!")
            FAIL_COUNTER += 1

    # @Debug Code
    # For syntax of list[-1:-9:-1], it's actually [-9, -8, -7, -6 ... -1] and it's interating thu by doing element -1 + (-1)
    # print("\n" + "Printing first_transmission[-1:-4:-1]: " + str(first_transmission[-1:-4:-1]))
    # print("\n" + "Printing second_transmission[-1:-8:-1]: " + str(second_transmission[-1:-8:-1]))
    
    ADC_value = convert((second_transmission[-1:-8:-1] + first_transmission[-1:-4:-1]))

    # @Debug Code
    # print("\n" + f"Printing ADC value: {ADC_value}")

    return ADC_value

# Function to join together the list of individual binary values into a singular binary.
def convert(list):
     
    # Converting integer list to string list
    s = [str(i) for i in list]
     
    # Join list items then convert them into base 10.
    result = int("".join(s), base=2)
     
    return(result)



#
#   DEBUG PORTION
#

SUCCESS_COUNTER = 0
FAIL_COUNTER = 0

SINE_WAVE = [
    0, 1, 3, 6, 11, 17, 24, 33, 43, 54, 66,
    80, 94, 110, 126, 143, 162, 180, 200, 220, 240,
    261, 283, 304, 326, 348, 370, 392, 413, 435, 456,
    476, 496, 516, 534, 553, 570, 586, 602, 616, 630,
    642, 653, 663, 672, 679, 685, 690, 693, 695, 696
    ]

#Changed 6 to 7
#Changed 326 to 340
#Changed 616 to 625
# SINE_WAVE = [
#     0, 1, 3, 7, 11, 17, 24, 33, 43, 54, 66,
#     80, 94, 110, 126, 143, 162, 180, 200, 220, 240,
#     261, 283, 304, 340, 348, 370, 392, 413, 435, 456,
#     476, 496, 516, 534, 553, 570, 586, 602, 625, 630,
#     642, 653, 663, 672, 679, 685, 690, 693, 695, 696
#     ]

# Binary search function 
def SEARCH_ELEMENT(ARR, TARGET_VAL):
    
    INDEX = bisect_left(ARR, TARGET_VAL)

    # ARR[INDEX] == TARGET_VAL checks if the returned index is equal to TARGET_VAL.
    # If TRUE, that indicates that the TARGET_VAL exists within array and we just returned its index #.

    # In the case where the TARGET_VAL is:
    # 1) Not present within the array.
    # 2) Larger than all values within the array.
    # Bisect_left value return an index # = (right most index # of array + 1).
    # This causes IndexError: list index out of range for ARR[INDEX] == TARGET_VAL check.
    # Solution: INDEX != len(ARR) returns -1 and indicates that TARGET_VAL is not found before ARR[INDEX] == TARGET_VAL is ran.
    
    if INDEX != len(ARR) and ARR[INDEX] == TARGET_VAL:
        return INDEX
    
    else:
        return -1

# Function tries to figure out which in the list we just obtained the UART data packet for.
def SYNC_FUNC():

    for _ in range (100):

        TARGET_NUM_TO_SYNC = DECODE_FUNC()

        INDEX_RET_VAL = SEARCH_ELEMENT(SINE_WAVE, TARGET_NUM_TO_SYNC)

        if INDEX_RET_VAL != -1:
            print(f"Data used for sync = {TARGET_NUM_TO_SYNC}")
            return INDEX_RET_VAL
        
        else:
            print("SYNC failed, trying again...")
    
    # We failed to sync. Exiting program.
    INDEX_RET_VAL = -1
    return INDEX_RET_VAL

# @Debug Code
def main():

    global SUCCESS_COUNTER, FAIL_COUNTER
    TOTAL_TEST_TO_DO = 1000000

    # SYNC PORTION
    ARRAY_INDEX = SYNC_FUNC()

    if ARRAY_INDEX == -1:
        print("We failed to sync. Exiting program.")
        exit()

    else:
        print("Sync is successful, data located within array.")
        print(f"ARRAY_INDEX = {ARRAY_INDEX}, which is = {SINE_WAVE[ARRAY_INDEX]}")

        # Resets both counters to clear any results from SYNC function.
        SUCCESS_COUNTER = 0
        FAIL_COUNTER = 0


    # TEST PORTION
    for ITERATION in range(TOTAL_TEST_TO_DO):
        
        ADC_VALUE = DECODE_FUNC()

        ARRAY_INDEX = SEARCH_ELEMENT(SINE_WAVE, ADC_VALUE)

        if ARRAY_INDEX == -1:
            FAIL_COUNTER += 1
            print("Error value has been received!")
        
        else:
            SUCCESS_COUNTER += 1

        progress_bar(ITERATION, TOTAL_TEST_TO_DO)

    print("\n\nError testing has finished!")
    print(f"SUCCESS COUNTER = {SUCCESS_COUNTER}")
    print(f"FAIL COUNTER = {FAIL_COUNTER}")

def progress_bar(ITERATION_VAL, TOTAL_VAL):
    
    percentage = round((ITERATION_VAL / TOTAL_VAL) * 100, 3)
    print(f"Test is {percentage}% finished!")

main()