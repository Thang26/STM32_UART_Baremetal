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
 * Function to write data onto the UART data register to be sent out.
 */

void USART2_Write(int data){

    /* Wait until the TX Buffer is empty*/
    while (!(USART2_TX_BUFF_READY)) {}
    USART2->DR = (data & 0xFF);
}

/*
 * Function to write a string of data onto the UART data register to be sent out.
 */

void USART2_WriteString(char *data){

    while(*data != '\0'){
        
        /* Wait until the TX Buffer is empty*/
        while (!(USART2_TX_BUFF_READY)) {}
        USART2_Write((int)(*data));
        data++;
    }
}