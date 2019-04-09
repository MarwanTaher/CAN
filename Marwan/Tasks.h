/*
 * Tasks.h
 *
 *  Created on: Mar 18, 2019
 *      Author: AVE-LAP-057
 */

#ifndef TASKS_H_
#define TASKS_H_

#include "FreeRTOS/Includes/FreeRTOS.h"
#include "FreeRTOS/Includes/event_groups.h"
#include "FreeRTOS/Includes/queue.h"
/*****************************************************************************/
/* Prototypes for the tasks.                                                 */
/*****************************************************************************/
extern void MainTaskInit(void *pvParameters);
extern void SW_1_Task(void *pvParameters);
extern void CAN0_TASK(void *pvParameters);
void Nodes_CountTASK(void *pvParameters);



#endif /* TASKS_H_ */
