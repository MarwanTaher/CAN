/*
 * Button0.c
 *
 *  Created on: Mar 18, 2019
 *      Author: AVE-LAP-44
 */
#include "../STD/Std_Types.h"
#include "../Commen/numbers.h"
#include "../Button/Button.h"
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#include "Button1_task.h"

#define BUTTON1 NUM_1


extern uint8 init_flag;
uint8 system_on=STD_LOW;
uint8 button1_pressed=NUM_ZERO;
static uint8 last_button1_state=NUM_ZERO;
static uint8 button1_count=NUM_ZERO;



void button1_task( void *pvParameters )
{

    uint8 button_state;
    for( ;; )
       {
        /* If the init. task completed */
                if(init_flag)
                {
                    /* Get the Key */
                    button_state=get_key(BUTTON1);

                    /* Check if the button state = last state */
                    if(button_state==last_button1_state)
                    {
                        /* Increment the counter */
                        button1_count++;

                    }
                    else
                    {

                        last_button1_state=button_state;
                        /* clear the counter */
                        button1_count =NUM_ZERO;
                    }
                    /* If counter reach threshold >> update the button value */
                    if(button1_count==NUM_5)
                    {
                        /*As button is pulled high
                         * button1_pressed =! state */
                        button1_pressed = !(button_state);
                        /* Clear the counter */
                        button1_count=NUM_ZERO;
                        /* if the first time set system on */
                        if(button1_pressed)
                        {
                            system_on=STD_HIGH  ;
                        }
                    }
                }

         vTaskDelay( 5 / portTICK_RATE_MS );

        }




}


