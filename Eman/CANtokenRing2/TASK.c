/*
 * TASK.c
 *
 *  Created on: Mar 18, 2019
 *      Author: AVE-LABS-50
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/can.h"

#include "SPI_FILE/SPI.h"
#include "LCD/LCD.h"
#include "CAN/CAN.h"
#include "TASK.h"
#include "Types.h"
#include "include/task.h"

#define mask_Dist 0x1f
#define mask_CMD 0xE0

TaskHandl x;
QueueHandle_t SPI_RECIEVE_H;

uint8_t volatile flag = NUM_0;
uint8_t volatile flag1 = NUM_0;
uint8_t volatile token = NUM_0;
uint8_t volatile count = NUM_0;
uint8_t volatile PB = NUM_0;

#if 0
0x81 = 1000 0001 /1
0x83 = 1000 0011 /2
0x85 = 1000 0101 /3
0x87 = 1000 0111
Mask Register = 1111 1001
mask1 = 1111 1001 /0xf9
mask2 = 1111 1001
mask3 = 1111 1001
#endif

void LED1_Blinking(void *pvParameters)
{

    while (1)
    {

        GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_1), (GPIO_PIN_1)); /* set high on led */
        vTaskDelay(NUM_100); /* delay 100m sec */

    }
}

/*********************************************************************************/
/* FUNCTION NAME: Tasks_Init                                                     */
/* @Param: *pvParameters                                                         */
/* return: void                                                                  */
/* FUNCTION Description: initialization of GPIO for led and pushbutton           */
/*********************************************************************************/
void Tasks_Init(void *pvParameters)
{
    while (1)
    {
        /* initialization of GPIOF LEDS PINS */
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); //clk

        while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
        {
        }

        GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,
        GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3); //SET direction output OF GPIOF
        GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, (GPIO_PIN_4));
        GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_4MA,
        GPIO_PIN_TYPE_STD_WPU);

        CAN0RX_INIT();/*initialization rx*/
        CAN0TX_INIT();/*initialization tx*/
        vTaskSuspend(x); /* suspend the task */
    }
}

void pushBUTTON(void *pvParameters)
{

    while (1)
    {
        if(token == NUM_1)
        {
        while (GPIOPinRead(GPIO_PORTF_BASE, (GPIO_PIN_4)) == NUM_0)
        {
            count++;
            vTaskDelay(NUM_5);
        }
        if (count >= NUM_5)/*handle debouncing*/
        {
            PB = NUM_1;/*raise flag*/
            token = NUM_0 ;
        }

        count = NUM_0;
        }
        vTaskDelay(NUM_50);
    }
}


void CAN_TX_TASK(void *pvParameters)
{
    while (NUM_1)
    {
//if(flag1 == 1)
        {
            //CAN0_TX_node1();
            flag1 = 0;
        }
        vTaskDelay(150);
        //vTaskSuspend(x); /* suspend the task */
    }
}

/*********************************************************************************/
/* FUNCTION NAME: CAN_RX_TASK                                                  */
/* @Param: *pvParameters                                                         */
/* return: void                                                                  */
/* FUNCTION Description: task receive data from CAN_RX_TASK                      */
/*********************************************************************************/
void CAN_RX_TASK(void *pvParameters)
{

    tCANMsgObject sCANMessage;
    uint8_t pui8MsgData[8];
    //
    // Initialize a message object to be used for receiving CAN messages with
    // any CAN ID.  In order to receive any CAN ID, the ID and mask must both
    // be set to 0, and the ID filter enabled.
    //
    sCANMessage.ui32MsgID = 2;
    sCANMessage.ui32MsgIDMask = 0;/*RECEIVE ANY MSG CAUSE MASK = 0 SO RECEIVE ANY ID */
    sCANMessage.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
    sCANMessage.ui32MsgLen = 8;

    //
    // Now load the message object into the CAN peripheral.  Once loaded the
    // CAN will receive any message on the bus, and an interrupt will occur.
    // Use message object 1 for receiving messages (this is not the same as
    // the CAN ID which can be any value in this example).
    //
    CANMessageSet(CAN0_BASE, 2, &sCANMessage, MSG_OBJ_TYPE_RX);

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
        uint8_t data = NUM_0;
        //
        // If the flag is set, that means that the RX interrupt occurred and
        // there is a message ready to be read from the CAN
        //
        if (g_bRXFlag2) //Received done
        {
            //GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_1), (GPIO_PIN_1)); /* set high on led */

            //Receive Message
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
            CANMessageGet(CAN0_BASE, 2, &sCANMessage, 0);
            if ((sCANMessage.ui32MsgID) == 2)
            {

                token = NUM_1;
                GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_1), (GPIO_PIN_1)); /* set high on led1 */
#if 0
                vTaskDelay(NUM_1000);
                GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_2), 0); /* set low on led */
                GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_1), 0); /* set low on led */

                CAN0_TX_node3();                            //try 3
