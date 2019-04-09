/*
 * App_Tasks.c
 *
 *  Created on: Mar 19, 2019
 *      Author: AVE-LAP-032
 */
#if 0
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
#include "FreeRTOS_Files/FreeRTOS.h"
#include "FreeRTOS_Files/task.h"
#include "FreeRTOS_Files/queue.h"
#include "FreeRTOS_Files/semphr.h"
#include "FreeRTOS_Files/event_groups.h"
#include "HAL/LCD.h"
#include "HAL/Magic_Num.h"
#include "Delay.h"
#include "App_Tasks.h"

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/can.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

//*****************************************************************************
//
// A counter that keeps track of the number of times the RX interrupt has
// occurred, which should match the number of messages that were received.
//
//*****************************************************************************
volatile uint32_t g_ui32MsgCount = 0;

//*****************************************************************************
//
// A flag for the interrupt handler to indicate that a message was received.
//
//*****************************************************************************
volatile bool g_bRXFlag = 0;

//*****************************************************************************
//
// A flag to indicate that some reception error occurred.
//
//*****************************************************************************
volatile bool g_bErrFlag = 0;

/*FLAGS */

volatile bool STATE = STARTUP;

volatile bool RX = NO;

volatile bool TX = NO;

//*****************************************************************************
//
// This function provides a 1 second delay using a simple polling method.
//
//*****************************************************************************
void SimpleDelay(void)
{
    //
    // Delay cycles for 1 second
    //
    SysCtlDelay(16000000 / 3);
}

//*****************************************************************************
//
// This function sets up UART0 to be used for a console to display information
// as the example is running.
//
//*****************************************************************************
void InitConsole(void)
{
    //
    // Enable GPIO port A which is used for UART0 pins.
    // TODO: change this to whichever GPIO port you are using.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Configure the pin muxing for UART0 functions on port A0 and A1.
    // This step is not necessary if your part does not support pin muxing.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    //
    // Enable UART0 so that we can configure the clock.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Select the alternate (UART) function for these pins.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
}

//*****************************************************************************
//
// This function is the interrupt handler for the CAN peripheral.  It checks
// for the cause of the interrupt, and maintains a count of all messages that
// have been received.
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
    if (ui32Status == CAN_INT_INTID_STATUS)
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
    // Check if the cause is message object 1, which what we are using for
    // receiving messages.
    //
    else if (ui32Status == 1)
    {
        //
        // Getting to this point means that the RX interrupt occurred on
        // message object 1, and the message reception is complete.  Clear the
        // message object interrupt.
        //
        CANIntClear(CAN0_BASE, 1);

        //
        // Increment a counter to keep track of how many messages have been
        // received.  In a real application this could be used to set flags to
        // indicate when a message is received.
        //
        g_ui32MsgCount++;

        //
        // Set flag to indicate received message is pending.
        //
        g_bRXFlag = 1;

        //
        // Since a message was received, clear any error flags.
        //
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

void Init_Task(void)
{
    while (ONE)
    {
        /*Enable clk for portf*/
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

        /*Wait for portf to complete initialization*/
        while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
        {
        }

        /* Set portf pin2 as output for led1 and led2*/
        GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2 | GPIO_PIN_3);

        /* Set portf pin0 and pin4 as Input for Button1 and Button2*/
        GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);

        /*Configure portf pin4 and pin0 as pullup*/
        GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4,
                GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPU);

#if defined(TARGET_IS_TM4C129_RA0) ||                                         \
    defined(TARGET_IS_TM4C129_RA1) ||                                         \
    defined(TARGET_IS_TM4C129_RA2)
        uint32_t ui32SysClock;
#endif

        //
        // Set the clocking to run directly from the external crystal/oscillator.
        // TODO: The SYSCTL_XTAL_ value must be changed to match the value of the
        // crystal used on your board.
        //
#if defined(TARGET_IS_TM4C129_RA0) ||                                         \
    defined(TARGET_IS_TM4C129_RA1) ||                                         \
    defined(TARGET_IS_TM4C129_RA2)
        ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                        SYSCTL_OSC_MAIN |
                        SYSCTL_USE_OSC)
                25000000);
#else
        SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                SYSCTL_XTAL_16MHZ);
