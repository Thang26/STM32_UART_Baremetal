/*
 * port_init.h
 *
 *  Created on: Oct 19, 2023
 *      Author: Thang Pham
 */

#ifndef PORT_INIT_H_
#define PORT_INIT_H_

/*
 *  Macro for PIN NUM
 */

#define PIN_0    0
#define PIN_1    1
#define PIN_2    2
#define PIN_3    3
#define PIN_4    4
#define PIN_5    5
#define PIN_6    6
#define PIN_7    7
#define PIN_8    8
#define PIN_9    9
#define PIN_10   10
#define PIN_11   11
#define PIN_12   12
#define PIN_13   13
#define PIN_14   14
#define PIN_15   15

/*
 *  Macro for GPIO Clock Initialization
 */

#define GPIOA_CLK_EN    (1U << 0)
#define GPIOB_CLK_EN    (1U << 1)
#define GPIOC_CLK_EN    (1U << 2)
#define GPIOD_CLK_EN    (1U << 3)
#define GPIOE_CLK_EN    (1U << 4)
#define GPIOF_CLK_EN    (1U << 5)
#define GPIOG_CLK_EN    (1U << 6)
#define GPIOH_CLK_EN    (1U << 7)

/*
 *  Macro for GPIO CLK Enable
 */

#define RCC_GPIO_CLK_ENABLE(GPIO_X)             SET_BIT(RCC->AHB1ENR,GPIO_X)

/*
 *  Macro for GPIO MODER Initialization
 */

#define INPUT_SEL   0U
#define OUTPUT_SEL  1U
#define ALT_SEL     2U
#define ANALOG_SEL  3U

//GPIO MODER Output/Input Configuration
#define GPIOA_MODER_SEL(PIN_NUM, MODE_SEL)      SET_BIT(GPIOA->MODER, (MODE_SEL) << (PIN_NUM * 2))
#define GPIOB_MODER_SEL(PIN_NUM, MODE_SEL)      SET_BIT(GPIOB->MODER, (MODE_SEL) << (PIN_NUM * 2))
#define GPIOC_MODER_SEL(PIN_NUM, MODE_SEL)      SET_BIT(GPIOC->MODER, (MODE_SEL) << (PIN_NUM * 2))


/*
 *  Macro for GPIO BSSR Register
 */

#define BSRR_PIN_SET    0
#define BSRR_PIN_CLEAR  16

#define GPIOA_BSRR_SEL(PIN_NUM, PIN_SET_CLEAR)  SET_BIT(GPIOA->BSRR, 1U << (PIN_NUM + PIN_SET_CLEAR))
#define GPIOB_BSRR_SEL(PIN_NUM, PIN_SET_CLEAR)  SET_BIT(GPIOB->BSRR, 1U << (PIN_NUM + PIN_SET_CLEAR))

//GPIOB Pin 3 & 4 is reserved for JTAG and NJTRST!
#define GPIOB_BSRR_ALL_CLEAR                    SET_BIT(GPIOB->BSRR, 0xFFE7 << BSRR_PIN_CLEAR)
#define GPIOC_BSRR_ALL_CLEAR                    SET_BIT(GPIOC->BSRR, 0xFFFF << BSRR_PIN_CLEAR)

/*
 *  Macro for GPIO AFR Register
 *  Select LOW for Pin 0 - 7, HIGH for Pin 8 - 15
 */

#define AFR_LOW     0
#define AFR_HIGH    1

#define GPIOA_AFR_SEL(HIGH_LOW, PIN_NUM, PERIPH_SEL)     SET_BIT(GPIOA->AFR[(HIGH_LOW)], (PERIPH_SEL) << (PIN_NUM * 4))

/*
 *  Other macros / masks for GPIO
 */

#define GPIOA_TOGGLE_PIN(PIN_NUM)               TOGGLE_BIT(GPIOA->ODR, 1U << PIN_NUM)



#endif /* PORT_INIT_H_ */