#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "BUTTON.h"

#define PRESSED 1
#define NOT_PRESSED 0
static uint8_t status=0;
static uint8_t counter1=0;
static uint8_t counter2=0;

/* function to initialize the PUSH BUTTON*/
void BUTTON_Init(void){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
            { }
   GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, (GPIO_PIN_4|GPIO_PIN_0));
   GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_2);
   GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

}

/* function to get the value of the PUSH BUTTON*/
uint8_t Get_BUTTON(void){

    uint8_t key;
    if(!GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4)){
        key=PRESSED;
    }
    else{
        key=NOT_PRESSED;
    }
    return key;
}
