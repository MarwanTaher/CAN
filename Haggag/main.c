#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/can.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "CAN.h"
#include "BUZZER.h"
#include "queue.h"
#include "My_Task.h"
#include "BTN.h"
#include "LED.h"

#define STACK_SIZE_WORD       300

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
    SYSCTL_OSC_MAIN);

    xTaskCreate(vTaskCode_INIT_CAN_ZERO, NULL, STACK_SIZE_WORD, NULL, 7, NULL);/*INIT TASK */
    //xTaskCreate(vTaskCode_NODE_ZERO_START, NULL, STACK_SIZE_WORD, NULL, 6, NULL);/*START UP NODE TASK */
    //xTaskCreate(vTaskCode_BTN1_GET, NULL, STACK_SIZE_WORD, NULL, 3, NULL);/* BTN TASK */

    xTaskCreate(vTaskCode_NODE_RX, NULL, STACK_SIZE_WORD, NULL, 3, NULL);/* TRANSMIT TASK */
    xTaskCreate(vTaskCode_NODE_TX, NULL, STACK_SIZE_WORD, NULL, 3, NULL);/*RECEIVE TASK */

    vTaskStartScheduler();
    return 0;
}
