/*
 * Button.c
 *
 *  Created on: Mar 18, 2019
 *      Author: AVE-LAP-44
 */

#include "../STD/Std_Types.h"
#include <stdint.h>
#include <stdbool.h>
#include "../Commen/numbers.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"

#include "inc/hw_memmap.h"
#include "Button.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"


void Button_init()
{

    /* Enable the GPIO port that is used for the on-board Button. */

    SysCtlPeripheralEnable(Button0_clk);

    SysCtlPeripheralEnable(Button1_clk);

    HWREG(GPIO_PORTF_BASE+GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE+GPIO_O_CR) |= 0x01;


    /* Enable the GPIO pins for the Button0 as Input . */

    GPIOPinTypeGPIOInput(Button0_PORT, Button0_PIN);
    GPIOPadConfigSet(Button0_PORT,Button0_PIN,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);
    GPIOPinTypeGPIOInput(Button1_PORT, Button1_PIN);
    GPIOPadConfigSet(Button1_PORT,Button1_PIN,GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPU);




}
static uint8 button_status;
uint8 get_key(uint8 button_num)

{

    if (NUM_ZERO==button_num)
    {
    button_status=GPIOPinRead (Button0_PORT, Button0_PIN);
    }
    else if(NUM_1==button_num)
    {
     button_status=GPIOPinRead (Button1_PORT, Button1_PIN);

    }
    else
    {

    }



    return button_status;

}