#endif

        //
        // Set up the serial console to use for displaying messages.  This is
        // just for this example program and is not needed for CAN operation.
        //
        InitConsole();

        //
        // For this example CAN0 is used with RX and TX pins on port B4 and B5.
        // The actual port and pins used may be different on your part, consult
        // the data sheet for more information.
        // GPIO port B needs to be enabled so these pins can be used.
        // TODO: change this to whichever GPIO port you are using
        //
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

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
        GPIOPinTypeCAN(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5);

        //
        // The GPIO port and pins have been set up for CAN.  The CAN peripheral
        // must be enabled.
        //
        SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);

        //
        // Initialize the CAN controller
        //
        CANInit(CAN0_BASE);

        //
        // Set up the bit rate for the CAN bus.  This function sets up the CAN
        // bus timing for a nominal configuration.  You can achieve more control
        // over the CAN bus timing by using the function CANBitTimingSet() instead
        // of this one, if needed.
        // In this example, the CAN bus is set to 500 kHz.  In the function below,
        // the call to SysCtlClockGet() or ui32SysClock is used to determine the
        // clock rate that is used for clocking the CAN peripheral.  This can be
        // replaced with a  fixed value if you know the value of the system clock,
        // saving the extra function call.  For some parts, the CAN peripheral is
        // clocked by a fixed 8 MHz regardless of the system clock in which case
        // the call to SysCtlClockGet() or ui32SysClock should be replaced with
        // 8000000.  Consult the data sheet for more information about CAN
        // peripheral clocking.
        //
#if defined(TARGET_IS_TM4C129_RA0) ||                                         \
    defined(TARGET_IS_TM4C129_RA1) ||                                         \
    defined(TARGET_IS_TM4C129_RA2)
        CANBitRateSet(CAN0_BASE, ui32SysClock, 500000);
#else
        CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 500000);
#endif

        //
        // Enable interrupts on the CAN peripheral.  This example uses static
        // allocation of interrupt handlers which means the name of the handler
        // is in the vector table of startup code.  If you want to use dynamic
        // allocation of the vector table, then you must also call CANIntRegister()
        // here.
        //
        // CANIntRegister(CAN0_BASE, CANIntHandler); // if using dynamic vectors
        //
        CANIntEnable(CAN0_BASE,
                CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);

        //
        // Enable the CAN interrupt on the processor (NVIC).
        //
        IntEnable(INT_CAN0);

        //
        // Enable the CAN for operation.
        //
        CANEnable(CAN0_BASE);

        /*Suspend the task*/
        vTaskSuspend(NULL);
    }

}

void CAN_TX_TASK(void)
{
    // uint8_t Node_Adress=0;
    tCANMsgObject sCANMessage;
    uint8_t ui8MsgData[2];
    uint8_t *pui8MsgData;

    pui8MsgData = (uint8_t *) &ui8MsgData;

    //
    // Initialize the message object that will be used for sending CAN
    // messages.  The message will be 4 bytes that will contain an incrementing
    // value.  Initially it will be set to 0.
    //
    // ui16MsgData = (1<<8)|0x02;
    ui8MsgData[0] = 0x01; /*src address*/
    ui8MsgData[1] = 0x02; /*dst address*/

    sCANMessage.ui32MsgID = 1;
    sCANMessage.ui32MsgIDMask = 0;
    sCANMessage.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
    //sCANMessage.ui32MsgLen = sizeof(pui8MsgData);
    sCANMessage.ui32MsgLen = 2;
    sCANMessage.pui8MsgData = pui8MsgData;

    //
    // Enter loop to send messages.  A new message will be sent once per
    // second.  The 4 bytes of message content will be treated as an uint32_t
    // and incremented by one each time.
    //
    while (1)
    {
        switch (STATE)

        {

            case STARTUP:

            // Print a message to the console showing the message count and the
            // contents of the message being sent.
            //
            UARTprintf("Sending msg: 0x%02X %02X ", pui8MsgData[0],
                    pui8MsgData[1]);
            //
            // Send the CAN message using object number 1 (not the same thing as
            // CAN ID, which is also 1 in this example).  This function will cause
            // the message to be transmitted right away.
            //
            CANMessageSet(CAN0_BASE, 1, &sCANMessage, MSG_OBJ_TYPE_TX);

            /*Turn-Off led after transmission*/
            GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_2), (ZERO));
            // vTaskDelay(1000);

#if 0
            //
            // Now wait 1 second before continuing
            //
            SimpleDelay();
#endif
            //
            // Check the error flag to see if errors occurred
            //

#if 0
            if (g_bErrFlag)
            {
                UARTprintf(" error - cable connected?\n");
            }
            else
            {
                //
                // If no errors then print the count of message sent
                //
                UARTprintf(" total count = %u\n", g_ui32MsgCount);
            }
#endif

            STATE = NORMAL;
            // vTaskDelay(1000);
            break;

            case NORMAL:
            // vTaskDelay(1000);
            break;

        }
        vTaskDelay(1000);
    }
}

