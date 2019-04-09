/*
 * LEDs.h
 *
 *  Created on: Mar 13, 2019
 *      Author: AVE-LAP-057
 */

#ifndef LEDS_INC_LEDS_H_
#define LEDS_INC_LEDS_H_

#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/ssi.h"

#define RED_LED   GPIO_PIN_1
#define BLUE_LED  GPIO_PIN_2
#define GREEN_LED GPIO_PIN_3

#define LOW             0
#define HIGH            1
/******************************************************************************/
/* Function: LEDs_Init                                                        */
/* @param: void                                                               */
/* return: void                                                               */
/* Description: Init LEDs                                                     */
/******************************************************************************/
void LEDs_Init(void);

/******************************************************************************/
/* Function: LED1                                                             */
/* @param: void                                                               */
/* return: void                                                               */
/* Description: Toggle LED1                                                   */
/******************************************************************************/
void LED1(void);


/******************************************************************************/
/* Function: LED1_OFF                                                         */
/* @param: void                                                               */
/* return: void                                                               */
/* Description: Turn Off LED1                                                 */
/******************************************************************************/
void LED1_OFF(void);


void LED2(void);
void LED3(void);
void Buzzer(void);



#endif /* LEDS_INC_LEDS_H_ */
