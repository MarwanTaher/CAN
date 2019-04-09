



/*****************************************************************************************************
 *                                          includes section
 ****************************************************************************************************/
#include "can_task.h"
#include "Switch.h"

extern volatile  uint8_t tx_flag ; /* flag to indicate that can has sent data to bus */
 extern volatile  uint8_t rx_flag ; /* flag to indicate that can has received  data to bus */

static uint8_t MAX_NODES = NUM_3;

volatile uint8_t TOKEN_FLAG = NUM_0; /* flag to indicate node is on token flag or not */
volatile uint8_t REVERSED_FLAG = NUM_0;  /* flag to indicate it rreversed mode or not */
static uint8_t normal_mode=NUM_0,reverse_mode=NUM_0;    /* variable to detect mode */





/*******************************************************************************************************
 * Function name :- INIT_task
 * Function job :- initiate all required modules
 * Function inputs :- N/A
 * Function outputs :- N/A
 *********************************************************************************************************/
void INIT_task(void *p)
{
    while(NUM_1)
    {
        /* initialize can module  */
        CAN_init(CAN0);
          LED_init();   /* initialize leds on board  */
          Switch_Init();   /* initialize switches  */
          /* suspend this task  to not come again */
          vTaskSuspend(NULL);
    }
}

/*******************************************************************************************************
 * Function name :- recieve_task
 * Function job :- tasks responsible for recieving data
 * Function inputs :- N/A
 * Function outputs :- N/A
 ********************************************************************************************************/
void transmit_mode(void *p)
{
  static uint8_t led_count = NUM_0,transmitted_value=NUM_0,sw_count = 0;
#if(MY_ID == 1)
  static uint8_t ON_FLAG = 1;
#endif

    while(NUM_1)
    {
        /* if this node is first one then check on no state*/
#if(MY_ID == 1)
        if( TOKEN_FLAG == NUM_1 || ON_FLAG == NUM_1 )
#else
            /* if any other mode wait for token role */
            if(TOKEN_FLAG == NUM_1 )
#endif
        {
                /* if node hold token */
            LED_on(NUM_1);
            /* increase led counting */
            led_count ++;
            /* token flag is on to disable any recieving */
            TOKEN_FLAG = NUM_1;
            /* check sw in pressed or not */
             if(SW_2_Status()){
                 /* set sw variable to one */
                 sw_count = NUM_1;
             }


        }

        /* time is 1 second and its time for the node to lose token */
        if(led_count == NUM_20 && TOKEN_FLAG == NUM_1)
        {
       /* check if sw is pressed or reverse is on */
            if(sw_count == NUM_1 || REVERSED_FLAG == NUM_1)
            {
                /* set reverse mode flag */
                reverse_mode = NUM_1;
                normal_mode = NUM_0;  /* clear normal flag */
                /* in case that reverse mode is on and switch is pressed */
                if( (REVERSED_FLAG == NUM_1 && sw_count == NUM_1))
                {
                    /* then return to normal mode */
                                   normal_mode = NUM_1;
                                   reverse_mode = NUM_0;
                                   REVERSED_FLAG = NUM_0;
                }
            }

            else{
                /* if switch is not pressed and reverse flag is cleared */
                normal_mode = NUM_1;
                 reverse_mode = NUM_0;

            }

              /* state of reverse mode */
            if(reverse_mode == NUM_1){
                /* transmit value with this manner */
                transmitted_value = (MY_ID - NUM_1) | (NUM_1<<NUM_7) ;
                /* in case that node 1 */
                if(MY_ID == NUM_1)
                {
                    /* send to node 3 */
                    transmitted_value = (NUM_3)|(NUM_1<<NUM_7);
                }

            }
            else if(normal_mode == NUM_1) {
                /* in normal mode send to the next node */
                transmitted_value = (MY_ID + NUM_1) & (~(NUM_1<<NUM_7)) ;
                /* if this node is the last node send to first node again */
                             if(MY_ID == MAX_NODES)
                             {
                                 transmitted_value = (NUM_1) & (~(NUM_1<<NUM_7));
                             }
                             REVERSED_FLAG = NUM_0;
            }


                /* after determining transmitted data  send it by can module */

            CAN_Transmit(transmitted_value);
          /* clear token flag indicate that node has lost token */
          TOKEN_FLAG = NUM_0;
          /* make switch flag is zero again */
          sw_count = NUM_0 ;
          /* if this is node one make on state off to translate it to normal mode again */
#if(MY_ID == NUM_1)
          ON_FLAG = NUM_0;
#endif
            led_count = NUM_0;
            LED_off(NUM_1);


        }


       vTaskDelay(TRANSMIT_MODE_PERIODICITY);
    }
}




/*******************************************************************************************************
 * Function name :- trasmit_task
 * Function job :- tasks responsible for transmitting data
 * Function inputs :- N/A
 * Function outputs :- N/A
 ********************************************************************************************************/
void recieve_mode(void *p)
{
   static uint8_t * received_value = NULL;  /* pointer to recieve can massege */

    while(NUM_1){

  /* check if any message exist and its not a token node */
        if(rx_flag == NUM_1 && TOKEN_FLAG == NUM_0 ){
            /* recieve can message */
       received_value = CAN_Recieve();
       /* if recieved message matching with my id */
       if( ((*received_value) & 0x0F) == MY_ID)
        {
           /* set token flag */
           TOKEN_FLAG = NUM_1;
          /* if recieved value has one in the most signifiecnt bit */
           if(((*received_value & (NUM_1<<NUM_7))>>NUM_7 == NUM_1))
           {
               /* data recieved is reversed */
               REVERSED_FLAG = NUM_1;


           }
           else {

            REVERSED_FLAG = NUM_0;
        }

        }
       /* clear recieveing flag */
        rx_flag = NUM_0;
        }

   vTaskDelay(RECIEVE_MODE_PERIODICITY);
    }
}