void CAN_RX_TASK(void)
{
    //uint8_t Node_Adress=0;
    tCANMsgObject sCANMessage;
    uint8_t pui8MsgData[2];

    //
    // Initialize a message object to be used for receiving CAN messages with
    // any CAN ID.  In order to receive any CAN ID, the ID and mask must both
    // be set to 0, and the ID filter enabled.
    //
    sCANMessage.ui32MsgID = 0;
    sCANMessage.ui32MsgIDMask = 0;
    sCANMessage.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
    sCANMessage.ui32MsgLen = 2;

    //
    // Enter loop to process received messages.  This loop just checks a flag
    // that is set by the interrupt handler, and if set it reads out the
    // message and displays the contents.  This is not a robust method for
    // processing incoming CAN data and can only handle one messages at a time.
    // If many messages are being received close together, then some messages
    // may be dropped.  In a real application, some other method should be used
    // for queuing received messages in a way to ensure they are not lost.  You
    // can also make use of CAN FIFO mode which will allow messages to be
    // buffered before they are processed.
    //
    while (1)
    {
        unsigned int uIdx;

        switch (STATE)
        {

            case STARTUP:
            // vTaskDelay(1000);
            break;

            case NORMAL:

            //
            // Now load the message object into the CAN peripheral.  Once loaded the
            // CAN will receive any message on the bus, and an interrupt will occur.
            // Use message object 1 for receiving messages (this is not the same as
            // the CAN ID which can be any value in this example).
            //
            CANMessageSet(CAN0_BASE, 1, &sCANMessage, MSG_OBJ_TYPE_RX);

            //
            // If the flag is set, that means that the RX interrupt occurred and
            // there is a message ready to be read from the CAN
            //

            //
            // Reuse the same message object that was used earlier to configure
            // the CAN for receiving messages.  A buffer for storing the
            // received data must also be provided, so set the buffer pointer
            // within the message object.
            //
            sCANMessage.pui8MsgData = pui8MsgData;

            //
            // Read the message from the CAN.  Message object number 1 is used
            // (which is not the same thing as CAN ID).  The interrupt clearing
            // flag is not set because this interrupt was already cleared in
            // the interrupt handler.
            //
            CANMessageGet(CAN0_BASE, 1, &sCANMessage, 0);

            if ( g_bRXFlag && (sCANMessage.ui32MsgID == 2) )
            {

                //
                // Clear the pending message flag so that the interrupt handler can
                // set it again when the next message arrives.
                //
                g_bRXFlag = 0;

                /*Turn-on led once received a msg*/
                GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_2), (GPIO_PIN_2));

                //  vTaskDelay(1000);
#if 0
                //
                // Now wait 1 second before continuing
                //
                SimpleDelay();
#endif

                //
                // Check to see if there is an indication that some messages were
                // lost.
                //
#if 0
                if (sCANMessage.ui32Flags & MSG_OBJ_DATA_LOST)
                {
                    UARTprintf("CAN message loss detected\n");
                }
#endif
                //
                // Print out the contents of the message that was received.
                //
                UARTprintf("Msg ID=0x%08X len=%u data=0x",
                        sCANMessage.ui32MsgID, sCANMessage.ui32MsgLen);
                for (uIdx = 0; uIdx < sCANMessage.ui32MsgLen; uIdx++)
                {
                    UARTprintf("%02X ", pui8MsgData[uIdx]);
                }
#if 0
                UARTprintf("total count=%u\n", g_ui32MsgCount);
#endif
                STATE = STARTUP;
            }

            // vTaskDelay(1000);
            break;
        }

        vTaskDelay(1000);
    }

}

