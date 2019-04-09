
/*
 * File name :- project_tasks.h
 * it contain all tasks headers
 * date :- 19/3/2019
 * at 12: 11 PM
 */

/******************************************************************************************************
 *                               guarding the file
 **************************************************************************************************** */
#ifndef project_tasks_H_
#define project_tasks_H_

/*****************************************************************************************************
 * includes section
 ****************************************************************************************************/
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

#include "include/FreeRTOS.h"
#include "include/task.h"
#include "include/queue.h"
#include "include/semphr.h"



  QueueHandle_t xQueue;
/******************************************************************************************************
 * Function name :- INIT_task
 * Function job :- initiate all modules
 * Function inputs :- N/A
 * Function outputs :- N/A
 ********************************************************************************************************/
void INIT_task(void *p);

/******************************************************************************************************
 * Function name :- BUT1_task
 * Function job :-
 * Function inputs :- N/A
 * Function outputs :- N/A
 ********************************************************************************************************/
void BUT1_task(void *p);

/******************************************************************************************************
 * Function name :- BUT2_task
 * Function job :-
 * Function inputs :- N/A
 * Function outputs :- N/A
 ********************************************************************************************************/
void BUT2_task(void *p);

/******************************************************************************************************
 * Function name :- LCD_task
 * Function job :-
 * Function inputs :- N/A
 * Function outputs :- N/A
 ********************************************************************************************************/
void LCD_task(void *p);














#endif     /* end of header file */
