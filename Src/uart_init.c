/*
 * UART_Init.c
 *
 *  Created on: Dec 21, 2023
 *      Author: Thang Pham
 * 
 *  File to set up and configure the UART peripherals.
 * 
 */

#include "common.h"
#include "port_init.h"
#include "uart_init.h"

void USART2_Init(void){

    RCC_GPIO_CLK_ENABLE(GPIOA_CLK_EN);
    RCC_UART_CLK_ENABLE(USART2_CLK_EN);

    /* Configure PA2 for USART2_TX */
    GPIOA_AFR_SEL(AFR_LOW, PIN_2, USART2_TX);
    GPIOA_MODER_SEL(PIN_2, ALT_SEL);

    /* Configure USART2 */
    USART2_BAUD_SELECT(BAUD_9600);
    USART2_CR1_SEL(USART2_TX_ENBL | USART2_WORD_8BIT);
    USART2_CR2_SEL(USART2_STOP_ONE_BIT);
    USART2_CR3_SEL(USART2_NO_FLOW_CONTROL);

    /* Enable USART2 after configuration complete*/
    USART2_CR1_SEL(USART2_ENABLE);

}