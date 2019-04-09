#if 0
#include "BUZZER.h"
#include "LED.h"
#include "BTN.h"
#include "LCD.h"
#include "FreeRTOS.h"
#include "include/task.h"
#include "queue.h"
#include "My_Task.h"

QueueHandle_t    Quee;
/*uint8_t BTN2_FLAG = 0 ;led
uint8_t BTN1_FLAG = 0 ;lcd*/
volatile uint8_t BTN2_COUNTER =ZERO  ;
volatile uint8_t BTN1_COUNTER =ZERO ;
#define NINE 9

/* INIT tasks  */
/* Parameters : N/A */
/* I/p : N/A */
/* O/p : N/A */
/* Return : void  */
/* Function that initilize LED , BTN , LCD */
void vTaskCode( void * pvParameters )
    {

        for( ;; )
        {

            LEDTaskInit();
            Buzzer_Init();/*buzzer init */
            Btns_Init();/*init buttuns */
            LCD_INIT();/*init the LCD */
            vTaskSuspend(NULL);/*susspend for init tasks */
        }
    }



/* BTN2 tasks  */
/* Parameters : N/A */
/* I/p : N/A */
/* O/p : N/A */
/* Return : void  */
/* Function that get status of BTN2 */
void vTaskCode3( void * pvParameters )
    {
         static uint8_t state = ZERO; /* BTN2 state */
         uint8_t data_btn2 = ONE ;    /* this variable will be insert in quee when BTN2 is presssed */
         uint8_t BTN2_FLAG = ONE;
        for( ;; )
        {
           state = Btn2_Read();/*call buttun read function to get the state for BTN2 and store in STATE variable */

           if((state == BTN2_ON) && (BTN2_FLAG==ZERO))/* check if state == one and BTN2_FLAG ==0 TO CHECK DEBOUNCE */
           {
               xQueueSend(Quee,&data_btn2,10);
           }
           BTN2_FLAG = state ;
           vTaskDelay(30);

        }
    }



/* BTN1 tasks  */
/* Parameters : N/A */
/* I/p : N/A */
/* O/p : N/A */
/* Return : void  */
/* Function that get status of BTN1 */
void vTaskCode6( void * pvParameters )
    {
         static uint8_t state = ZERO;
         uint8_t BTN1_FLAG    = ZERO;
         uint8_t data_btn1    =TWO ;

        for( ;; )
        {
           state = Btn1_Read();
           if(state == BTN1_ON && BTN1_FLAG==ZERO)
           {
               xQueueSend(Quee,&data_btn1,10);

           }
           BTN1_FLAG = state ;

           vTaskDelay(30);

        }
    }






/* LCD tasks  */
/* Parameters : N/A */
/* I/p : N/A */
/* O/p : N/A */
/* Return : void  */
/* Function that display LCD  */
void vTaskCode5( void * pvParameters )
{
    uint8_t recive =ZERO;
    for( ;; )
    {
        xQueueReceive(Quee, &recive, 10);
       if(recive==ONE)
       {
           LCD_DISPLAY1(BTN1_COUNTER);
           BTN1_COUNTER++;
           vTaskDelay(5);
           if(BTN1_COUNTER>NINE)
            {
             BTN1_COUNTER=ZERO;
            }
           recive = ZERO ;
       }
       else if(recive==TWO)
       {
           LCD_DISPLAY2(BTN2_COUNTER);
           BTN2_COUNTER++;
           vTaskDelay(5);
           if(BTN2_COUNTER>9)
           {
            BTN2_COUNTER=ZERO;
           }
           recive = ZERO ;
       }

        vTaskDelay( 20 );
    }
}
#endif
