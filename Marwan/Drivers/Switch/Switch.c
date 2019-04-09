/*
 * Switch.c
 *
 *  Created on: Mar 18, 2019
 *      Author: AVE-LAP-057
 */

#include "inc/Switch.h"

volatile uint8_t button_Flag = 0;
/******************************************************************************/
/* Function: Switch_Init                                                      */
/* @param: void                                                               */
/* return: void                                                               */
/* Description: Init Switch                                                   */
/******************************************************************************/
void Switch_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTF_BASE ,GPIO_PIN_4,GPIO_STRENGTH_4MA,GPIO_PIN_TYPE_STD_WPU);
    HWREG(GPIO_PORTF_BASE+GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE+GPIO_O_CR) |= 0x01;
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,GPIO_PIN_0);
    GPIOPadConfigSet(GPIO_PORTF_BASE ,GPIO_PIN_0,GPIO_STRENGTH_4MA,GPIO_PIN_TYPE_STD_WPU);
}



/******************************************************************************/
/* Function: SW_1_Status                                                      */
/* @param: void                                                               */
/* return: uint8 the status of the button                                     */
/* Description: return SW status                                              */
/******************************************************************************/
uint8_t SW_1_Status(void)
{
    uint8_t status = 0;
    if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0) == 0)
    {
        status = 1;
    }
    else
    {
        status = 0;
    }
    return status;
}

/******************************************************************************/
/* Function: SW_1_Status                                                      */
/* @param: void                                                               */
/* return: uint8 the status of the button                                     */
/* Description: return SW status                                              */
/******************************************************************************/
uint8_t SW_2_Status(void)
{
    uint8_t status = 0;
    if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) == 0)
    {
        status =1;
    }
    return status;
}
