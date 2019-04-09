/*
 * switchs_tasks.h
 *
 *  Created on: Mar 18, 2019
 *      Author: AVE-LAP-016
 */

#ifndef SWITCHS_TASKS_H_
#define SWITCHS_TASKS_H_

#define BUTTONS_GPIO_PERIPH     SYSCTL_PERIPH_GPIOF
#define BUTTONS_GPIO_BASE       GPIO_PORTF_BASE

#define PRESSED     1
#define NOT_PRESSED 0

//*****************************************************************************
//
// Useful macros for detecting button events.
//
//*****************************************************************************
#define BUTTON_PRESSED(button, buttons, changed)                              \
        (((button) & (changed)) && ((button) & (buttons)))

#define BUTTON_RELEASED(button, buttons, changed)                             \
        (((button) & (changed)) && !((button) & (buttons)))

extern volatile uint8_t button1_status ;
extern volatile uint8_t button2_status ;

void Switch_Init_Task(void *pvParameters);
extern void SwitchTask(void *pvParameters);




#endif /* SWITCHS_TASKS_H_ */
