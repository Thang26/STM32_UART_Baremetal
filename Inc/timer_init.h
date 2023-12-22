/*
 * timer_init.h
 *
 *  Created on: Nov 01, 2023
 *      Author: Thang Pham
 */

/*
 * Function prototype declarations
 */

void LED_FLASH_TIMER_INIT(UINT16 PSC_Div_Val, UINT16 ARR_Div_Val);
void LED_FLASH_TIMER_UPDATE_VAL(UINT16 ARR_Div_Val);
void DELAY_OPM_TIMER_INIT(UINT16 ARR_Div_Val);
void DELAY_OPM_TIMER_UPDATE(UINT16 ARR_Div_Val);


/*
 *  Macro for TIMERx Enable Initialization
 */

/*
 *  Macro for Timer Enables
 */

/* For APB1ENR Timers */
#define TIMER_2_EN  (1U << 0)
#define TIMER_3_EN  (1U << 1)
#define TIMER_4_EN  (1U << 2)
#define TIMER_5_EN  (1U << 3)
#define TIMER_6_EN  (1U << 4)
#define TIMER_7_EN  (1U << 5)
#define TIMER_12_EN (1U << 6)
#define TIMER_13_EN (1U << 7)
#define TIMER_14_EN (1U << 8)

/*
 *  APB1ENR Timers
 *  TIM2, TIM3, TIM4, TIM5, TIM6,
 *  TIM7, TIM12, TIM13, TIM14
 */

#define APB1_TIMERx_ENABLE(TIMER_x_EN)         SET_BIT(RCC->APB1ENR, TIMER_x_EN)

/*
 *  APB2ENR Timers
 */

//#define TODO

/*
 *  Starts the timer from CEN bit of TIMx_CR1 register.
 */

#define TIM2_START          SET_BIT(TIM2->CR1, 1U << 0)
#define TIM3_START          SET_BIT(TIM3->CR1, 1U << 0)

/*
 *  Clears the Update Interrupt Event Flag generated by
 *  an overflow or underflow of the counter.
 */

#define TIM2_FLAG_CLEAR     CLEAR_BIT(TIM2->SR, 1U << 0)
#define TIM3_FLAG_CLEAR     CLEAR_BIT(TIM3->SR, 1U << 0)

/*
 *  Macro to check the UIF bit within the SR register
 */

#define TIM2_COMPLETE_EVENT (TIM2->SR & (1U << 0))
#define TIM3_COMPLETE_EVENT (TIM3->SR & (1U << 0))

/*
 *  Configures a TIMERx to trigger an interrupt
 */

#define TIM2_IRQ_EN         SET_BIT(TIM2->DIER, 1U << 0)
#define TIM3_IRQ_EN         SET_BIT(TIM3->DIER, 1U << 0)

/*
 *  Configures a TIMERx to disable itself after one overflow event
 */

#define TIM2_OPM_EN         SET_BIT(TIM2->CR1, 1U << 3)
#define TIM3_OPM_EN         SET_BIT(TIM3->CR1, 1U << 3)