
#include <stdbool.h>
#include <stdint.h>
#include "driverlib/gpio.h"
#include "utils/uartstdio.h"
#include "FreeRTOS/Includes/FreeRTOS.h"
#include "FreeRTOS/Includes/task.h"
#include "FreeRTOS/Includes/queue.h"
#include "FreeRTOS/Includes/semphr.h"
#include "Drivers/LEDs/inc/LEDs.h"
#include "Drivers/Switch/inc/Switch.h"
#include "FreeRTOS/Includes/event_groups.h"
#include "driverlib/can.h"
#include "Tasks.h"
#include "Drivers/LCD/inc/LCD.h"
#include "Drivers/KeyPad/inc/Keypad.h"
#include "Drivers/UART/inc/uart.h"
#include "Drivers/SPI/inc/spi.h"
#include "Drivers/CAN/CAN.h"


/******************************************************************************/
/* The Nodes definations.                                     */
/******************************************************************************/

#define NODE_1          1
#define NODE_2          0
#define NODE_3          0


/******************************************************************************/
/* The stack size for CAN task.                                            */
/******************************************************************************/
#define CANSTACKSIZE        200
/******************************************************************************/
/* The stack size for the SW task.                                            */
/******************************************************************************/
#define SWTASKSTACKSIZE        128

/******************************************************************************/
/* The stack size for the Main task.                                          */
/******************************************************************************/
#define MAINTASKSTACKSIZE        200


/******************************************************************************/
/* The priorities of the various tasks.                                       */
/******************************************************************************/
#define PRIORITY_MAIN_TASK          5
#define PRIORITY_SW_TASK            4
#define PRIORITY_CAN_TASK           3
//*****************************************************************************/
/* The error routine that is called if the driver library encounters an error.*/
//*****************************************************************************/
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}

#endif

/*****************************************************************************/
/* This hook is called by FreeRTOS when an stack overflow error is detected. */
/*****************************************************************************/
void
vApplicationStackOverflowHook(xTaskHandle *pxTask, char *pcTaskName)
{
    /***************************************************************************/
    /* This function can not return, so loop forever.  Interrupts are disabled */
    /* on entry to this function, so no processor interrupts will interrupt    */
    /* this loop.                                                              */
    /***************************************************************************/
    while(1)
    {
    }
}

int main(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
      while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));

      GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,(GPIO_PIN_0 | GPIO_PIN_1 |GPIO_PIN_2|GPIO_PIN_3));


        /***************************************************/
        /* Set the clocking to run at 50 MHz from the PLL. */
        /***************************************************/
        ROM_SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |
                           SYSCTL_OSC_MAIN);
        //*****************************************************************************
        //
        // A flag for the interrupt handler to indicate that a message was received.
        //
        //*****************************************************************************
        volatile bool g_bRXFlag = 1;
        volatile bool g_bTXFlag = 0;


        //*****************************************************************************
        //
        // A flag to indicate that some transmission error occurred.
        //
        //*****************************************************************************
        volatile bool g_bErrFlag = 0;


        /***************************************************/
        /* Define SEND CAN Structures.    */
        /***************************************************/
        extern tCANMsgObject sCANMessageTX;
        extern uint8_t *pui8MsgDataout;
        extern uint32_t ui32MsgDataout;


        extern tCANMsgObject sCANMessageRX;
        extern tCANMsgObject sCANMessageRXG;
        extern uint8_t pui8MsgDatain[8];
        extern uint8_t pui8MsgDataing[8];



#if NODE_1
       // ui32MsgDataout = 0;
        sCANMessageTX.ui32MsgID = 1;
        sCANMessageTX.ui32MsgIDMask = 0;
        sCANMessageTX.ui32Flags = 0;
        sCANMessageTX.ui32MsgLen = 1;
        sCANMessageTX.pui8MsgData = pui8MsgDataout;

       // CANMessageSet(CAN0_BASE, 2, &sCANMessageTX, MSG_OBJ_TYPE_TX);


        /***************************************************/
         /* Define REC CAN Structures.    */
         /***************************************************/

        //
         // Configure a receive object.
         //
         sCANMessageRX.ui32MsgID = 2;
         sCANMessageRX.ui32MsgIDMask = 0xFFFFF;
         sCANMessageRX.ui32Flags =   MSG_OBJ_USE_ID_FILTER | MSG_OBJ_RX_INT_ENABLE;
         sCANMessageRX.ui32MsgLen = 1;
         sCANMessageRX.pui8MsgData = pui8MsgDatain;


         sCANMessageRXG.ui32MsgID = 0;
         sCANMessageRXG.ui32MsgIDMask = 0xFFFFF;
         sCANMessageRXG.ui32Flags =   MSG_OBJ_USE_ID_FILTER | MSG_OBJ_RX_INT_ENABLE;
         sCANMessageRXG.ui32MsgLen = 1;
         sCANMessageRXG.pui8MsgData = pui8MsgDatain;

        // CANMessageSet(CAN0_BASE, 1, &sCANMessageRX, MSG_OBJ_TYPE_RX);