void LED_TASK(void)
{
    /*check if button1 is pressed turn-on led1 otherwise turn-off led1 */
    while (1)
    {

        GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_2), (GPIO_PIN_2));
        vTaskDelay(ONE_HUNDRED);

        GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_2), (ZERO));
        vTaskDelay(ONE_HUNDRED);

    }
}
#endif

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
#include "FreeRTOS_Files/FreeRTOS.h"
#include "FreeRTOS_Files/task.h"
#include "FreeRTOS_Files/queue.h"
#include "FreeRTOS_Files/semphr.h"
#include "FreeRTOS_Files/event_groups.h"
#include "HAL/LCD.h"
#include "HAL/Magic_Num.h"
#include "Delay.h"
#include "App_Tasks.h"

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/can.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

//*****************************************************************************
//
// A flag for the interrupt handler to indicate that a message was received for object 2 or 4
//
//*****************************************************************************
volatile bool g_bRX2Flag = 0;
volatile bool g_bRX4Flag = 0;

//*****************************************************************************
//
// Counters that are used to count the number of messages on each of the
// TX and RX message objects that are used in this example.
//
//*****************************************************************************
volatile uint32_t g_ui32MsgTX1Count = 0;
volatile uint32_t g_ui32MsgTX3Count = 0;
volatile uint32_t g_ui32MsgRX2Count = 0;
volatile uint32_t g_ui32MsgRX4Count = 0;

//*****************************************************************************
//
//  flags to indicate that CAN controller message object 1,3 has sent a message.
//
//*****************************************************************************
volatile bool g_bMsgObj1Sent = 0;
volatile bool g_bMsgObj3Sent = 0;

