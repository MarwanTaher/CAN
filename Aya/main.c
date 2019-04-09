#include "can_task.h"

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}

#endif

//*****************************************************************************
//
// This hook is called by FreeRTOS when an stack overflow error is detected.
//
//*****************************************************************************
void
vApplicationStackOverflowHook(xTaskHandle *pxTask, char *pcTaskName)
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


    int main(void)
    {

        SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

        xCreatedEventGroup_flags = xEventGroupCreate();

        xTaskCreate(INIT_task,"INIT", 100, NULL,5,NULL);
        xTaskCreate(recieve_mode,"recieve", 300, NULL,3,NULL);
        xTaskCreate(transmit_mode,"transmit", 300, NULL,2,NULL);


        vTaskStartScheduler();

    return 0;
}
