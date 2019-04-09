#include <FreeRTOS.h>
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
#include "Task.h"
#include "led_task.h"
#include "CAN_Driver.h"
#include "CAN_Task.h"
#include "Switch_Driver.h"

#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}

#endif

int main(void)
{
    // Set the clocking to run at 50 MHz from the PLL.
    //
    //ROM_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
    //SYSCTL_OSC_MAIN);

    /*Inatalize UART*/
    InitConsole();

    /*Initalize Buttons*/
    Switch_init();

    /*Init Can Send*/
    Can_Send_Init();

    /*Init Can Recive*/
    Can_Recive_Init();

    /*Create Init Task For Led*/
    xTaskCreate(LEDS_Task_init, (const portCHAR *) "LED_Init", 128, NULL, 13,
    NULL);

    /*add Task for Token*/
    xTaskCreate(Token_Task, (const portCHAR *) "Token Task", 150, NULL, 4,
    NULL);

    /*add Task for Token*/
    xTaskCreate(Button_Task, (const portCHAR *) "Button Task", 150, NULL, 8,
    NULL);

    /*Task For CAN*/
    xTaskCreate(Can_Task_Recive, (const portCHAR *) "CAN Task Receive", 150,
    NULL,
                6, NULL);
    /*Add Task For Led*/
    xTaskCreate(Led_Task, (const portCHAR *) "Led Task", 150, NULL, 3 ,NULL);

    /*Start Schedular*/
    vTaskStartScheduler();

    while (1)
    {
    }
    return 0;
}