//*****************************************************************************
//
// A flag to indicate that some transmission or reception error occurred.
//
//*****************************************************************************
volatile bool g_bErrFlag = 0;

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
    if (ui32Status == CAN_INT_INTID_STATUS)
    {
        //
        // Read the controller status.  This will return a field of status
        // error bits that can indicate various errors.  Error processing
        // is not done in this example for simplicity.  Refer to the
        // API documentation for details about the error status bits.
        // The act of reading this status will clear the interrupt.  If the
        // CAN peripheral is not connected to a CAN bus with other CAN devices
        // present, then errors will occur and will be indicated in the
        // controller status.
        //
        ui32Status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);

        //
        // Set a flag to indicate some errors may have occurred.
        //
        g_bErrFlag = 1;
    }

    //
    // Check if the cause is message object 1, which is used for sending
    // message 1.
    //
    else if (ui32Status == 1)
    {
        //
        // Getting to this point means that the TX interrupt occurred on
        // message object 1, and the message TX is complete.  Clear the
        // message object interrupt.
        //
        CANIntClear(CAN0_BASE, 1);

        //
        // Increment a counter to keep track of how many messages have been
        // sent.  In a real application this could be used to set flags to
        // indicate when a message is sent.
        //
        g_ui32MsgTX1Count++;

        //
        // Since the message was sent, clear any error flags.
        //
        g_bErrFlag = 0;
    }
    //
    // Check if the cause is message object 3, which is used for sending
    // message 3.
    //
    else if (ui32Status == 3)
    {
        //
        // Getting to this point means that the TX interrupt occurred on
        // message object 3, and the message TX is complete.  Clear the
        // message object interrupt.
        //
        CANIntClear(CAN0_BASE, 3);

        //
        // Increment a counter to keep track of how many messages have been
        // sent.  In a real application this could be used to set flags to
        // indicate when a message is sent.
        //
        g_ui32MsgTX3Count++;

        //
        // Since the message was sent, clear any error flags.
        //
        g_bErrFlag = 0;
    }

    //
    // Check if the cause is message object 2, which is used for receiving
    // message 2.
    //
    else if (ui32Status == 2)
    {
        //
        // Getting to this point means that the TX interrupt occurred on
        // message object 2, and the message TX is complete.  Clear the
        // message object interrupt.
        //
        CANIntClear(CAN0_BASE, 2);

        // Set flag to indicate received message is pending for this message
        // object.
        //
        g_bRX2Flag = 1;

        //
        // Increment a counter to keep track of how many messages have been
        // received.In a real application this could be used to set flags to
        // indicate when a message is received.
        //
        g_ui32MsgRX2Count++;

        //
        // Since the message was received, clear any error flags.
        //
        g_bErrFlag = 0;
    }

    //
    // Check if the cause is message object 4, which is used for sending
    // message 4.
    //
    else if (ui32Status == 4)
    {
        //
        // Getting to this point means that the TX interrupt occurred on
        // message object 4, and the message TX is complete.  Clear the
        // message object interrupt.
        //
        CANIntClear(CAN0_BASE, 4);

        // Set flag to indicate received message is pending for this message
        // object.
        //
        g_bRX4Flag = 1;

        //
        // Increment a counter to keep track of how many messages have been
        // received.In a real application this could be used to set flags to
        // indicate when a message is received.
        //
        g_ui32MsgRX4Count++;

        //
        // Since the message was received, clear any error flags.
        //
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

//*****************************************************************************
//
// CAN message objects that will hold the separate CAN messages.  These could
// also be allocated on the stack but be careful because these structures
// each take about 20 bytes.
//
//*****************************************************************************
tCANMsgObject g_sCANMsgObjectTX1; /*Mailbox for transmission*/
tCANMsgObject g_sCANMsgObjectTX3; /*Mailbox for transmission*/
tCANMsgObject g_sCANMsgObjectRX2; /*Mailbox for reception*/
tCANMsgObject g_sCANMsgObjectRX4; /*Mailbox for reception*/

//*****************************************************************************
// Message buffer that hold the contents of the message(PDU) that
// is being transmitted.with 2 bytes length.
// 1st byte:src address(0) --- 2nd byte:dst address(1)
//*****************************************************************************
uint8_t g_pui8MsgTX1[2] = { 1, 2 };
uint8_t g_pui8MsgTX3[2] = { 1, 0 };

//*****************************************************************************
//
// This function provides a 1 second delay using a simple polling method.
//
//*****************************************************************************
void SimpleDelay(void)
{
    //
    // Delay cycles for 1 second
    //
    SysCtlDelay(16000000 / 3);
}

/*Flag To define the current state of the node*/
volatile bool STATE = STARTUP;

/*Flag To define the current state of the BUTTON*/
volatile bool REVERSE = NO;

//*****************************************************************************
//
// This function sets up UART0 to be used for a console to display information
// as the example is running.
//
//*****************************************************************************
void InitConsole(void)
{
    //
    // Enable GPIO port A which is used for UART0 pins.
    // TODO: change this to whichever GPIO port you are using.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Configure the pin muxing for UART0 functions on port A0 and A1.
    // This step is not necessary if your part does not support pin muxing.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    //
    // Enable UART0 so that we can configure the clock.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Select the alternate (UART) function for these pins.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
}

//*****************************************************************************
//
// This function prints some information about the CAN message to the
// serial port for information purposes only.
//
//*****************************************************************************
void PrintCANMessageInfo_TX(tCANMsgObject *psCANMsg, uint32_t ui32MsgObj)
{
    unsigned int uIdx;

    UARTprintf("Sending msg: obj=%d ID=0x%04X msg=0x", ui32MsgObj,
               psCANMsg->ui32MsgID);
    for (uIdx = 0; uIdx < psCANMsg->ui32MsgLen; uIdx++)
    {
        UARTprintf("%02X ", psCANMsg->pui8MsgData[uIdx]);
    }
    UARTprintf("\n");
}

//*****************************************************************************
//
// This function prints some information about the CAN message to the
// serial port for information purposes only.
//
//*****************************************************************************
void PrintCANMessageInfo_RX(tCANMsgObject *psCANMsg, uint32_t ui32MsgObj)
{
    unsigned int uIdx;

    //
    // Check to see if there is an indication that some messages were
    // lost.
    //
    if (psCANMsg->ui32Flags & MSG_OBJ_DATA_LOST)
    {
        UARTprintf("CAN message loss detected on message object %d\n",
                   ui32MsgObj);
    }

    //
    // Print out the contents of the message that was received.
    //
    UARTprintf("Msg Obj=%u ID=0x%05X len=%u data=0x", ui32MsgObj,
               psCANMsg->ui32MsgID, psCANMsg->ui32MsgLen);
    for (uIdx = 0; uIdx < psCANMsg->ui32MsgLen; uIdx++)
    {
        UARTprintf("%02X ", psCANMsg->pui8MsgData[uIdx]);
    }
    UARTprintf("\n");
}

void Init_Task(void)
{
    while (ONE)
    {
        /*Enable clk for portf*/
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

        /*Wait for portf to complete initialization*/
        while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
        {
        }


        /*Unlock portf pin0*/
        HWREG(GPIO_PORTF_BASE+GPIO_O_LOCK) = GPIO_LOCK_KEY;
        HWREG(GPIO_PORTF_BASE+GPIO_O_CR) |= HEX_ONE;

        /* Set portf pin2 as output for led1 and led2*/
        GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2 | GPIO_PIN_3);

        /* Set portf pin0 and pin4 as Input for Button1 and Button2*/
        GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);

        /*Configure portf pin4 and pin0 as pullup*/
        GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4,
        GPIO_STRENGTH_4MA,
                         GPIO_PIN_TYPE_STD_WPU);

