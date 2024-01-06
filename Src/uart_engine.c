/*
 * UART_Engine.c
 *
 *  Created on: Dec 21, 2023
 *      Author: Thang Pham
 * 
 *  File that contains all of the UART associated functions and operations.
 * 
 */

#include "common.h"
#include "uart_init.h"

/*
 * Function to write data onto the UART1 data register to be sent out.
 */

void USART1_Write(int data){

    /* Wait until the TX Buffer is empty*/
    while (!(USART1_TX_BUFF_READY)) {}
    USART1->DR = (data & 0xFF);
}

/*
 * Function to write a string of data onto the UART2 data register to be sent out.
 */

void USART1_WriteString(char *data){

    while(*data != '\0'){
        
        /* Wait until the TX Buffer is empty*/
        while (!(USART1_TX_BUFF_READY)) {}
        USART1_Write((int)(*data));
        data++;
    }
}

/*
 * Function to write data onto the UART2 data register to be sent out.
 */

void USART2_Write(int data){

    /* Wait until the TX Buffer is empty*/
    while (!(USART2_TX_BUFF_READY)) {}
    USART2->DR = (data & 0xFF);
}

/*
 * Function to write a string of data onto the UART2 data register to be sent out.
 */

void USART2_WriteString(char *data){

    while(*data != '\0'){
        
        /* Wait until the TX Buffer is empty*/
        while (!(USART2_TX_BUFF_READY)) {}
        USART2_Write((int)(*data));
        data++;
    }
}

/*
 * Function to write data onto the UART3 data register to be sent out.
 */

void USART3_Write(UINT8 data){

    /* Wait until the TX Buffer is empty*/
    while (!(USART3_TX_BUFF_READY)) {}
    USART3->DR = (data & 0xFF);
}

/*
 * Function to write a string of data onto the UART3 data register to be sent out.
 */

void USART3_WriteString(char *data){

    while(*data != '\0'){
        
        /* Wait until the TX Buffer is empty*/
        while (!(USART3_TX_BUFF_READY)) {}
        USART3_Write((UINT8)(*data));
        data++;
    }
}

//TODO: Write a description of what this function does.
void ENCODE_FUNC(UINT16 dataValue, UINT8 *first_send, UINT8 *second_send, UINT8 *first_transmit, UINT8 *second_transmit){

    UINT8 bit_array[10] = {};
    const int FIRST_THREE_DIGITS = 3;
    int index;

    /*  Converts hex values into an array of bits that we can individually access. */
    for(index = 9; index >= 0; --index){
        bit_array[index] = (bool)(dataValue & (1U << index));
    }

    /*  Split the array of bits into two separate transmissions to send. */
    for(index = 0; index < 10; index++){

        /*
         *  This part puts the individual bits of the data we're trying to send into their correct slots of the two transmission arrays.
         *  Looks at the first three entries of bit_array and puts that into the first transmission (slot 5 - 7).
         */
        if(index < FIRST_THREE_DIGITS){
            first_send[5+index] = bit_array[index];
        }

        /*  Looks at the remaining seven entries of bit_array and puts that into the second transmission (slot 1 - 7). */
        else{
            second_send[index-2] = bit_array[index];
        }
    }

    /*
     *  Recode the transmission to be a Hex value, ready for UART to transmit.
     *  How it's recoding is that its doing binary addition.
     *  Example: 1,0,1,0 is 1000 + 000 + 10 + 0 = 1010.
     */
    *first_transmit = 0;
    *second_transmit = 0;

    for(index = 0; index < SIZE_OF_BYTE; index++){
        *first_transmit += (first_send[index] << (7 - index));
        *second_transmit += (second_send[index] << (7 - index));
    }
}