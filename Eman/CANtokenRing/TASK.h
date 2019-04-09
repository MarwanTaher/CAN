/*
 * TASK.h
 *
 *  Created on: Mar 18, 2019
 *      Author: AVE-LABS-50
 */

#ifndef TASK_H_
#define TASK_H_
#include "include/event_groups.h"
#include "include/queue.h"

typedef void * TaskHandl;

QueueHandle_t xQueue;


#define QUEUE_LENGTH 4
#define QUEUE_ITEM_SIZE 1


void pushBUTTON(void *pvParameters);
void CAN_TX_TASK(void *pvParameters);
//void CAN_TX2_TASK(void *pvParameters);
void CAN_startup_TASK(void *pvParameters);
/*********************************************************************************/
/* FUNCTION NAME: CAN_RX                                                          */
/* @Param: *pvParameters                                                         */
/* return: void                                                                  */
/* FUNCTION Description: task receive data from spi                              */
/*********************************************************************************/
 void CAN_RX_TASK(void *pvParameters);
 //void CAN_RX_TASK(void *pvParameters);
 /*********************************************************************************/
 /* FUNCTION NAME: LCD                                                            */
 /* @Param: *pvParameters                                                         */
 /* return: void                                                                  */
 /* FUNCTION Description: display lcd                                             */
 /*********************************************************************************/
 void LCD(void *pvParameters);


/*********************************************************************************/
/* FUNCTION NAME: Tasks_Init                                                     */
/* @Param: *pvParameters                                                         */
/* return: void                                                                  */
/* FUNCTION Description: initialization of GPIO for led and pushbutton and lcd   */
/*********************************************************************************/
 void Tasks_Init(void *pvParameters);

#if 0
 if ((sCANMessage.ui32MsgID )==3)
            {
                if (GPIOPinRead(GPIO_PORTF_BASE, (GPIO_PIN_4)) == NUM_0)
                {
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
                    CANMessageGet(CAN0_BASE, 1, &sCANMessage, 0);

                    GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_1), (GPIO_PIN_1)); /* set high on led */

                    //
                    // Clear the pending message flag so that the interrupt handler can
                    // set it again when the next message arrives.
                    //
                    g_bRXFlag = 0;

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
                    UARTprintf("Msg ID=0x%08X len=%u data=0x",
                            sCANMessage.ui32MsgID, sCANMessage.ui32MsgLen);
                    for (uIdx = 0; uIdx < sCANMessage.ui32MsgLen; uIdx++)
                    {
                        UARTprintf("%02X ", pui8MsgData[uIdx]);
                    }
                    UARTprintf("total count=%u\n", g_ui32MsgCount);

                    vTaskDelay(NUM_1000);
                }
                else()
                {
                    //Discard Message
                }
            }
            else
            {
                if ((sCANMessage.ui32MsgID )==2)
                {
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
                    CANMessageGet(CAN0_BASE, 1, &sCANMessage, 0);

                    GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_1), (GPIO_PIN_1)); /* set high on led */

                    //
                    // Clear the pending message flag so that the interrupt handler can
                    // set it again when the next message arrives.
                    //
                    g_bRXFlag = 0;

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
                    UARTprintf("Msg ID=0x%08X len=%u data=0x",
                            sCANMessage.ui32MsgID, sCANMessage.ui32MsgLen);
                    for (uIdx = 0; uIdx < sCANMessage.ui32MsgLen; uIdx++)
                    {
                        UARTprintf("%02X ", pui8MsgData[uIdx]);
                    }
                    UARTprintf("total count=%u\n", g_ui32MsgCount);

                    vTaskDelay(NUM_1000);
                }
                else()
                {
                    //Discard Message
                }

            }
        }





    if(pui8MsgData[0]==1)
               {
               if ((sCANMessage.ui32MsgID )==2)
               {
                   if (GPIOPinRead(GPIO_PORTF_BASE, (GPIO_PIN_4)) == NUM_0)
                   {
                   }
                   else
                   {

                   }
               }
               else
               {

               }
               pui8MsgData[0]=0;
    }
    //vTaskDelay(NUM_1000);
    GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_1), 0); /* set low on led */
#endif

#endif /* TASK_H_ */


