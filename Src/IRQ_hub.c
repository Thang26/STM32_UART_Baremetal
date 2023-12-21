/*
 * IRQ_hub.c
 *
 *  Created on: Nov 04, 2023
 *      Author: Thang Pham
 * 
 *  This is a collection of all the IRQ service routine functions.
 *  
 *  IMPORTANT: You must abstract whatever functionalities associated
 *  with the IRQ away from the handler itself. This is to foster the idea
 *  that an IRQ handler can be swapped in and out the functionalities
 *  associated with that IRQ.
 * 
 *  This can be done by having the IRQ envoke a function. EXPERIMENTAL.
 */

#include <common.h>

void TIM3_IRQHandler(void){
    TIM3->SR &= ~(1U << 0);     //Clears UIE flag for TIMER3

}