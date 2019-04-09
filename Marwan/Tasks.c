/*
 * Tasks.c
 *
 *  Created on: Mar 18, 2019
 *      Author: AVE-LAP-057
 */

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/rom.h"
#include "utils/uartstdio.h"
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "tasks.h"
#include "driverlib/can.h"
#include "FreeRTOS/Includes/task.h"
#include "FreeRTOS/Includes/semphr.h"
#include "Drivers/Switch/inc/Switch.h"
#include "Drivers/LEDs/inc/LEDs.h"
#include "tasks.h"
#include "Drivers/LCD/inc/LCD.h"
#include "Drivers/KeyPad/inc/Keypad.h"
#include "Drivers/UART/inc/uart.h"
#include "Drivers/SPI/inc/spi.h"
#include "Drivers/CAN/CAN.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

/******************************************************************************/
/* Switch flag to check if the button is pressed or not.                      */
/******************************************************************************/
volatile uint8_t WS_Flag = 0;

/********************************************************************************/
/* Default LED toggle delay value. LED toggling frequency is twice this number. */
/****************************************************************************** */
#define LED_TOGGLE_DELAY        10

/********************************************************************************/
/* Default LED toggle delay value. LED toggling frequency is twice this number. */
/****************************************************************************** */
#define SW_DELAY        10
#define SW_DEBOUN       1000

#define T_DELAY_1000                      1000
#define T_DELAY_10                        10
#define T_DELAY_100                       100
#define T_DELAY_50                        50

/******************************************************************************/
/* The Nodes definations.                                     */
/******************************************************************************/

#define NODE_1          1
#define NODE_2          0
#define NODE_3          0
extern uint8_t Token;
extern uint8_t STARTUP;
uint8_t Nodes_counter = 0;
uint8_t Reversed = 0;
uint8_t State_NODE_2 = 0;
uint8_t State_NODE_3 = 0;
uint8_t Next = 0;

/******************************************************************************/
/* This task Init the leds and Switches                                       */
/******************************************************************************/
void MainTaskInit(void *pvParameters)
{
    while (1)
    {

        LEDs_Init();
        Switch_Init();
        InitConsole();
        CAN_Init();
        StartUpState();

        vTaskSuspend( NULL);
    }
}

/******************************************************************************/
/* This task Check if the button is pressed or not                            */
/******************************************************************************/
void SW_1_Task(void *pvParameters)
{
    button_Flag = 0;
    /* delay till all modules intialized */
    while (1)
    {
        if (SW_1_Status())
        {
            button_Flag = 1;

        }
        else
        {
            button_Flag = 0;

        }
        vTaskDelay(10);
    }
}

/******************************************************************************/
/* This task Send & Receive through CAN0                                           */
/******************************************************************************/
void CAN0_TASK(void *pvParameters)
{
    /******************************************************************************/
    /* NODE 1 TASK                                                               */
    /******************************************************************************/
#if NODE_1

    while (1)
    { /* Set Message object to receive  */
        CANMessageSet(CAN0_BASE, NUM_1, &sCANMessageRX, MSG_OBJ_TYPE_RX);
        pui8MsgDataout = (uint8_t *) &ui32MsgDataout; /* Assign Value in object */
        /* Startup State begin */
        if (STARTUP == NUM_1)
        {
            *pui8MsgDataout = NUM_1;
            //pui8MsgDataout = (uint8_t *) &ui32MsgDataout;
            sCANMessageTX.ui32MsgID = NUM_4; /* Message ID to next node  */
            CANMessageSet(CAN0_BASE, NUM_2, &sCANMessageTX, MSG_OBJ_TYPE_TX); /* Set Message object to receive     */
            UARTprintf("Sending msg: %d", pui8MsgDataout[NUM_0]); /* Print the value in uart    */

            Token = NUM_1;
            STARTUP = NUM_0; /* Startup State end   */

        }

        else
        {
            /* Receive from Message object      */
            CANMessageGet(CAN0_BASE, NUM_1, &sCANMessageRX, NUM_0);
            UARTprintf("data: %d", pui8MsgDatain[NUM_0]);

            /* check for interrupt flag means a message received    */
            if (g_bRXFlag1)
            {
                /* Check for the ID      */
                if (sCANMessageRX.ui32MsgID == NUM_2)
                {
                    Token = NUM_1;
                }
                if (Token == NUM_1)
                {

                    /* GREEN LED ON   */
                    GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED, GREEN_LED);
                    /* DELAY 1 SEC     */
                    vTaskDelay(T_DELAY_1000);

                    /* CLEAR Interrupt FLAGS     */
                    g_bRXFlag1 = NUM_0;
                    g_bRXFlag2 = NUM_0;
                    g_bRXFlag3 = NUM_0;
                    /* Check for button     */
                    if (pui8MsgDatain[NUM_0] == NUM_0)
                    {
                        if(button_Flag)
                        {
                            *pui8MsgDataout = NUM_1;
                            sCANMessageTX.ui32MsgID = NUM_6;

                            /* SEND TO NEXT NODE     */
                            CANMessageSet(CAN0_BASE, NUM_3, &sCANMessageTX,
                                    MSG_OBJ_TYPE_TX);

                        }
                        else
                        {
                            *pui8MsgDataout = NUM_1;
                            sCANMessageTX.ui32MsgID = NUM_4;
                            /* SEND TO NEXT NODE     */
                            CANMessageSet(CAN0_BASE, NUM_3, &sCANMessageTX,
                                    MSG_OBJ_TYPE_TX);

                        }

                    }
                    else if (pui8MsgDatain[NUM_0] == NUM_1)
                    {
                        if(button_Flag)
                                               {
                        *pui8MsgDataout = NUM_0;
                        sCANMessageTX.ui32MsgID = NUM_4;

                        /* SEND TO NEXT NODE     */
                        CANMessageSet(CAN0_BASE, NUM_3, &sCANMessageTX,
                                MSG_OBJ_TYPE_TX);

                    }
                    else
                    {
                        *pui8MsgDataout = NUM_1;
                        sCANMessageTX.ui32MsgID = NUM_6;
                        /* SEND TO NEXT NODE     */
                        CANMessageSet(CAN0_BASE, NUM_3, &sCANMessageTX,
                                MSG_OBJ_TYPE_TX);
                    }
                }
            }

            Token = NUM_0;
            /* TURN LEDS OFF     */
            GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED, NUM_0);

        }
    }
    vTaskDelay(T_DELAY_50);
}

}
#endif

