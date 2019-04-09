/*
 * Keypad_cfg.h
 *
 *  Created on: Mar 12, 2019
 *      Author: AVE-LAP-071
 */

#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#define GPIO_PORTA_BASE         0x40004000  // GPIO Port A
#define GPIO_PORTB_BASE         0x40005000  // GPIO Port B
#define GPIO_PORTC_BASE         0x40006000  // GPIO Port C
#define GPIO_PORTD_BASE         0x40007000  // GPIO Port D

#define COL_NUM         3       /* Number of columns */
#define ROW_NUM         3       /* Number of rows */


/* define rows & columns ports                                                     */
#define ROW_BASE_PORT       GPIO_PORTB_BASE
#define COL_BASE_PORT       GPIO_PORTD_BASE
#define COL3_BASE_PORT      GPIO_PORTA_BASE

/* define Rows Pins                                                     */

#define ROW1_PIN       GPIO_PIN_2
#define ROW2_PIN       GPIO_PIN_3
#define ROW3_PIN       GPIO_PIN_6


/* define columns pins                                                  */

#define COL1_PIN        GPIO_PIN_7
#define COL2_PIN        GPIO_PIN_6
#define COL3_PIN        GPIO_PIN_5

#define HIGH     1
#define LOW     0
#define ZERO    0

#endif /* KEYPAD_CFG_H_ */
