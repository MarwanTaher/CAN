/*
 * CAN.c
 *
 *  Created on: Apr 3, 2019
 *      Author: AVE-LAP-016
 */
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/can.h"
#include "driverlib/interrupt.h"
#include "utils/uartstdio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "switchs_tasks.h"
#include "leds_tasks.h"
#include "CAN.h"

tCANBitClkParms CANBitClk;
tCANMsgObject sCAN_TransmitMessage;
tCANMsgObject sCAN_ReceiveMessage;
//tCANMsgObject sCAN_Message;

uint8_t pui8ReceiveMsgData[8] = {0};
uint8_t pui8TransmitMsgData[8] = {0} ;
//uint8_t pui8MsgData[8] = {0} ;
void (*direction_LED)(void) = LED_RED_Enable ;
// A counter that keeps track of the number of times the TX interrupt has
// occurred, which should match the number of TX messages that were sent.
//
//*****************************************************************************
 volatile uint32_t g_ui32TransmitMsgCount  = 0 ;
 volatile uint32_t g_ui32ReceiveMsgCount = 0  ;

//*****************************************************************************
//
// A flag to indicate that some transmission error occurred.
//
//*****************************************************************************
 volatile bool g_bErrFlag = 0 ;

 //*****************************************************************************
 //
 // A flag for the interrupt handler to indicate that a message was received.
 //
 //*****************************************************************************
 volatile bool g_bRXFlag = 0;

 //*****************************************************************************
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


void CAN0_init(void)
{
    // Initialize the message object that will be used for sending CAN
       // messages.  The message will be 4 bytes that will contain an incrementing
       // value.  Initially it will be set to 0.
      pui8TransmitMsgData[0] = MY_ID ;
      direction_LED = LED_RED_Enable ;
      sCAN_TransmitMessage.ui32Flags = MSG_OBJ_TX_INT_ENABLE ;
      /* for sending and receiving 1 byte of data */
      sCAN_TransmitMessage.ui32MsgLen = 1;
      /* A buffer for sending the data stored in it */
      sCAN_TransmitMessage.pui8MsgData = &pui8TransmitMsgData[0];
      pui8TransmitMsgData[0] = MY_ID ;

      sCAN_ReceiveMessage.ui32MsgID = MY_ID;
      sCAN_ReceiveMessage.ui32MsgIDMask = 0xFF ;
      sCAN_ReceiveMessage.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
        /* for sending and receiving 1 byte of data */
      sCAN_ReceiveMessage.ui32MsgLen = 1;
        /* A buffer for storing the received data */
      sCAN_ReceiveMessage.pui8MsgData = &pui8ReceiveMsgData[0];



    // CAN0 is used with RX and TX pins on port B4 and B5.
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

       //
       // Configure the GPIO pin muxing to select CAN0 functions for these pins.

       GPIOPinConfigure(GPIO_PB4_CAN0RX);
       GPIOPinConfigure(GPIO_PB5_CAN0TX);

       //
       // Enable the alternate function on the GPIO pins.  The above step selects
       // which alternate function is available.  This step actually enables the
       // alternate function instead of GPIO for these pins.

       GPIOPinTypeCAN(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5);
    // Enable the CAN0 module.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);
    //
    // Wait for the CAN0 module to be ready.
    //
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_CAN0))
    {
    }
    // Reset the state of all the message objects and the state of the CAN
    // module to a known state.
    //
    CANInit(CAN0_BASE);
    // Enable interrupts on the CAN peripheral.  This example uses static
   // allocation of interrupt handlers which means the name of the handler
   // is in the vector table of startup code.  If you want to use dynamic
   // allocation of the vector table, then you must also call CANIntRegister()
   // here.
   //
   // CANIntRegister(CAN0_BASE, CANIntHandler); // if using dynamic vectors
   //
    CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 500000);
   CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);

   //
   // Enable the CAN interrupt on the processor (NVIC).
   //
   IntEnable(INT_CAN0);

    // Take the CAN0 device out of INIT state.
    //
    CANEnable(CAN0_BASE);


}