#endif

#if NODE_2
         /***************************************************/
          /* Define SEND CAN Structures.    */
          /***************************************************/
          //ui32MsgDataout = 0;
          sCANMessageTX.ui32MsgID = 3;
          sCANMessageTX.ui32MsgIDMask = 0;
          sCANMessageTX.ui32Flags = 0;
          sCANMessageTX.ui32MsgLen = 1;
          sCANMessageTX.pui8MsgData = pui8MsgDataout;


         // CANMessageSet(CAN0_BASE, 3, &sCANMessageTX, MSG_OBJ_TYPE_TX);
          /***************************************************/
           /* Define REC CAN Structures.    */
           /***************************************************/

          //
           // Configure a receive object.
           //
           sCANMessageRX.ui32MsgID = 4;
           sCANMessageRX.ui32MsgIDMask = 0xFFFFFF;
           sCANMessageRX.ui32Flags = MSG_OBJ_USE_ID_FILTER | MSG_OBJ_RX_INT_ENABLE;
           sCANMessageRX.ui32MsgLen = 1;
           sCANMessageRX.pui8MsgData = pui8MsgDatain;

           sCANMessageRXG.ui32MsgID = 0;
           sCANMessageRXG.ui32MsgIDMask = 0xFFFFFF;
           sCANMessageRXG.ui32Flags =   MSG_OBJ_USE_ID_FILTER | MSG_OBJ_RX_INT_ENABLE;
           sCANMessageRXG.ui32MsgLen = 1;
           sCANMessageRXG.pui8MsgData = pui8MsgDatain;


#endif

#if NODE_3

           /***************************************************/
                   /* Define SEND CAN Structures.    */
                   /***************************************************/


                 //  ui32MsgDataout = 0;
                   sCANMessageTX.ui32MsgID = 5;
                   sCANMessageTX.ui32MsgIDMask = 0;
                   sCANMessageTX.ui32Flags = 0;
                   sCANMessageTX.ui32MsgLen = sizeof(pui8MsgDataout);
                   sCANMessageTX.pui8MsgData = pui8MsgDataout;

                  // CANMessageSet(CAN0_BASE, 1, &sCANMessageTX, MSG_OBJ_TYPE_TX);
                   /***************************************************/
                    /* Define REC CAN Structures.    */
                    /***************************************************/
                   //
                    // Configure a receive object.
                    //
                    sCANMessageRX.ui32MsgID = 6;
                    sCANMessageRX.ui32MsgIDMask = 0xFFFFFF;
                    sCANMessageRX.ui32Flags = MSG_OBJ_USE_ID_FILTER | MSG_OBJ_RX_INT_ENABLE;
                    sCANMessageRX.ui32MsgLen = sizeof(pui8MsgDatain);
                    sCANMessageRX.pui8MsgData = pui8MsgDatain;


                    sCANMessageRXG.ui32MsgID = 0;
                    sCANMessageRXG.ui32MsgIDMask = 0xFFFFFF;
                    sCANMessageRXG.ui32Flags =   MSG_OBJ_USE_ID_FILTER | MSG_OBJ_RX_INT_ENABLE;
                    sCANMessageRXG.ui32MsgLen = 1;
                    sCANMessageRXG.pui8MsgData = pui8MsgDatain;
                   // CANMessageSet(CAN0_BASE, 1, &sCANMessageRX, MSG_OBJ_TYPE_RX);



#endif

        /***************************************************/
        /* Create MainTaks that initialize the drivers.    */
        /***************************************************/
        xTaskCreate(MainTaskInit, (const portCHAR *)"MainInit", MAINTASKSTACKSIZE, NULL,
                           tskIDLE_PRIORITY + PRIORITY_MAIN_TASK, NULL);
#if 1
        /***************************************************/
        /* Create SWTask that check the button status.     */
        /***************************************************/
        xTaskCreate(SW_1_Task, (const portCHAR *)"SW1", SWTASKSTACKSIZE, NULL,
                                       tskIDLE_PRIORITY + PRIORITY_SW_TASK, NULL);
#endif
        /***************************************************/
        /* Create CANTask that check the button status.     */
        /***************************************************/

        xTaskCreate(CAN0_TASK, (const portCHAR *)"CAN_T", CANSTACKSIZE, NULL,
                                           tskIDLE_PRIORITY + PRIORITY_CAN_TASK, NULL);

        /******************************************************************************/
        /* Start the scheduler.  This should not return.                              */
        /******************************************************************************/
        vTaskStartScheduler();

        /**********************************************************************************/
        /* In case the scheduler returns for some reason, print an error and loop forever.*/
        /**********************************************************************************/
        while(1)
        {
        }


}
