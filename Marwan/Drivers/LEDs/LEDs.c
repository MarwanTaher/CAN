/*
 * LEDs.c
 *
 *  Created on: Mar 13, 2019
 *      Author: AVE-LAP-057
 */
#include "inc/LEDs.h"

/******************************************************************************/
/* Function: LEDs_Init                                                        */
/* @param: void                                                               */
/* return: void                                                               */
/* Description: Init LEDs                                                     */
/******************************************************************************/
void LEDs_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,(GPIO_PIN_0 | GPIO_PIN_1 |GPIO_PIN_2|GPIO_PIN_3));
}

/******************************************************************************/
/* Function: LED1                                                             */
/* @param: void                                                               */
/* return: void                                                               */
/* Description: Toggle LED1                                                   */
/******************************************************************************/
void LED1(void)
{
    if (!GPIOPinRead(GPIO_PORTF_BASE,  GPIO_PIN_1))
           {
               GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);

           }

           else if(GPIOPinRead(GPIO_PORTF_BASE,  GPIO_PIN_1))
           {
               GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0x0);
           }

           else
           {
               /*Nothing to do*/
           }
}



/******************************************************************************/
/* Function: LED1_OFF                                                         */
/* @param: void                                                               */
/* return: void                                                               */
/* Description: Turn Off LED1                                                 */
/******************************************************************************/
void LED1_OFF(void)
{

    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, LOW);

}

/******************************************************************************/
/* Function: LED2                                                             */
/* @param: void                                                               */
/* return: void                                                               */
/* Description: Toggle LED2                                                   */
/******************************************************************************/
void LED2(void)
{
    if (!GPIOPinRead(GPIO_PORTF_BASE,  GPIO_PIN_2))
           {
               GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);

           }

           else if(GPIOPinRead(GPIO_PORTF_BASE,  GPIO_PIN_2))
           {
               GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x0);
           }

           else
           {
               /*Nothing to do*/
           }

}



/******************************************************************************/
/* Function: LED3                                                             */
/* @param: void                                                               */
/* return: void                                                               */
/* Description: Toggle LED3                                                   */
/******************************************************************************/
void LED3(void)
{
    if (!GPIOPinRead(GPIO_PORTF_BASE,  GPIO_PIN_3))
           {
               GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);

           }

           else if(GPIOPinRead(GPIO_PORTF_BASE,  GPIO_PIN_3))
           {
               GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x0);
           }

           else
           {
               /*Nothing to do*/
           }
}


void Buzzer(void)
{
    if (!GPIOPinRead(GPIO_PORTF_BASE,  GPIO_PIN_0))
               {
                   GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_PIN_0);

               }

               else if(GPIOPinRead(GPIO_PORTF_BASE,  GPIO_PIN_0))
               {
                   GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0x0);
               }

               else
               {
                   /*Nothing to do*/
               }
}