void CAN0_Transmit_task(void)
{
    while(1)
    {

        // Print a message to the console showing the message count and the
        // contents of the message being sent.
        //
        UARTprintf("Sending msg: 0x%02X %02X %02X %02X",
                   pui8TransmitMsgData[0], pui8TransmitMsgData[1], pui8TransmitMsgData[2],
                   pui8TransmitMsgData[3]);

        //
        // Send the CAN message using object number 1 (not the same thing as
        // CAN ID, which is also 1 in this example).  This function will cause
        // the message to be transmitted right away.
        //
        CANMessageSet(CAN0_BASE, TRANSMIT_STATUS, &sCAN_TransmitMessage, MSG_OBJ_TYPE_TX);

        //
        // Now wait 1 second before continuing
        //
        vTaskDelay(100);

        //
        // Check the error flag to see if errors occurred
        //
        if(g_bErrFlag)
        {
            UARTprintf(" error - cable connected?\n");
        }
        else
        {
            //
            // If no errors then print the count of message sent
            //
            UARTprintf(" total count = %u\n", g_ui32TransmitMsgCount);
        }

        //
        // Increment the value in the message data.
        //
        //ui32TransmitMsgData++;
    }

}
void CAN0_Receive_task(void)
{
    unsigned int uIdx;
    //
  // Now load the message object into the CAN peripheral.  Once loaded the
  // CAN will receive any message on the bus, and an interrupt will occur.
  // Use message object 1 for receiving messages (this is not the same as
  // the CAN ID which can be any value in this example).
  //
  CANMessageSet(CAN0_BASE, RECEIVE_STATUS, &sCAN_ReceiveMessage, MSG_OBJ_TYPE_RX);
    while(1)
    {
        //
       // If the flag is set, that means that the RX interrupt occurred and
       // there is a message ready to be read from the CAN
       //
       if(g_bRXFlag)
       {
           //
           // Reuse the same message object that was used earlier to configure
           // the CAN for receiving messages.  A buffer for storing the
           // received data must also be provided, so set the buffer pointer
           // within the message object.
           //
           sCAN_ReceiveMessage.pui8MsgData = pui8ReceiveMsgData;


           //
           // Read the message from the CAN.  Message object number 1 is used
           // (which is not the same thing as CAN ID).  The interrupt clearing
           // flag is not set because this interrupt was already cleared in
           // the interrupt handler.
           //
           CANMessageGet(CAN0_BASE, RECEIVE_STATUS, &sCAN_ReceiveMessage, 0);

           //
           // Clear the pending message flag so that the interrupt handler can
           // set it again when the next message arrives.
           //
           g_bRXFlag = 0;

           //
           // Check to see if there is an indication that some messages were
           // lost.
           //
           if(sCAN_ReceiveMessage.ui32Flags & MSG_OBJ_DATA_LOST)
           {
               UARTprintf("CAN message loss detected\n");
           }

           //
           // Print out the contents of the message that was received.
           //
           UARTprintf("Received Msg ID=0x%08X len=%u data=0x",
                      sCAN_ReceiveMessage.ui32MsgID, sCAN_ReceiveMessage.ui32MsgLen);
           for(uIdx = 0; uIdx < sCAN_ReceiveMessage.ui32MsgLen; uIdx++)
           {
               UARTprintf("%02X ", pui8ReceiveMsgData[uIdx]);
           }
           UARTprintf("total count=%u\n", g_ui32ReceiveMsgCount);
       }

       vTaskDelay(100);
    }

}


