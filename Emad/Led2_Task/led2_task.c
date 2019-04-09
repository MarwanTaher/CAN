/*
 * led2_task.c
 *
 *  Created on: Mar 13, 2019
 *      Author: AVE-LAP-44
 */

#include "../STD/Std_Types.h"
#include "../Commen/numbers.h"
#include "FreeRTOS.h"
#include "task.h"
#include "../LED/LED.h"
#include "led2_task.h"

static uint8 Led2_state=NUM_ZERO;
extern uint8 system_on;

void led2_task( void *pvParameters )
{


    for( ;; )
    {
      if(Led_ready&&(system_on))
      {
        if(Led2_state)
        {
            Led_on(LED2);
            Led2_state=NUM_ZERO;
        }
        else
        {
            Led_off(LED2);
            Led2_state=NUM_1;
        }

        vTaskDelay( 1000 / portTICK_RATE_MS );
      }
    }
}