#if defined(TARGET_IS_TM4C129_RA0) ||                                         \
    defined(TARGET_IS_TM4C129_RA1) ||                                         \
    defined(TARGET_IS_TM4C129_RA2)
        uint32_t ui32SysClock;
#endif

        //
        // Set the clocking to run directly from the external crystal/oscillator.
        // TODO: The SYSCTL_XTAL_ value must be changed to match the value of the
        // crystal used on your board.
        //
#if defined(TARGET_IS_TM4C129_RA0) ||                                         \
    defined(TARGET_IS_TM4C129_RA1) ||                                         \
    defined(TARGET_IS_TM4C129_RA2)
        ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                        SYSCTL_OSC_MAIN |
                        SYSCTL_USE_OSC)
                25000000);
#else
        SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
        SYSCTL_XTAL_16MHZ);
#endif

        //
        // Set up the serial console to use for displaying messages.  This is
        // just for this example program and is not needed for CAN operation.
        //
        InitConsole();

        //
        // For this example CAN0 is used with RX and TX pins on port B4 and B5.
        // The actual port and pins used may be different on your part, consult
        // the data sheet for more information.
        // GPIO port B needs to be enabled so these pins can be used.
        // TODO: change this to whichever GPIO port you are using
        //
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

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
        GPIOPinTypeCAN(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5);

        //
        // The GPIO port and pins have been set up for CAN.  The CAN peripheral
        // must be enabled.
        //
        SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);

        //
        // Initialize the CAN controller
        //
        CANInit(CAN0_BASE);

        //
        // Set up the bit rate for the CAN bus.  This function sets up the CAN
        // bus timing for a nominal configuration.  You can achieve more control
        // over the CAN bus timing by using the function CANBitTimingSet() instead
        // of this one, if needed.
        // In this example, the CAN bus is set to 500 kHz.  In the function below,
        // the call to SysCtlClockGet() or ui32SysClock is used to determine the
        // clock rate that is used for clocking the CAN peripheral.  This can be
        // replaced with a  fixed value if you know the value of the system clock,
        // saving the extra function call.  For some parts, the CAN peripheral is
        // clocked by a fixed 8 MHz regardless of the system clock in which case
        // the call to SysCtlClockGet() or ui32SysClock should be replaced with
        // 8000000.  Consult the data sheet for more information about CAN
        // peripheral clocking.
        //
#if defined(TARGET_IS_TM4C129_RA0) ||                                         \
    defined(TARGET_IS_TM4C129_RA1) ||                                         \
    defined(TARGET_IS_TM4C129_RA2)
        CANBitRateSet(CAN0_BASE, ui32SysClock, 500000);
#else
        CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 500000);
