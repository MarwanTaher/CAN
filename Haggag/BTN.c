#include "Btn.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#define ZERO 0


/*Btns_Init */
/* Parameters : N/A */
/* I/p : N/A */
/* O/p : N/A */
/* Return : void  */
/* Function that init the BTN 1     */
void Btns_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
            { }
   GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, (GPIO_PIN_4|GPIO_PIN_0));
   GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_2);
   GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
}



/* Btn1_Read */
/* Parameters : N/A */
/* I/p : N/A */
/* O/p : N/A */
/* Return : uint32_t */
/* Function check the button status and return the stat if pressed return 1 and if not pressed return zero    */
uint32_t Btn1_Read(void)
{
   uint32_t BtnState = ZERO ;/*flag to store the status in BTN  */

   BtnState = GPIOPinRead(PUSHBTN1PORT,PUSHBTN1PIN);/*check the status of BTN status using TIVA WARE function */

   if (!BtnState)  /*if button is pressed check the zero condition cause its pull up */
       BtnState = BTN1_ON ;/*set BtnState flag =1 */
   else if(BtnState)
       BtnState = BTN1_OFF ;
   else{}

   return BtnState ; /*return BTN2 state */
}


/*Btn1_Read */
/* Parameters : N/A */
/* I/p : N/A */
/* O/p : N/A */
/* Return : uint32_t */
/* Function check the button status and return the stat if pressed return 1 and if not pressed return zero    */
uint32_t Btn2_Read(void)
{
   uint32_t BtnState = ZERO ;/*flag to store the status in BTN  */

   BtnState = GPIOPinRead(PUSHBTN0PORT,PUSHBTN0PIN);/*check the status of BTN status using TIVA WARE function */

   if (!BtnState)  /*if button is pressed check the zero condition cause its pull up  */
       BtnState = BTN1_ON ;/*set BtnState flag =1 */
   else if(BtnState)
       BtnState = BTN1_OFF ;
   else{}

   return BtnState ; /*return BTN1 state */
}



