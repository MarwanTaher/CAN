/*
 * LED.c
 *
 *  Created on: Mar 13, 2019
 *      Author: AVE-LAP-44
 */
#include "../STD/Std_Types.h"
#include "../Commen/numbers.h"
#include <stdint.h>
#include <stdbool.h>

#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "inc/hw_memmap.h"
#include "LED.h"

#define  LED0_PORT      GPIO_PORTF_BASE
#define  LED1_PORT      GPIO_PORTF_BASE
#define  LED2_PORT      GPIO_PORTF_BASE

#define  LED0_clk       SYSCTL_PERIPH_GPIOF
#define  LED1_clk       SYSCTL_PERIPH_GPIOF
#define  LED2_clk       SYSCTL_PERIPH_GPIOF

#define  LED0_PIN       GPIO_PIN_1
#define  LED1_PIN       GPIO_PIN_2
#define  LED2_PIN       GPIO_PIN_3


uint8 Led_ready=FALSE;
void Led_init()
{


    /* Enable the GPIO port that is used for the on-board LED0. */

    SysCtlPeripheralEnable(LED0_clk);

    /* Enable the GPIO port that is used for the on-board LED1. */

    SysCtlPeripheralEnable(LED1_clk);

    /* Enable the GPIO port that is used for the on-board LED2. */

    SysCtlPeripheralEnable(LED2_clk);

    /* Enable the GPIO pins for the LED0 as Output . */

    GPIOPinTypeGPIOOutput(LED0_PORT, LED0_PIN);
    /* Enable the GPIO pins for the LED1 as Output . */
    GPIOPinTypeGPIOOutput(LED1_PORT, LED1_PIN);
    /* Enable the GPIO pins for the LED2 as Output . */
    GPIOPinTypeGPIOOutput(LED2_PORT, LED2_PIN);

    Led_ready=TRUE;
}


void Led_on(uint8 num)
{
  switch(num)
  {
    case LED0:
    {
        GPIOPinWrite (LED0_PORT, LED0_PIN, LED0_PIN);
        break;
    }
    case LED1:
    {
        GPIOPinWrite (LED1_PORT, LED1_PIN, LED1_PIN);
        break;
    }
    case LED2:
    {
        GPIOPinWrite (LED2_PORT, LED2_PIN, LED2_PIN);
        break;
    }

  }
}
void Led_off(uint8 num)
{
    switch(num)
    {
      case LED0:
      {
          GPIOPinWrite (LED0_PORT, LED0_PIN, LOW);
          break;
      }
      case LED1:
      {
          GPIOPinWrite (LED1_PORT, LED1_PIN, LOW);
          break;
      }
      case LED2:
      {
          GPIOPinWrite (LED2_PORT, LED2_PIN, LOW);
          break;
      }

    }
}

