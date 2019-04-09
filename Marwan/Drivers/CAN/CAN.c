/*
 * CAN.c
 *
 *  Created on: Apr 3, 2019
 *      Author: AVE-LAP-071
 */
#include <stdbool.h>
#include <stdint.h>
#include "FreeRTOS/Includes/FreeRTOS.h"
#include "FreeRTOS/Includes/task.h"
#include "FreeRTOS/Includes/queue.h"
#include "FreeRTOS/Includes/semphr.h"
#include "FreeRTOS/Includes/event_groups.h"
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "CAN.h"
#include "driverlib/can.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

/***************************************************/
/* Define SEND CAN Structures.    */
/***************************************************/
tCANMsgObject sCANMessageTX;
uint8_t *pui8MsgDataout;
uint32_t ui32MsgDataout;
/***************************************************/
/* Define REC CAN Structures.    */
/***************************************************/
tCANMsgObject sCANMessageRX;
tCANMsgObject sCANMessageRXG;
uint8_t pui8MsgDatain[8];
uint8_t pui8MsgDataing[8];


//*****************************************************************************
//
// A flag to indicate that some transmission error occurred.
//
//*****************************************************************************
volatile uint8_t g_bErrFlag = 0;



#define NODE_1          1
#define NODE_2          0
#define NODE_3          0
//*****************************************************************************
//
// flags for the interrupt handler to indicate that a message was received/Sent.
//
//*****************************************************************************
uint8_t STARTUP;
uint8_t Token = 0;
volatile bool g_bRXFlag1 = 0;
volatile bool g_bRXFlag2 = 0;
volatile bool g_bRXFlag3 = 0;

void CAN_Init()
{

    //
    // Enable the CAN0 module.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    //
    // Wait for the CAN0 module to be ready.
    //
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB))
    {
    }
    GPIOPinTypeCAN(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);
           /*
           // Wait for the CAN0 module to be ready.
           */
           while(!SysCtlPeripheralReady(SYSCTL_PERIPH_CAN0));
           //
    //
    // Configure the GPIO pin muxing to select CAN0 functions for these pins.
    // This step selects which alternate function is available for these pins.
    // This is necessary if your part supports GPIO pin function muxing.
    // Consult the data sheet to see which functions are allocated per pin.
    // TODO: change this to select the port/pin you are using
    //

    GPIOPinConfigure(GPIO_PB4_CAN0RX);
    GPIOPinConfigure(GPIO_PB5_CAN0TX);

    //
    // Enable the alternate function on the GPIO pins.  The above step selects
    // which alternate function is available.  This step actually enables the
    // alternate function instead of GPIO for these pins.
    // TODO: change this to match the port/pin you are using
    //

    CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 500000);
    //
    // Reset the state of all the message objects and the state of the CAN
    // module to a known state.
    //
    CANInit(CAN0_BASE);

    //
    // Configure the controller for 1 Mbit operation.
    //


    //
    // Enable interrupts on the CAN peripheral.  This example uses static
    // allocation of interrupt handlers which means the name of the handler
    // is in the vector table of startup code.  If you want to use dynamic
    // allocation of the vector table, then you must also call CANIntRegister()
    // here.
    //
    //CANIntRegister(CAN0_BASE, CANIntHandler); // if using dynamic vectors
    //
    CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);

    //
    // Enable the CAN interrupt on the processor (NVIC).
    //
    IntEnable(INT_CAN0);
    //
    // Take the CAN0 device out of INIT state.
    //
    CANEnable(CAN0_BASE);


}


void
InitConsole(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTStdioConfig(0, 115200, 16000000);
}

void SimpleDelay(void)
{
    // 1 second
    SysCtlDelay(16000000 / 3);
}

void StartUpState(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
    SimpleDelay();
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
#if NODE_1
    Token = 1;
    STARTUP = 1 ;
#endif
}

//*****************************************************************************
//
// This function is the interrupt handler for the CAN peripheral.  It checks
// for the cause of the interrupt, and maintains a count of all messages that
// have been transmitted.
//
//*****************************************************************************
void CANIntHandler(void)
{

    uint32_t ui32Status;

       //
       // Read the CAN interrupt status to find the cause of the interrupt
       //
       ui32Status = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE);

       //
       // If the cause is a controller status interrupt, then get the status
       //
       if(ui32Status == CAN_INT_INTID_STATUS)
       {
           //
           // Read the controller status.  This will return a field of status
           // error bits that can indicate various errors.  Error processing
           // is not done in this example for simplicity.  Refer to the
           // API documentation for details about the error status bits.
           // The act of reading this status will clear the interrupt.
           //
           ui32Status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);

           //
           // Set a flag to indicate some errors may have occurred.
           //
           g_bErrFlag = 1;
       }

       //
       // Check if the cause is message object 1.
       //
       else if(ui32Status == 1)
       {
           //
           // Getting to this point means that the RX interrupt occurred on
           // message object 1, and the message reception is complete.  Clear the
           // message object interrupt.
           //
           CANIntClear(CAN0_BASE, 1);

           //
           // Set flag to indicate received message is pending for this message
           // object.
           //
           g_bRXFlag1 = 1;

           //
           // Since a message was received, clear any error flags.
           //
           g_bErrFlag = 0;
       }

       //
       // Check if the cause is message object 2.
       //
       else if(ui32Status == 2)
       {
           CANIntClear(CAN0_BASE, 2);

           g_bRXFlag2 = 1;
           g_bErrFlag = 0;
       }

       //
       // Check if the cause is message object 3.
       //
       else if(ui32Status == 3)
       {
           CANIntClear(CAN0_BASE, 3);

           g_bRXFlag3 = 1;
           g_bErrFlag = 0;
       }

       //
       // Otherwise, something unexpected caused the interrupt.  This should
       // never happen.
       //
       else
       {
           //
           // Spurious interrupt handling can go here.
           //
       }
}