#if NODE_2
    /******************************************************************************/
    /* NODE 2 TASK                                                               */
    /******************************************************************************/

    while(1)
    {
        CANMessageSet(CAN0_BASE, NUM_2, &sCANMessageRX, MSG_OBJ_TYPE_RX);
        pui8MsgDataout = (uint8_t *) &ui32MsgDataout;
        if (STARTUP == NUM_1)
        {
            *pui8MsgDataout = NUM_1;
            //pui8MsgDataout = (uint8_t *) &ui32MsgDataout;
            sCANMessageTX.ui32MsgID = NUM_6; /* Message ID to next node  */
            CANMessageSet(CAN0_BASE, NUM_3, &sCANMessageTX, MSG_OBJ_TYPE_TX); /* Set Message object to receive     */
            UARTprintf("Sending msg: %d", pui8MsgDataout[NUM_0]); /* Print the value in uart    */

            Token = NUM_1;
            STARTUP = NUM_0; /* Startup State end   */

        }

        /* Receive from Message object      */
        CANMessageGet(CAN0_BASE, NUM_2, &sCANMessageRX, NUM_0);
        UARTprintf("data: %d", pui8MsgDatain[NUM_0]);
        button_Flag=0;
        /* check for interrupt flag means a message received    */
        if( g_bRXFlag2 )
        {

            if(sCANMessageRX.ui32MsgID==NUM_4)
            {
                Token=NUM_1;
            }
            if(Token == NUM_1)
            {
                /* GREEN LED ON   */
                GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED, GREEN_LED);

                vTaskDelay(T_DELAY_1000);
                /* CLEAR Interrupt FLAGS     */
                g_bRXFlag1 = NUM_0;
                g_bRXFlag2 = NUM_0;
                g_bRXFlag3 = NUM_0;
                /* Check for button     */
                if(button_Flag)
                {

                    if(pui8MsgDatain[NUM_0] == NUM_0)
                    {
                        *pui8MsgDataout = NUM_1;
                        sCANMessageTX.ui32MsgID = NUM_2;

                        /* SEND TO NEXT NODE     */
                        CANMessageSet(CAN0_BASE, NUM_3, &sCANMessageTX, MSG_OBJ_TYPE_TX);


                    }
                    else if(pui8MsgDatain[NUM_0] == NUM_1)
                    {
                        *pui8MsgDataout = NUM_0;
                        sCANMessageTX.ui32MsgID = NUM_6;

                        /* SEND TO NEXT NODE     */
                        CANMessageSet(CAN0_BASE, NUM_3, &sCANMessageTX, MSG_OBJ_TYPE_TX);


                    }

                }
                else
                {
                    if(pui8MsgDatain[NUM_0] == NUM_0)
                    {
                        *pui8MsgDataout = NUM_0;
                        sCANMessageTX.ui32MsgID = NUM_6;

                        /* SEND TO NEXT NODE     */
                        CANMessageSet(CAN0_BASE, NUM_3, &sCANMessageTX, MSG_OBJ_TYPE_TX);

                    }
                    else if(pui8MsgDatain[NUM_0] == NUM_1)
                    {
                        *pui8MsgDataout = NUM_1;
                        sCANMessageTX.ui32MsgID = NUM_2;
                        /* SEND TO NEXT NODE     */

                        CANMessageSet(CAN0_BASE, NUM_3, &sCANMessageTX, MSG_OBJ_TYPE_TX);


                    }
                }

            }
            Token=NUM_0;
            /* TURN LEDS OFF     */
            GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED, NUM_0);

        }

        vTaskDelay(T_DELAY_50);
    }
}

