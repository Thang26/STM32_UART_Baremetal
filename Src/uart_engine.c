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