/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <common.h>
#include <uart_engine.h>
#include <timer_init.h>

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
  USART3_Init();
  DELAY_OPM_TIMER_INIT(100);
  char sineWave[12] = {'1', '2', '3', '5', '8', '9', '9', '8', '5', '3', '2', '1'};
  int i;

  while(1){

    for(i = 0; i < 12; i++){
      USART3_Write(sineWave[i]);
      DELAY_OPM_TIMER_UPDATE(300);
      while(!(TIM2_COMPLETE_EVENT)){}
    }
  }
}
