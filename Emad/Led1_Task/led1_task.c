/*
 * led1_task.c
 *
 *  Created on: Mar 13, 2019
 *      Author: AVE-LAP-44
 */

#include "../STD/Std_Types.h"
#include "../Commen/numbers.h"
#include "../LED/LED.h"
#include "FreeRTOS.h"
#include "task.h"
#include "led1_task.h"


static uint8 Led1_state=NUM_ZERO;
extern uint8 system_on;

void led1_task( void *pvParameters )
{


    for( ;; )
    {
     if(Led_ready&&(system_on))
     {
        if(Led1_state)
        {
            Led_on(LED1);
            Led1_state=NUM_ZERO;
        }
        else
        {
            Led_off(LED1);
            Led1_state=NUM_1;
        }

        vTaskDelay( 200 / portTICK_RATE_MS );
      }
     }
}
