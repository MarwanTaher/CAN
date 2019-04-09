#include "LED.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

/* INIT led  */
/* Parameters : N/A */
/* I/p : N/A */
/* O/p : N/A */
/* Return : void  */
/* Function that initilize led  */
uint32_t
LEDTaskInit(void)
{
    // Enable the GPIO port that is used for the on-board LED.
        //
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
        //
        // Check if the peripheral access is enabled.
        //
        while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
        {
        }
        GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,( GPIO_PIN_1 | GPIO_PIN_2 |GPIO_PIN_3));
        return 0 ;
}

void ON_LED1(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_1) ,GPIO_PIN_1);/* LED ON */


}

void OFF_LED1(void)
{

    GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_1) ,0x0);/* LED OFF */

}



