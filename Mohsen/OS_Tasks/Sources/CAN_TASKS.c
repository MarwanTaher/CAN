
/******************************************** Includes ********************************************************/
#include "CAN_TASKS.h"

volatile uint8_t Switch_State = 0 ;
volatile uint8_t Action_Switch_State ;

/******************************************* Tasks Definitions ************************************************/
void init_Task(){
    CAN_APP_sys_init();
    CAN_APP_init_fun();


#ifdef NODE1
    CAN_APP_config_TX_msg(THIS_NODE_ID);
    CAN_APP_config_RX_msg(RECEIVE_ALL_MESSAGES);
#endif
#ifdef NODE2
    CAN_APP_config_TX_msg(THIS_NODE_ID);
    CAN_APP_config_RX_msg(RECEIVE_ALL_MESSAGES);
#endif
#ifdef NODE3
    CAN_APP_config_TX_msg(THIS_NODE_ID);
    CAN_APP_config_RX_msg(RECEIVE_ALL_MESSAGES);
#endif


    vTaskSuspend(NULL);
}


void CAN_Tx_Task(){
    while(1){
        #ifndef NODE1
            if(can_messages_rx_arr[STARTUP_NODE_INDEX] == STARTUP_NODE_VAL ){
                can_messages_tx_arr[STARTUP_NODE_INDEX] = STARTUP_NODE_VAL ;
                CAN_APP_send_the_messages_according_to_state();
            }
        #endif
        #ifdef NODE1
            CAN_APP_send_the_messages_according_to_state();
        #endif
            vTaskDelay(1000/portTICK_RATE_MS);

    }
}

void CAN_Rx_Task(){
    while(1){
        CAN_APP_receive_the_messages_according_to_state();
        vTaskDelay(400/portTICK_RATE_MS);

    }
}


void CAN_Led_Task()
{
    uint8_t LED_Periodicity_ctr = LED_INIT_STATE ;

    while(1){
        uxBits = xEventGroupWaitBits(led_event_gp, LED_BIT_EVENT_FLAG,pdTRUE,pdFALSE,4);
        if((uxBits & (LED_BIT_EVENT_FLAG) )){
            LED_Periodicity_ctr++ ;
            if(LED_Periodicity_ctr == NODE_LED_ON){
                LED_write(THIS_NODE_LED_PORT,THIS_NODE_LED_PIN,THIS_NODE_LED_PIN );
            }else if(LED_Periodicity_ctr == NODE_LED_OFF){
                LED_write(THIS_NODE_LED_PORT,THIS_NODE_LED_PIN,LOW);
                LED_Periodicity_ctr = LED_INIT_STATE ;
            }
        }
        vTaskDelay(1000/portTICK_RATE_MS);
    }
}

void CAN_Push_Button_Task(){

    while(1){
        if((uxBits & (LED_BIT_EVENT_FLAG) ) == ( LED_BIT_EVENT_FLAG )){
            if(!Push_Button_Read(PUSH_BUTTON1_PIN_NUM)){

                    Action_Switch_State = 1 ;

        }else{
                    Action_Switch_State = 0 ;
            }
        }
        vTaskDelay(50/portTICK_RATE_MS);
    }
}
