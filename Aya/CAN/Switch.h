/*
 * Switch.h
 *
 *  Created on: Mar 18, 2019
 *      Author: AVE-LAP-023
 */

#ifndef DRIVERS_SWITCH_SWITCH_H_
#define DRIVERS_SWITCH_SWITCH_H_


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
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
/******************************************************************************/
/* Function: Switch_Init                                                      */
/* @param: void                                                               */
/* return: void                                                               */
/* Description: Init Switch                                                   */
/******************************************************************************/
void Switch_Init(void);

/******************************************************************************/
/* Function: LED1                                                             */
/* @param: void                                                               */
/* return: uint8 the status of the button                                     */
/* Description: return SW status                                              */
/******************************************************************************/
uint8_t SW_1_Status(void);
uint8_t SW_2_Status(void);
#endif /* DRIVERS_SWITCH_SWITCH_H_ */
