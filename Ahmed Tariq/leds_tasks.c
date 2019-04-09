/*
 * leds_tasks.c
 *
 *  Created on: Mar 18, 2019
 *      Author: AVE-LAP-016
 */
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "switchs_tasks.h"
#include "LCD.h"
#include "leds_tasks.h"
// Indexes into the array of colors
//
#define RED                     0
#define GREEN                   1
#define BLUE                    2

//
// Ratio for percent of full on that should be "true" white.
//
#define RED_WHITE_BALANCE        0.497f
#define GREEN_WHITE_BALANCE      0.6f
#define BLUE_WHITE_BALANCE       1.0f

//
// GPIO, Timer, Peripheral, and Pin assignments for the colors
//
#define RED_GPIO_PERIPH         SYSCTL_PERIPH_GPIOF
#define RED_TIMER_PERIPH        SYSCTL_PERIPH_TIMER0
#define BLUE_GPIO_PERIPH        SYSCTL_PERIPH_GPIOF
#define BLUE_TIMER_PERIPH       SYSCTL_PERIPH_TIMER1
#define GREEN_GPIO_PERIPH       SYSCTL_PERIPH_GPIOF
#define GREEN_TIMER_PERIPH      SYSCTL_PERIPH_TIMER1


#define RED_GPIO_BASE           GPIO_PORTF_BASE
#define RED_TIMER_BASE          TIMER0_BASE
#define BLUE_GPIO_BASE          GPIO_PORTF_BASE
#define BLUE_TIMER_BASE         TIMER1_BASE
#define GREEN_GPIO_BASE         GPIO_PORTF_BASE
#define GREEN_TIMER_BASE        TIMER1_BASE



#define RED_GPIO_PIN_CFG        GPIO_PF1_T0CCP1
#define BLUE_GPIO_PIN_CFG       GPIO_PF2_T1CCP0
#define GREEN_GPIO_PIN_CFG      GPIO_PF3_T1CCP1

#define RED_TIMER_CFG           TIMER_CFG_B_PWM
#define BLUE_TIMER_CFG          TIMER_CFG_A_PWM
#define GREEN_TIMER_CFG         TIMER_CFG_B_PWM

#define RED_TIMER               TIMER_B
#define BLUE_TIMER              TIMER_A
#define GREEN_TIMER             TIMER_B


xQueueHandle g_pLEDQueue;

void LEDs_tasks_init(void *pvParameters)
{

        // Enable the GPIO Port and Timer for each LED
        //
    while(1)
    {
        // Enable the GPIOA peripheral
           //
           SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
           //
           // Wait for the GPIOA module to be ready.
           //
           while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
           {
           }


           // Initialize the GPIO pin configuration.
           // Set pins 0 and 3 as output, SW controlled.
           //
           GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, RED_GPIO_PIN | BLUE_GPIO_PIN | GREEN_GPIO_PIN );
           GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, RIGHT_BUTTON | LEFT_BUTTON );

           HWREG(GPIO_PORTF_BASE+GPIO_O_LOCK) = GPIO_LOCK_KEY;
           HWREG(GPIO_PORTF_BASE+GPIO_O_CR) |= 0x01;
           GPIOPadConfigSet(GPIO_PORTF_BASE ,RIGHT_BUTTON,GPIO_STRENGTH_4MA,GPIO_PIN_TYPE_STD_WPU);
           GPIOPadConfigSet(GPIO_PORTF_BASE ,LEFT_BUTTON,GPIO_STRENGTH_4MA,GPIO_PIN_TYPE_STD_WPU);



        vTaskSuspend(NULL);
    }
}
void LED_RED_task(void *pvParameters)
{

    while(1)
    {
        LED_RED_Enable();
        if( ( button1_status == 1) ||  (button2_status == 1 ) )
          {
            LED_RED_Enable();
          }
        else
          {
            LED_BLUE_Enable();
          }

        vTaskDelay(50); // 50 ms

    }

}

void LED_RED_Enable(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE, RED_GPIO_PIN , RED_GPIO_PIN);
    GPIOPinWrite(GPIO_PORTF_BASE, GREEN_GPIO_PIN , 0);
    GPIOPinWrite(GPIO_PORTF_BASE, BLUE_GPIO_PIN , 0);
}
void LED_BLUE_Enable(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE, BLUE_GPIO_PIN , BLUE_GPIO_PIN);
    GPIOPinWrite(GPIO_PORTF_BASE, RED_GPIO_PIN , 0);
    GPIOPinWrite(GPIO_PORTF_BASE, GREEN_GPIO_PIN , 0);
}
void LED_GREEN_Enable(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE, GREEN_GPIO_PIN , GREEN_GPIO_PIN);
    GPIOPinWrite(GPIO_PORTF_BASE, RED_GPIO_PIN , 0);
    GPIOPinWrite(GPIO_PORTF_BASE, BLUE_GPIO_PIN , 0);
}
void LED_WHITE_Enable(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE, RED_GPIO_PIN , RED_GPIO_PIN);
    GPIOPinWrite(GPIO_PORTF_BASE, BLUE_GPIO_PIN , BLUE_GPIO_PIN);
    GPIOPinWrite(GPIO_PORTF_BASE, GREEN_GPIO_PIN , GREEN_GPIO_PIN);
}