#endif

        //
        // Enable interrupts on the CAN peripheral.  This example uses static
        // allocation of interrupt handlers which means the name of the handler
        // is in the vector table of startup code.  If you want to use dynamic
        // allocation of the vector table, then you must also call CANIntRegister()
        // here.
        //
        // CANIntRegister(CAN0_BASE, CANIntHandler); // if using dynamic vectors
        //
        CANIntEnable(CAN0_BASE,
        CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);

        //
        // Enable the CAN interrupt on the processor (NVIC).
        //
        IntEnable(INT_CAN0);

        //
        // Enable the CAN for operation.
        //
        CANEnable(CAN0_BASE);

        /*Suspend the task*/
        vTaskSuspend(NULL);
    }

}

/*a task for node0 with lower address*/
void CAN_NODE0_TASK(void)
{

    /* Initialize the message object that will be used for sending CAN
     ** messages.  The message will be 2 bytes that will contain the PDU_Token
     */
    g_sCANMsgObjectTX1.ui32MsgID = 0x3001; /*Tx to ECU0 in normal case*/
    g_sCANMsgObjectTX1.ui32MsgIDMask = 0;
    g_sCANMsgObjectTX1.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
    g_sCANMsgObjectTX1.ui32MsgLen = 2;
    g_sCANMsgObjectTX1.pui8MsgData = g_pui8MsgTX1;

    g_sCANMsgObjectTX3.ui32MsgID = 0x3002;/*Tx to ECU1 in reverse case*/
    g_sCANMsgObjectTX3.ui32MsgIDMask = 0;
    g_sCANMsgObjectTX3.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
    g_sCANMsgObjectTX3.ui32MsgLen = 2;
    g_sCANMsgObjectTX3.pui8MsgData = g_pui8MsgTX3;

    // Initialize a message object to receive CAN messages with ID 0x2001.
    // The expected ID must be set along with the mask to indicate that all
    // bits in the ID must match.
    //
    g_sCANMsgObjectRX2.ui32MsgID = 0x2001;  /*RX from ECU1 in normal case*/
    g_sCANMsgObjectRX2.ui32MsgIDMask = 0xfffff;
    g_sCANMsgObjectRX2.ui32Flags = (MSG_OBJ_RX_INT_ENABLE
            | MSG_OBJ_USE_ID_FILTER);
    g_sCANMsgObjectRX2.ui32MsgLen = 8;

    g_sCANMsgObjectRX4.ui32MsgID = 0x1002;  /*RX from ECU0 in reverse case*/
    g_sCANMsgObjectRX4.ui32MsgIDMask = 0xfffff;
    g_sCANMsgObjectRX4.ui32Flags = (MSG_OBJ_RX_INT_ENABLE
            | MSG_OBJ_USE_ID_FILTER);
    g_sCANMsgObjectRX4.ui32MsgLen = 8;

    //
    // Now load the message object into the CAN peripheral message object 2.
    // Once loaded the CAN will receive any messages with this CAN ID into
    // this message object, and an interrupt will occur.
    //
    CANMessageSet(CAN0_BASE, 2, &g_sCANMsgObjectRX2, MSG_OBJ_TYPE_RX);

    CANMessageSet(CAN0_BASE, 4, &g_sCANMsgObjectRX4, MSG_OBJ_TYPE_RX);

    uint8_t pui8MsgDataRX[8]; /*receive buffer*/

    //STATE=NORMAL;

    /*Enter loop to send and receive messages. */
    while (1)
    {
        switch (STATE)

        {

        case STARTUP:
            /*Receiving msg*/
            // If the flag for message object 2 is set, that means that the RX
            // interrupt occurred and there is a message ready to be read from
            // this CAN message object.
            //
            if (g_bRX2Flag)
            {
                  REVERSE = NO;
                // Reuse the same message object that was used earlier to configure
                // the CAN for receiving messages.  A buffer for storing the
                // received data must also be provided, so set the buffer pointer
                // within the message object.  This same buffer is used for all
                // messages in this example, but your application could set a
                // different buffer each time a message is read in order to store
                // different messages in different buffers.
                //
                g_sCANMsgObjectRX2.pui8MsgData = pui8MsgDataRX;

                //
                // Read the message from the CAN.  Message object number 2 is used
                // (which is not the same thing as CAN ID).  The interrupt clearing
                // flag is not set because this interrupt was already cleared in
                // the interrupt handler.
                //
                CANMessageGet(CAN0_BASE, 2, &g_sCANMsgObjectRX2, 0);

                /*Turn-on led once received a msg*/
                GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_2), (GPIO_PIN_2));
                //GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_2), (ZERO));

                //
                // Clear the pending message flag so that the interrupt handler can
                // set it again when the next message arrives.
                //
                g_bRX2Flag = 0;

                vTaskDelay(1000); /* 1 second delay*/

                STATE = NORMAL; /*go to normal state*/

                //
                // Print information about the message just received.
                //
                PrintCANMessageInfo_RX(&g_sCANMsgObjectRX2, 2);

            }

            /*Receiving msg*/
            // If the flag for message object 4 is set, that means that the RX
            // interrupt occurred and there is a message ready to be read from
            // this CAN message object 4.
            //
            else if (g_bRX4Flag)
            {
                 REVERSE = YES;

                g_sCANMsgObjectRX4.pui8MsgData = pui8MsgDataRX;

                CANMessageGet(CAN0_BASE, 4, &g_sCANMsgObjectRX4, 0);

                /*Turn-on led once received a msg*/
                GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_2), (GPIO_PIN_2));
                //GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_2), (ZERO));

                g_bRX4Flag = 0;

                vTaskDelay(1000); /* 1 second delay*/

                STATE = NORMAL; /*go to normal state*/

                PrintCANMessageInfo_RX(&g_sCANMsgObjectRX4, 4);
            }

            // vTaskDelay(1000); /* 1 second delay*/
            break;

        case NORMAL:
            /*Transmitting msg*/
            /* Send message 1 using CAN controller message object 1.  This is
             ** the only message sent using this message object.  The
             ** CANMessageSet() function will cause the message to be sent right
             ** away.
             */
            if (REVERSE == YES)
            {

                PrintCANMessageInfo_TX(&g_sCANMsgObjectTX3, 3);
                CANMessageSet(CAN0_BASE, 3, &g_sCANMsgObjectTX3,
                              MSG_OBJ_TYPE_TX);

                /*Turn-Off led */
                //GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_3), (ZERO));
                GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_2), (ZERO));

                // vTaskDelay(1000); /* 1 second delay*/

                /* Check the error flag to see if errors occurred */
                if (g_bErrFlag)
                {
                    UARTprintf(" error - cable connected?\n");
                }
                else
                {
                    //
                    // If no errors then print the count of message sent
                    //
                    UARTprintf(" total count = %u\n", g_ui32MsgTX3Count);
                }

                STATE = STARTUP; /*GO to startup state*/

            }

            else
            {
                PrintCANMessageInfo_TX(&g_sCANMsgObjectTX1, 1);
                CANMessageSet(CAN0_BASE, 1, &g_sCANMsgObjectTX1,
                              MSG_OBJ_TYPE_TX);

                /*Turn-Off led */
                GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_2), (ZERO));
                //GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_3), (ZERO));

                // vTaskDelay(1000); /* 1 second delay*/

                /* Check the error flag to see if errors occurred */
                if (g_bErrFlag)
                {
                    UARTprintf(" error - cable connected?\n");
                }
                else
                {
                    //
                    // If no errors then print the count of message sent
                    //
                    UARTprintf(" total count = %u\n", g_ui32MsgTX1Count);
                }

                STATE = STARTUP; /*GO to startup state*/

            }
            // vTaskDelay(1000); /* 1 second delay*/
            break;
        }

    }
}

/*Task that increments the number of pressed times of button2 if it is pressed and send
 it to the queue*/
void BUTTON_TASK(void)
{
    /*a variable to check the previous state of the button2*/
    uint8_t Prev_Status = ONE;
    /*a variable to check the current state of the button2*/
    uint8_t Current_Status = ONE;

    while (1)
    {
        /*check if button2 is pressed*/
        if (GPIOPinRead(GPIO_PORTF_BASE, (GPIO_PIN_0)) == ZERO)
        {
            Current_Status = ZERO;
            if (Prev_Status == ONE)
            {
                if (REVERSE == YES)
                    REVERSE = NO;
                else
                    REVERSE = YES;
                Prev_Status = Current_Status;
                vTaskDelay(ONE_HUNDRED);
            }
        }
        else
        {
            Current_Status = ONE;
            Prev_Status = Current_Status;
            vTaskDelay(ONE_HUNDRED);
        }

    }
}
