/*
 * FSM.c
 *
 *  Created on: Apr 4, 2019
 *      Author: Ahmed Abdlrehem
 */
#include "Types.h"
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
#include "driverlib/sysctl.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "LCD.h"
#include "driverlib/can.h"
#include "can.h"
#include "BUTTON.h"
#include "FSM.h"
/*********************************************************************************/
#define PRESSED 1
#define NOT_PRESSED 0
#define START_UP_STATE 0
#define NORMAL_STATE 1
#define ONE 1
#define THREE 3
#define TWO 2
#define TEN 10
#define ZERO 0
volatile uint8_t Reverse_Sending = 0;
volatile uint8_t Reverse_Counter = 0;
volatile uint8_t count = 0;
volatile uint8_t guard_flag = 0;
/*******************************************************************************/
/*******************************************************************************/
#define NODE N_one
#define INITIAl_STATE START_UP_STATE
/******************************************************************************/
uint8_t Node_arr[NUM_OF_NODES] = { 2, 3, 4, 1 };
uint8_t token_flag = 0;
uint8_t volatile Led_flag = 0;
uint8_t volatile send_flag = 0;
uint8_t volatile counter = 0;
/*****************************************************************************/
/*********************Button_Task**************************
 * *
 * FUNCTION NAME: Button_Task
 * *
 * ARGUMENTS:
 *               NOTHING
 *
 * DESCRIPTION :This Task Checks the pressed button and apply the concept of debouncing check
 * *
 * RETURNS: NOTHING
 * *
 *********************************************************/
void Button_Task(void)
{
    while (1)
    {
        if (Get_BUTTON() == PRESSED)
        {
            count++;
        }
        if (Get_BUTTON() == NOT_PRESSED)
        {
            count = ZERO;
        }

        if (count == TEN)
        {
            Reverse_Sending = 1;
            count = 0;
        }
        vTaskDelay(5);

    }
}
/*********************Led_Task**************************
 * *
 * FUNCTION NAME: Led_Task
 * *
 * ARGUMENTS:
 *               NOTHING
 *
 * DESCRIPTION :This Task Checks the Led_Flag to turn the led for 1 second and
 * * set the Token flag to send the Token to the next node
 * RETURNS: NOTHING
 * *
 *********************************************************/
void Led_Task()
{

    while (1)
    {
        /*if the flag is set to 1 then make the led turn on*/
        if (Led_flag == 1)
        {
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
            counter++;
        }
        if (counter == 2)
        {
            /*after one second make the led turn off*/
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
            counter = 0;
            /*Set the Token flag*/
            token_flag = 1;

        }

        vTaskDelay(1000);
    }

}
/********************************************************
 * *
 * FUNCTION NAME: FSM_TASK
 * *
 * ARGUMENTS:
 *               NOTHING
 *
 * DESCRIPTION :this task is the main task in this task we choose the initial state for
 * * each node and the node we want to work on and we loop on our nodes
 *   and  check if we received a new message in mailbox we check the flag
 *   and if we received the task will check id of this node to see if the message
 *   is for it or not and after that we check the data if the data is zero then the
 *   normal direction for each node will be applied and if the data is one
 *   then that means that the direction is switched and it should continue sending
 *   in the reverse direction
 * RETURNS: * NOTHING
 * *
 *********************************************************/
void FSM_Task()
{
    uint8_t i = 0;
    static Node_Id Node = NODE;
    static uint8_t Data_Reverse = 0;
    static strData_Id Received_object;
    static uint8_t state = INITIAl_STATE;
    while (1)
    {
        for (i = 0; i < NUM_OF_NODES; i++)
        {
            if (Node == i)
            {
                if (state == START_UP_STATE)
                {
                    Led_flag = 1;
                    if (token_flag == 1)
                    {

                        if (1 == Reverse_Sending)
                        {
                            Led_flag = 0;
                            Data_Reverse = 1;
                            Can_Transmit(Data_Reverse, Node_arr[i + 1]);
                            state = NORMAL_STATE;
                            Reverse_Sending = 0;
                        }
                        else
                        {
                            Can_Transmit(ZERO, Node_arr[i]);
                            state = NORMAL_STATE;
                        }
                    }
                }
                else if (state == NORMAL_STATE)
                {

                    if (Rx_flag == 1)
                    {

                        Received_object = Can_Receive();
                        if (Received_object.ID == (i + 1))
                        {
                            Led_flag = 1;
                            if (token_flag == 1)
                            {
                                Led_flag = 0;
                                if (*(Received_object.pui8MsgData) == 0)
                                {
                                    if (ONE == Reverse_Sending)
                                    {
                                        if (i == (NUM_OF_NODES - 1))
                                        {
                                            Data_Reverse = 1;
                                            Can_Transmit(Data_Reverse,
                                                         Node_arr[0]);
                                            Reverse_Sending = 0;
                                            Rx_flag = 0;
                                            token_flag = 0;
                                        }
                                        else
                                        {
                                            Data_Reverse = 1;
                                            Can_Transmit(Data_Reverse,
                                                         Node_arr[i + 1]);
                                            Reverse_Sending = 0;
                                            Rx_flag = 0;
                                            token_flag = 0;
                                        }
                                    }
                                    else
                                    {
                                        Rx_flag = 0;
                                        Can_Transmit(0, Node_arr[i]);
                                        token_flag = 0;
                                    }

                                }
                                else if (*(Received_object.pui8MsgData) == 1)
                                {
                                    if (1 == Reverse_Sending)
                                    {
                                        Can_Transmit(ZERO, Node_arr[i]);
                                        Rx_flag = ZERO;
                                        Reverse_Sending = ZERO;
                                        token_flag = 0;
                                    }
                                    else
                                    {
                                        if (i == (NUM_OF_NODES - 1))
                                        {
                                            Data_Reverse = ONE;
                                            Can_Transmit(Data_Reverse,
                                                         Node_arr[0]);
                                            Reverse_Sending = ZERO;
                                            Rx_flag = ZERO;
                                            token_flag = 1;
                                        }
                                        else
                                        {
                                            Can_Transmit(1, Node_arr[i + ONE]);
                                            Rx_flag = 0;
                                            token_flag = 0;
                                        }
                                    }

                                }
                            }
                        }

                    }

                }
            }
        }
        vTaskDelay(25);
    }
}
