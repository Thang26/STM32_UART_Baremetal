/*
 * common.h
 *
 *  Created on: Oct 20, 2023
 *      Author: Thang Pham
 */

#ifndef COMMON_H_
#define COMMON_H_

/*
 *  Header Declarations
 */
#include <stdint.h>
#include <stm32f446xx.h>

/*
 *  Typedef Declarations
 */
typedef uint8_t UINT8;
typedef int8_t INT8;
typedef uint16_t UINT16;
typedef uint32_t UINT32;


/*
 *  Enum declarations
 */
typedef enum {
    OPERATION_FAILED = 0,
    OPERATION_SUCCESS = 1
} OPERATION_RESULT;

/*
 *  Macros for setting and clearing a bit in a register
 */

#define SET_BIT(REG,PIN)        ((REG) |= (PIN))
#define CLEAR_BIT(REG,PIN)      ((REG) &= ~(PIN))
#define TOGGLE_BIT(REG,PIN)     ((REG) ^= (PIN))
#define HARD_SET_BIT(REG,PIN)   ((REG) = (PIN))

#endif /* COMMON_H_ */
