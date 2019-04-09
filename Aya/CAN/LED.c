

#include  "LED.h"

/********************************************************************************************************************************************
 * Function name :- LED_init
 * Function job :- initialize leds
 * Function arguments :- N/A
 * Function return :- N/A
 ************************************************************************************************************************************************/
void LED_init(void)
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

               //
               // Enable the GPIO pin for the LED (PF3).  Set the direction as output, and
               // enable the GPIO pin for digital function.
               //
               GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1 );

}


/********************************************************************************************************************************************
 * Function name :- LED_on
 * Function job :- turn desired led on
 * Function arguments :- desired led
 * Function return :- N/A
 ************************************************************************************************************************************************/
void LED_on(uint8_t led_num)
{

    switch(led_num)
    {
    /* in case of selected led is 1 */
    case LED1 :
        /* write one on pin 1 to turn led on */
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1,GPIO_PIN_1 );
        break ;
        /* in case of selected led is 2 */
          case LED2 :
              /* write one on pin 2 to turn led on */
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2,GPIO_PIN_2 );
              break ;
              /* in case of selected led is 3 */
           case LED3 :
                    /* write one on pin 3 to turn led on */
         GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3,GPIO_PIN_3 );
               break ;

    }

}

/********************************************************************************************************************************************
 * Function name :- LED_off
 * Function job :- turn desired led off
 * Function arguments :- desired led
 * Function return :- N/A
 ************************************************************************************************************************************************/
void LED_off(uint8_t led_num)
{

    switch(led_num)
    {
    /* in case of selected led is 0 */
    case LED1 :
        /* write zero on pin 1 to turn led on */
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1,0x0 );
        break ;
        /* in case of selected led is 2 */
          case LED2 :
              /* write zero on pin 2 to turn led on */
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2,0x0 );
              break ;
              /* in case of selected led is 3 */
           case LED3 :
                    /* write zero on pin 3 to turn led on */
         GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3,0x0 );
               break ;

    }

}
