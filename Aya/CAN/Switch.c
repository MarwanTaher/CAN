/*
 * Switch.c
 *
 *  Created on: Mar 18, 2019
 *      Author: AVE-LAP-023
 */

#include "Switch.h"
#include "CommonNumbers.h"


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
    uint8_t status = NUM_0;
    if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0) == NUM_0)
    {
        status =NUM_1;
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
    uint8_t status = NUM_0;
    if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) == NUM_0)
    {
        status =NUM_1;
    }
    return status;
}