#endif
#if NODE_3
    /******************************************************************************/
    /* NODE 3 TASK                                                               */
    /******************************************************************************/

    while (1)
    {
        CANMessageSet(CAN0_BASE, NUM_3, &sCANMessageRX, MSG_OBJ_TYPE_RX);
        pui8MsgDataout = (uint8_t *) &ui32MsgDataout;
        CANMessageGet(CAN0_BASE, NUM_3, &sCANMessageRX, NUM_0);
        UARTprintf("data: %d", pui8MsgDatain[NUM_0]);

        if (g_bRXFlag3)
        {
            if (sCANMessageRX.ui32MsgID == NUM_6)
            {
                Token = NUM_1;
            }
            if (Token == NUM_1)
            {

                GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED, GREEN_LED);

                vTaskDelay(T_DELAY_1000);

                g_bRXFlag1 = NUM_0;
                g_bRXFlag2 = NUM_0;
                g_bRXFlag3 = NUM_0;

                if (button_Flag)
                {

                    if (pui8MsgDatain[NUM_0] == NUM_0)
                    {
                        *pui8MsgDataout = NUM_1;
                        sCANMessageTX.ui32MsgID = NUM_6;
                        sCANMessageTX.pui8MsgData = pui8MsgDataout;

                        CANMessageSet(CAN0_BASE, NUM_2, &sCANMessageTX,
                                      MSG_OBJ_TYPE_TX);

                        UARTprintf("Sending msg: %d", pui8MsgDataout[NUM_0]);

                    }
                    else if (pui8MsgDatain[NUM_0] == NUM_1)
                    {
                        *pui8MsgDataout = NUM_0;
                        sCANMessageTX.ui32MsgID = NUM_2;
                        sCANMessageTX.pui8MsgData = pui8MsgDataout;

                        CANMessageSet(CAN0_BASE, NUM_2, &sCANMessageTX,
                                      MSG_OBJ_TYPE_TX);

                        UARTprintf("Sending msg: %d", pui8MsgDataout[NUM_0]);

                    }

                }
                else
                {
                    if (pui8MsgDatain[NUM_0] == NUM_0)
                    {
                        *pui8MsgDataout = NUM_0;
                        sCANMessageTX.ui32MsgID = NUM_2;
                        sCANMessageTX.pui8MsgData = pui8MsgDataout;

                        CANMessageSet(CAN0_BASE, NUM_2, &sCANMessageTX,
                                      MSG_OBJ_TYPE_TX);

                        UARTprintf("Sending msg: %d", pui8MsgDataout[NUM_0]);

                    }
                    else if (pui8MsgDatain[NUM_0] == NUM_1)
                    {
                        *pui8MsgDataout = NUM_1;
                        sCANMessageTX.ui32MsgID = NUM_4;
                        sCANMessageTX.pui8MsgData = pui8MsgDataout;

                        CANMessageSet(CAN0_BASE, NUM_2, &sCANMessageTX,
                                      MSG_OBJ_TYPE_TX);

                        UARTprintf("Sending msg: %d", pui8MsgDataout[NUM_0]);

                    }
                }

            }
            Token = NUM_0;
            GPIOPinWrite(GPIO_PORTF_BASE, GREEN_LED, NUM_0);

        }
        vTaskDelay(T_DELAY_50);
    }

}

#endif
#if 0
void Nodes_CountTASK(void *pvParameters)
{
    pui8MsgDataout = (uint8_t *) &ui32MsgDataout;
    *pui8MsgDataout = 0;
    sCANMessageTX.ui32MsgID = 0;
    sCANMessageTX.pui8MsgData = pui8MsgDataout;
    CANMessageSet(CAN0_BASE, 1, &sCANMessageTX, MSG_OBJ_TYPE_TX);
    CANMessageSet(CAN0_BASE, 1, &sCANMessageRXG, MSG_OBJ_TYPE_RX);
    while (1)
    {
        CANMessageGet(CAN0_BASE, 1, &sCANMessageRXG, MSG_OBJ_TYPE_RX);
        if (pui8MsgDatain[0] == 1)
        {
            Nodes_counter++;
        }
    }

}
#endif
