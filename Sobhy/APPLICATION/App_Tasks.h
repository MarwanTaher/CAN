/*
 * App_Tasks.h
 *
 *  Created on: Mar 20, 2019
 *      Author: AVE-LAP-032
 */

#ifndef APP_TASKS_H_
#define APP_TASKS_H_


/*define the bits to check on */
#define BIT_0   ( ONE << ZERO )
#define BIT_4   ( ONE << FOUR )


/* Declare a variable to hold the created event group. */
EventGroupHandle_t xCreatedEventGroup;
#define HEX_ONE 0x01
#define ONE_HUNDRED 100

#define FOUR  4
#define THREE 3

#define STARTUP 0
#define NORMAL  1

#define YES 1
#define NO 0




void Init_Task(void );
void BUTTON_TASK(void);
void LED_TASK(void);
void LCD_TASK(void);
void Init_LCD_Task (void);
void CAN_RX_TASK(void);
void CAN_TX_TASK(void);
void CAN_NODE0_TASK(void);


/* Declare a variable to hold the created event group. */
EventGroupHandle_t xCreatedEventGroup;


QueueHandle_t xQueue;

/* Define the data type that will be queued. */
typedef struct A_Message
{
uint8_t Button_MessageID; /*Holds the Id of the button pressed */
uint16_t Button_Data;     /*Holds number of pressed times of the button */
} AMessage;


/* Define the queue parameters. */
#define QUEUE_LENGTH 2
#define QUEUE_ITEM_SIZE sizeof( AMessage )


#endif /* APP_TASKS_H_ */
