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

  const UINT16 sineWave[100] = {
    348, 370, 392, 413, 435, 456, 476, 496, 516, 534,
    553, 570, 586, 602, 616, 630, 642, 653, 663, 672,
    679, 685, 690, 693, 695, 696, 695, 693, 690, 685,
    679, 672, 663, 653, 642, 630, 616, 602, 586, 570,
    553, 534, 516, 496, 476, 456, 435, 413, 392, 370,
    348, 326, 304, 283, 261, 240, 220, 200, 180, 162,
    143, 126, 110, 94, 80, 66, 54, 43, 33, 24,
    17, 11, 6, 3, 1, 0, 1, 3, 6, 11,
    17, 24, 33, 43, 54, 66, 80, 94, 110, 126,
    143, 162, 180, 200, 220, 240, 261, 283, 304, 326
  };

  UINT8 first_send[SIZE_OF_BYTE] = {0, 0, 0, 0, 1};
  UINT8 second_send[SIZE_OF_BYTE] = {1, };
  UINT8 first_transmit, second_transmit;

  /*
   *  Initialization Routine
   */
  USART3_Init();
  DELAY_OPM_TIMER_INIT(100);

  while(1){

    //Does UART send the MSB or LSB first?
    for(int i = 0; i < sizeof(sineWave)/sizeof(sineWave[0]); i++){
      ENCODE_FUNC(sineWave[i], first_send, second_send, &first_transmit, &second_transmit);

      USART3_Write(first_transmit);
      DELAY_OPM_TIMER_UPDATE(100);
      while(!(TIM2_COMPLETE_EVENT)){}

      USART3_Write(second_transmit);
      DELAY_OPM_TIMER_UPDATE(100);
      while(!(TIM2_COMPLETE_EVENT)){}
    }
  }
}