#endif
                if (*sCANMessage.pui8MsgData == 1) /* reverse mode cw */
                {
                        vTaskDelay(NUM_1000);
                        GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_1), 0); /* set low on led */
                        token = NUM_0;
                        if (PB == NUM_1)
                        {
                          PB = NUM_0;
                          data = NUM_0;/*transmitted data*/

                          CAN0_TX_node3(data);/*transmit to node 3*/


                    }
                    else
                    {

                        token = NUM_0;
                        data = NUM_1;/*transmitted data*/

                       CAN0_TX_node1(data);/*transmit to node 1*/
                    }

                }
                else //normal mode ccw
                {

                        vTaskDelay(NUM_1000);
                        GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_1), 0); /* set low on led */
                        token = NUM_0;
                        if (PB == NUM_1)
                        {
                             PB = NUM_0;
                             data = 1;/*transmitted data*/

                           CAN0_TX_node1(data);/*transmit to node 1*/
                    }
                    else
                    {

                        GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_1), 0); /* set low on led */
                        token = NUM_0;
                        data = NUM_0;/*transmitted data*/

                       CAN0_TX_node3(data);/*transmit to node 3*/
                    }

                }

            }
            //
            // Clear the pending message flag so that the interrupt handler can
            // set it again when the next message arrives.
            //
            g_bRXFlag2 = 0;

            //
            // Check to see if there is an indication that some messages were
            // lost.
            //
            if (sCANMessage.ui32Flags & MSG_OBJ_DATA_LOST)
            {
                UARTprintf("CAN message loss detected\n");
            }

            //
            // Print out the contents of the message that was received.
            //
            UARTprintf("Msg ID=0x%08X len=%u data=0x", sCANMessage.ui32MsgID,
                       sCANMessage.ui32MsgLen);
            for (uIdx = 0; uIdx < sCANMessage.ui32MsgLen; uIdx++)
            {
                UARTprintf("%02X ", pui8MsgData[uIdx]);
            }
            UARTprintf("total count=%u\n", g_ui32MsgCount);
#if 0
            if (pui8MsgData[0] == 1) /* reverse mode cw */
            {
                if (GPIOPinRead(GPIO_PORTF_BASE, (GPIO_PIN_4)) == NUM_0)
                {
                    vTaskDelay(NUM_1000);
                    GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_1), 0); /* set low on led */
                    pui8MsgData[0] = 1;
                    CAN0_TX_node3();

                }
                else
                {
                    vTaskDelay(NUM_1000);
                    GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_1), 0); /* set low on led */
                    //pui8MsgData[0] = 0;
                    CAN0_TX_node1();

                }

            }
            else //normal mode ccw (pui8MsgData[0] == 0)
            {

                if (GPIOPinRead(GPIO_PORTF_BASE, (GPIO_PIN_4)) == NUM_0)
                {
                    vTaskDelay(NUM_1000);
                    GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_1), 0); /* set low on led */
                    pui8MsgData[0] = 1;
                    CAN0_TX_node1();

                }
                else
                {
                    vTaskDelay(NUM_1000);
                    GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_2), 0); /* set low on led */
                    GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_1), 0); /* set low on led */
                    //pui8MsgData[0] = 0;
                    CAN0_TX_node1();//try 3
                    // GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_2), (GPIO_PIN_2)); /* set high on led */
                    //vTaskDelay(NUM_5);
                }
#endif

            //pui8MsgData[0] = 0;

        }

        vTaskDelay(50);
    }
}

