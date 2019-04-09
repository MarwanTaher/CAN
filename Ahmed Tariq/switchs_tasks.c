
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
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "switchs_tasks.h"

//*****************************************************************************
//
// The stack size for the display task.
//
//*****************************************************************************

extern xQueueHandle g_pLEDQueue;
extern xSemaphoreHandle g_pUARTSemaphore;

volatile uint8_t button1_status = 0 ;
volatile uint8_t button2_status = 0 ;

extern void SwitchTask(void *pvParameters)
{

    while(1)
    {
        if( GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4) == 0 )
        {
          button1_status = 1 ;
        }
        else
        {
          button1_status = 0 ;
        }


        if( GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_0) == 0)
        {
               button2_status = 1 ;
        }
        else
        {
            button2_status = 0 ;
        }

        vTaskDelay(50); // 50 ms

    }

        //
        // Wait for the required amount of time to check back.
        //

}
