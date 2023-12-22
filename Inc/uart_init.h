/*
 * UART_Init.h
 *
 *  Created on: Dec 21, 2023
 *      Author: Thang Pham
 * 
 *  Header file associated with the init of UART peripheral.
 *  Contains macros for the init functions.
 * 
 */

/*
 *  Macro for UART Clock Initialization
 */

#define USART2_CLK_EN   (1U << 17)
#define USART3_CLK_EN   (1U << 18)
#define UART4_CLK_EN    (1U << 19)
#define UART5_CLK_EN    (1U << 20)

/*
 *  Macro for UART (APB1ENR) CLK Enable
 */

#define RCC_UART_CLK_ENABLE(UART_X)             SET_BIT(RCC->APB1ENR,UART_X)

/*
 *  Macro for UART Peripheral Select
 */

#define USART2_TX       (0x7)

/*
 *  Macro for UART Baud Rate Register
 */

/* 
 *  Table of values for Baud Rate with OVERSAMPL = 16 and CLK = 16MHz.
 *  Formula: USARTDIV = Fck / 16 * Baud
 */

#define BAUD_9600       0x0683
#define BAUD_19200      0x0341
#define BAUD_57600      0x0116
#define BAUD_115200     0x008B

#define USART2_BAUD_SELECT(BAUD_RATE)      HARD_SET_BIT(USART2->BRR, BAUD_RATE) 

/*
 *  Macro for UART Control 1 Register
 */

#define USART2_TX_DISBL     (0U << 3)
#define USART2_TX_ENBL      (1U << 3)
#define USART2_WORD_8BIT    (0U << 12)
#define USART2_WORD_9BIT    (1U << 12)
#define USART2_DISABLE      (0U << 13)
#define USART2_ENABLE       (1U << 13)

#define USART2_CR1_SEL(SEL)                 SET_BIT(USART2->CR1, SEL)

/*
 *  Macro for UART Control 2 Register
 */

#define USART2_STOP_ONE_BIT     (0U << 12)
#define USART2_STOP_HALF_BIT    (1U << 12)
#define USART2_STOP_TWO_BIT     (2U << 12)

#define USART2_CR2_SEL(SEL)                 SET_BIT(USART2->CR2, SEL)

/*
 *  Macro for UART Control 3 Register
 */

#define USART2_NO_FLOW_CONTROL  (0xFFF << 0)

#define USART2_CR3_SEL(SEL)                 SET_BIT(USART2->CR3, SEL)

/*
 *  Macro to check the status of USART2's data register.
 */

#define USART2_TX_BUFF_READY                CHECK_BIT(USART2->SR, 1U << 7)