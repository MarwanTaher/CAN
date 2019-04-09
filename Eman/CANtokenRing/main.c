#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/can.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

#include "include/FreeRTOS.h"
#include "include/task.h"
#include "include/queue.h"
#include "include/semphr.h"

#include "Types.h"
#include "TASK.h"


//*****************************************************************************
//
// This hook is called by FreeRTOS when an stack overflow error is detected.
//
//*****************************************************************************
void
vApplicationStackOverflowHook(TaskHandle_t *pxTask, char *pcTaskName)
{
    //
    // This function can not return, so loop forever.  Interrupts are disabled
    // on entry to this function, so no processor interrupts will interrupt
    // this loop.
    //
    while(1)
    {
    }
}


int
main(void)
{

    xTaskCreate(CAN_RX_TASK, NULL, 300, NULL, 2, NULL);

    //xTaskCreate( CAN_TX_TASK,NULL, 300, NULL, 2, NULL );

    //   xTaskCreate( CAN_RX2_TASK,NULL, 300 , NULL, 2, NULL );

    xTaskCreate(pushBUTTON, NULL, 300, NULL, 2, NULL);
    xTaskCreate(CAN_startup_TASK, NULL, 300, NULL, 3, NULL);
    xTaskCreate(Tasks_Init, NULL, 300, NULL, 4, NULL);
    // Start FreeRTOS
    vTaskStartScheduler();
    //
    while(1)
    {
    }
    //
    // Return no errors
    //

}