//*****************************************************************************
//
// This function is the interrupt handler for the CAN peripheral.  It checks
// for the cause of the interrupt, and maintains a count of all messages that
// have been transmitted.
//
//*****************************************************************************
void
CANIntHandler(void)
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
    // Check if the cause is message object 1, which what we are using for
    // sending messages.
    //
    else if(ui32Status == TRANSMIT_STATUS)
       {
           //
           // Getting to this point means that the RX interrupt occurred on
           // message object 1, and the message reception is complete.  Clear the
           // message object interrupt.
           //
           CANIntClear(CAN0_BASE, TRANSMIT_STATUS);

           //
           // Increment a counter to keep track of how many messages have been
           // received.  In a real application this could be used to set flags to
           // indicate when a message is received.
           //
           g_ui32TransmitMsgCount++;


           //
           // Since a message was received, clear any error flags.
           //
           g_bErrFlag = 0;
       }

       //
       // Check if the cause is message object 2.
       //
       else if(ui32Status == RECEIVE_STATUS)
       {
           CANIntClear(CAN0_BASE, RECEIVE_STATUS);
           g_ui32ReceiveMsgCount++;
           g_bRXFlag = 1;
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

void CAN0_Upgraded_Tranceive_task(void *pvParameters)
{
   uint8_t counter = 0 ;
   uint8_t state = 0 ;

    while(1)
    {
        /* ECU should enter startup state when power is turned on */
        if( state == STARTUP_STATE) /* start up state */
        {
            LED_WHITE_Enable();
            /* By default Send the talk to the next node and
             * this may be changed depending on the message source */

            /* The lowest address ECU transmit token to the higher address ECU
             *  and switch its state to normal state.*/
#if(MY_ID == NODE_1_ID)

            sCAN_TransmitMessage.ui32MsgID = FRONT_NODE_ID;

            /* passing the talk */
            pui8TransmitMsgData[0] = MY_ID ;

            /* Print a message to the console showing the message count and the
             * contents of the message being sent.
            */
            UARTprintf("\nSending msg: 0x%02X", *(sCAN_TransmitMessage.pui8MsgData) );

            //
            // Send the CAN message using object number 1 (not the same thing as
            // CAN ID, which is also 1 in this example).  This function will cause
            // the message to be transmitted right away.
            //
            CANMessageSet(CAN0_BASE, TRANSMIT_STATUS, &sCAN_TransmitMessage, MSG_OBJ_TYPE_TX);
            // Now wait 1 second before continuing
           //
           vTaskDelay(10);

           //
           // Check the error flag to see if errors occurred
           //
           if(g_bErrFlag)
           {
               UARTprintf(" first transmit error - cable connected?\n");
           }
           else
           {
               //
               // If no errors then print the count of message sent
               //
               state = NORMAL_STATE ;
               UARTprintf("\ntotal transmit count = %u\n", g_ui32TransmitMsgCount);
           }
#else
           /* By default all the ECUs except the lowest address ECU
            * mode are waiting until receiving the first token
            * and switch its state to normal state. */
           CANMessageSet(CAN0_BASE, RECEIVE_STATUS, &sCAN_ReceiveMessage, MSG_OBJ_TYPE_RX);

           if(g_bRXFlag)
           {
                state = NORMAL_STATE ;
           }
#endif
        }
        /* At Normal state:
          When token is received:
          Turn on led for 1 second.
          Pass token to higher address node after one second delay.
          Turn off the led.
         */
        else if( state == NORMAL_STATE )
        {
            LED_BLUE_Enable();
            /* Receiving */
            sCAN_ReceiveMessage.ui32MsgID = MY_ID;
            CANMessageSet(CAN0_BASE, RECEIVE_STATUS, &sCAN_ReceiveMessage, MSG_OBJ_TYPE_RX);

           if(g_bRXFlag)
           {
               (*direction_LED)();
               //LED_RED_Enable();
               while( counter < 1 )
               {
                   vTaskDelay(200);
                   counter++ ;
               }
                   counter = 0 ;
                   LED_BLUE_Enable();


               /* Read the message from the CAN.  Message object number "RECEIVE_STATUS"
                * is used (which is not the same thing as CAN ID).  The interrupt clearing
                * flag is not set because this interrupt was already cleared in
                * the interrupt handler.
                */
               CANMessageGet(CAN0_BASE, RECEIVE_STATUS, &sCAN_ReceiveMessage, 0);
               UARTprintf("CAN message loss detected%d\n",*(sCAN_ReceiveMessage.pui8MsgData));

               /* Clear the pending message flag so that the interrupt handler
                * can set it again when the next message arrives. */
               g_bRXFlag = 0;

         /* Check to see if there is an indication that some messages were lost. */
               if(sCAN_ReceiveMessage.ui32Flags & MSG_OBJ_DATA_LOST)
               {
                   UARTprintf("CAN message loss detected\n");
               }
               else
               {
                   //
                 // Print out the contents of the message that was received.
                 //
                 UARTprintf("\nReceived Msg ID=0x%08X len=%u data=0x%02X",
                            sCAN_ReceiveMessage.ui32MsgID, 1 ,  pui8ReceiveMsgData[0] );

                 UARTprintf("\ntotal Receive count=%u\n", g_ui32ReceiveMsgCount);

               }

/* Transmitting " pass the token " */

#if(MY_ID == LAST_NODE )
               /* if reverse round send to the back node
                *    || ( button1_status == PRESSED) */
              if( ( *(sCAN_ReceiveMessage.pui8MsgData) == NODE_1_ID ) )
              {
                  pui8TransmitMsgData[0] = MY_ID ;
                  /* if i am the last node so the next node is the back node */
                  sCAN_TransmitMessage.ui32MsgID = BACK_NODE_ID;
                  direction_LED = LED_GREEN_Enable ;
              }
               /* if normal round send to the front node */
              else
              {
                  pui8TransmitMsgData[0] = MY_ID ;
                  /* if i am the last node so the next node is the first node */
                  sCAN_TransmitMessage.ui32MsgID = NODE_1_ID;
                  direction_LED = LED_RED_Enable ;
              }

#elif(MY_ID == NODE_1_ID)
               /* if reverse round send to the back node
                *    || ( button1_status == PRESSED)*/
              if(( *(sCAN_ReceiveMessage.pui8MsgData) == FRONT_NODE_ID )  )
              {
                pui8TransmitMsgData[0] = MY_ID ;
                /* if i am the first node so the back node is the last node */
                sCAN_TransmitMessage.ui32MsgID = LAST_NODE;
                direction_LED = LED_GREEN_Enable ;

              }

               /* if normal round send to the front node */
              else
              {
                pui8TransmitMsgData[0] = MY_ID ;
                /* the next node is the front node */
                sCAN_TransmitMessage.ui32MsgID = FRONT_NODE_ID;
                direction_LED = LED_RED_Enable ;
              }


#else
               /* if reverse round send to the back node
                *    || ( button1_status == PRESSED)*/
             if( ( *(sCAN_ReceiveMessage.pui8MsgData) == FRONT_NODE_ID ) )
             {
                 pui8TransmitMsgData[0] = MY_ID ;
                 /* the back node is (MY_ID - 1) */
                 sCAN_TransmitMessage.ui32MsgID = BACK_NODE_ID;
                 direction_LED = LED_GREEN_Enable ;
             }
               /* if normal round send to the front node */
             else
              {
                 pui8TransmitMsgData[0] = MY_ID ;
                  /* the next node is the front node */
                 sCAN_TransmitMessage.ui32MsgID = FRONT_NODE_ID;
                 //direction_LED = LED_RED_Enable ;
              }


#endif
               /* Print a message to the console showing the message count and the
                * contents of the message being sent.
                */
               UARTprintf("\nSending msg: 0x%02X", *(sCAN_TransmitMessage.pui8MsgData) );

              /* This function will cause
               * the message to be transmitted right away.
               */
               CANMessageSet(CAN0_BASE, TRANSMIT_STATUS, &sCAN_TransmitMessage, MSG_OBJ_TYPE_TX);

               vTaskDelay(10);

               //
               // Check the error flag to see if errors occurred
               //
               if(g_bErrFlag)
               {
                   UARTprintf(" error - cable connected?\n");
               }
               else
               {
                   //
                   // If no errors then print the count of message sent
                   UARTprintf("\nSending msg: 0x%02X", *(sCAN_TransmitMessage.pui8MsgData) );

                   UARTprintf("\ntotal transmit count = %u\n", g_ui32TransmitMsgCount);
               }


           }
        }

       vTaskDelay(100);
    }

}


void read_button1(void)
{
   if( GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4) == 0 )
   {
     button1_status = 1 ;
   }
   else
   {
     button1_status = 0 ;
   }
}
