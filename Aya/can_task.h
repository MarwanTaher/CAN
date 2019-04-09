


/*************************************************************************************************************
 *                                               guard file
 ****************************************************************************************************************/
#ifndef CAN_TASK_H_
#define  CAN_TASK_H_


/*****************************************************************************************************
 *                                          includes section
 ****************************************************************************************************/
#include "include/FreeRTOS.h"
#include "include/task.h"
#include "include/queue.h"
#include "include/semphr.h"
#include "include/event_groups.h"
#include "can.h"
#include "can_cfg.h"
#include "LED.h"

 EventGroupHandle_t xCreatedEventGroup_flags;

#define RECIEVE_MODE_PERIODICITY  50
#define  TRANSMIT_MODE_PERIODICITY  50



/*******************************************************************************************************************************************************
 *                                                               FUNCTION PROTOTYPES
 ******************************************************************************************************************************************************/

/*******************************************************************************************************
 * Function name :- INIT_task
 * Function job :- initiate all required modules
 * Function inputs :- N/A
 * Function outputs :- N/A
 *********************************************************************************************************/
void INIT_task(void *p);

/*******************************************************************************************************
 * Function name :- recieve_task
 * Function job :- tasks responsible for recieving data
 * Function inputs :- N/A
 * Function outputs :- N/A
 ********************************************************************************************************/
void recieve_mode(void *p);



/*******************************************************************************************************
 * Function name :- trasmit_task
 * Function job :- tasks responsible for transmitting data
 * Function inputs :- N/A
 * Function outputs :- N/A
 ********************************************************************************************************/
void transmit_mode(void *p);




#endif   /*  end of CAN_TASK_H_  */


