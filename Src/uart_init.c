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

void USART1_Init(void){

    RCC_GPIO_CLK_ENABLE(GPIOB_CLK_EN);
    RCC_UART_CLK_ENABLE_APB2(USART1_CLK_EN);

    /* Configure PB6 for USART1_TX */
    GPIOB_AFR_SEL(AFR_LOW, PIN_6, USART1_TX);
    GPIOB_MODER_SEL(PIN_6, ALT_SEL);

    /* Configure USART1 */
    USART1_BAUD_SELECT(BAUD_9600);
    USART1_CR1_SEL(USART_TX_ENBL | USART_WORD_8BIT);
    USART1_CR2_SEL(USART_STOP_ONE_BIT);
    USART1_CR3_SEL(USART_NO_FLOW_CONTROL);

    /* Enable USART3 after configuration complete*/
    USART1_CR1_SEL(USART_ENABLE);
}

void USART2_Init(void){

    RCC_GPIO_CLK_ENABLE(GPIOA_CLK_EN);
    RCC_UART_CLK_ENABLE_APB1(USART2_CLK_EN);

    /* Configure PA2 for USART2_TX */
    GPIOA_AFR_SEL(AFR_LOW, PIN_2, USART2_TX);
    GPIOA_MODER_SEL(PIN_2, ALT_SEL);

    /* Configure USART2 */
    USART2_BAUD_SELECT(BAUD_9600);
    USART2_CR1_SEL(USART_TX_ENBL | USART_WORD_8BIT);
    USART2_CR2_SEL(USART_STOP_ONE_BIT);
    USART2_CR3_SEL(USART_NO_FLOW_CONTROL);

    /* Enable USART2 after configuration complete*/
    USART2_CR1_SEL(USART_ENABLE);
}

void USART3_Init(void){

    RCC_GPIO_CLK_ENABLE(GPIOC_CLK_EN);
    RCC_UART_CLK_ENABLE_APB1(USART3_CLK_EN);

    /* Configure PC10 for USART3_TX */
    /* WARNING: Remember to select AFR_HIGH for pin 8 - 15! */
    /* WARNING: PB10 can also be used for USART3_TX.
     * However, with the 64pin package, PB11 does not exist for USART3_RX.
     */
    GPIOC_AFR_SEL(AFR_HIGH, PIN_10, USART3_TX);
    GPIOC_MODER_SEL(PIN_10, ALT_SEL);

    /* Configure USART3 */
    USART3_BAUD_SELECT(BAUD_9600);
    USART3_CR1_SEL(USART_TX_ENBL | USART_WORD_8BIT);
    USART3_CR2_SEL(USART_STOP_ONE_BIT);
    USART3_CR3_SEL(USART_NO_FLOW_CONTROL);

    /* Enable USART3 after configuration complete*/
    USART3_CR1_SEL(USART_ENABLE);
}