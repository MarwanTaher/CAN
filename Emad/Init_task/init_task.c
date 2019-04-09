/*
 * init_task.c
 *
 *  Created on: Mar 13, 2019
 *      Author: AVE-LAP-44
 */
#include "project_switch.h"
#include "../STD/Std_Types.h"
#include <stdbool.h>
#include <stdint.h>
#include "../Commen/numbers.h"
#include "../LED/LED.h"

#include "FreeRTOS.h"
#include "task.h"
#include "init_task.h"
#include "../Can/can.h"
#include "../Button/Button.h"
#include "driverlib/can.h"
#include "inc/hw_memmap.h"
#include "driverlib/can.h"
#include "../LCD/lcd.h"
#if MASTER
tCANMsgObject tocken_mailbox;
tCANMsgObject ecu_on_flag_mailbox;
tCANMsgObject master_receive;



uint32  tocken=STD_HIGH;
uint8 *tocken_ptr=(uint8 *)&tocken;


uint32  ecu_on_flag ;
uint8 *ecu_on_flag_ptr=(uint8 *)&ecu_on_flag;


uint32  master_receive_buffer;
uint8 *master_receive_buffer_ptr=(uint8 *)&master_receive_buffer;



uint8 init_flag =STD_LOW;

void init_task( void *pvParameters )
{

    for( ;; )
    {

            Led_init();
            Button_init();
            Can_init(CAN0);



            tocken_mailbox.ui32MsgID = 2;
            tocken_mailbox.ui32MsgIDMask = 0;
            tocken_mailbox.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
            tocken_mailbox.ui32MsgLen = 1;
            tocken_mailbox.pui8MsgData = tocken_ptr;

            ecu_on_flag_mailbox.ui32MsgID = 10;
            ecu_on_flag_mailbox.ui32MsgIDMask = 0;
            ecu_on_flag_mailbox.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
            ecu_on_flag_mailbox.ui32MsgLen = 1;
            ecu_on_flag_mailbox.pui8MsgData = ecu_on_flag_ptr;

            master_receive.ui32MsgID = 0;
            master_receive.ui32MsgIDMask =0;
            master_receive.ui32Flags = (MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER |
                                                   MSG_OBJ_EXTENDED_ID);
            master_receive.ui32MsgLen = 1;
            master_receive.pui8MsgData = master_receive_buffer_ptr;
            CANMessageSet(CAN0_BASE, 2, &master_receive, MSG_OBJ_TYPE_RX);
            LCD_init();
            LCD_smile_init();
            LCD_displayString("PRESS SW1 ",NUM_11);
            LCD_smile_display();
            LCD_smile_display();
            init_flag=STD_HIGH;
            vTaskSuspend(NULL);
    }
}
#endif

#if SLAVE

uint8 init_flag =STD_LOW;
extern void mailbox_init(void);

void init_task( void *pvParameters )
{

    for( ;; )
    {
            /* Initialize the led */
            Led_init();

            /* Initialize the CAN0 channel */
            Can_init(CAN0);

            /* Initialize the button */
            Button_init();

            /* Initialize the can mail box config.  */
            mailbox_init();

            /* Initialize the LCD */
            LCD_init();

            /* Set the init. flag */
            init_flag=STD_HIGH;

            /* Suspend the task */
             vTaskSuspend(NULL);
    }
}
#endif

