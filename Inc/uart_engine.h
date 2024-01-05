/*
 * UART_Engine.h
 *
 *  Created on: Dec 22, 2023
 *      Author: Thang Pham
 * 
 *  Header file associated with the UART_Engine.c file.
 * 
 */

/*
 *  Function Prototypes
 */

void USART1_Init(void);
void USART1_Write(int data);
void USART1_WriteString(char *data);
void USART1_Init(void);
void USART2_Write(int data);
void USART2_WriteString(char *data);
void USART3_Init(void);
void USART3_Write(int data);
void USART3_WriteString(char *data);
void ENCODE_FUNC(UINT16 dataValue, UINT8 *first_send, UINT8 *second_send, UINT8 *first_transmit, UINT8 *second_transmit);