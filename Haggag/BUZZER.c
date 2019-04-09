#include "BUZZER.h"

void Buzzer_Init(void)
{
   /* Set Buzzer peripheral clock (PORT D) */
   SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
   while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD));

   /* Set Buzzer pins to O/P */
   GPIOPinTypeGPIOOutput(BUZZERPORT, BUZZERPIN);
}


void Buzzer_Toggle(void)
{
   static uint8_t i = 0 ;
   /* Enable Buzzer */
   if(i==0)
   {
       GPIOPinWrite(BUZZERPORT, BUZZERPIN,BUZZER_HIGH);
       i = 1 ;
   }
   else if(i==1)
   {
       GPIOPinWrite(BUZZERPORT, BUZZERPIN,BUZZER_LOW);
       i= 0 ;
   }

}


