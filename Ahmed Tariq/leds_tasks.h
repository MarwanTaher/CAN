/*
 * leds_tasks.h
 *
 *  Created on: Mar 18, 2019
 *      Author: AVE-LAP-016
 */

#ifndef LEDS_TASKS_H_
#define LEDS_TASKS_H_

//*****************************************************************************
//
// The stack size for the LED toggle task.
//
//*****************************************************************************
#define LEDTASKSTACKSIZE        128         // Stack size in words

//*****************************************************************************
//
// The item size and queue size for the LED message queue.
//
//*****************************************************************************
#define LED_ITEM_SIZE           sizeof(uint8_t)
#define LED_QUEUE_SIZE          5

//*****************************************************************************
//
// Default LED toggle delay value. LED toggling frequency is twice this number.
//
//*****************************************************************************
#define LED_TOGGLE_DELAY        250
#define LED0_TOGGLE_DELAY       1000
#define LED1_TOGGLE_DELAY       2000
#define LED2_TOGGLE_DELAY       1000
#define LEFT_BUTTON             GPIO_PIN_4
#define RIGHT_BUTTON            GPIO_PIN_0


#define RED_GPIO_PIN            GPIO_PIN_1
#define BLUE_GPIO_PIN           GPIO_PIN_2
#define GREEN_GPIO_PIN          GPIO_PIN_3

//*****************************************************************************
void LEDs_tasks_init(void *pvParameters);
void LED_RED_task(void *pvParameters);
void LED1_task(void *pvParameters);
void LED2_task(void *pvParameters);

void LED_RED_Enable(void);
void LED_BLUE_Enable(void);
void LED_GREEN_Enable(void);
void LED_WHITE_Enable(void);

#endif /* LEDS_TASKS_H_ */
