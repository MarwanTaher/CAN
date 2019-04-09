
/* Guard file */
#ifndef LED_H_
#define  LED_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"

/* leds configuration */
#define   LED1    1
#define   LED2    2
#define   LED3    3


/**********************************************************************************************************************
 *                                               Function prototypes
 **********************************************************************************************************************/


/********************************************************************************************************************************************
 * Function name :- LED_init
 * Function job :- initialize leds
 * Function arguments :- N/A
 * Function return :- N/A
 ************************************************************************************************************************************************/
void LED_init(void);


/********************************************************************************************************************************************
 * Function name :- LED_on
 * Function job :- turn desired led on
 * Function arguments :- desired led
 * Function return :- N/A
 ************************************************************************************************************************************************/
void LED_on(uint8_t led_num);

/********************************************************************************************************************************************
 * Function name :- LED_off
 * Function job :- turn desired led off
 * Function arguments :- desired led
 * Function return :- N/A
 ************************************************************************************************************************************************/
void LED_off(uint8_t led_num);


#endif    /*       end of LLED_H_ */
