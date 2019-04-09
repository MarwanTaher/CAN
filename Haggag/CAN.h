#ifndef CAN_H_
#define CAN_H_
#include <stdint.h>
/*********************NORMAL CONFIGURATION *********************/
#define ID_TX_N             0           /*THE ADDRESS WILL BE TRANSMIT BY CAN ON MAILBOX 1 IN TRANSMIT NODE */
#define ID_RX_N             2            /*THE ADDRESS WILL BE RECEIVED BY MAILBOX 2 IN RECEIVE NODE */

#define DATA_N              1            /* DATA NORMAL*/
#define DATA_R              5            /* DATA REVERS */

/*********************REVERS CONFIGURATION *********************/
#define ID_TX_R             1          /*THE ADDRESS WILL BE TRANSMIT BY CAN ON MAILBOX 1 IN TRANSMIT NODE */
#define ID_RX_R             2`           /*THE ADDRESS WILL BE RECEIVED BY MAILBOX 2 IN RECEIVE NODE */


extern void CANIntHandler(void);
extern void vTaskCode_INIT_CAN_ZERO(void * pvParameters);/*INIT task */
extern void vTaskCode_NODE_ZERO_START(void * pvParameters);/*STARTUP NODE TASK BY NODE 0 */
extern void vTaskCode_NODE_RX(void * pvParameters);/*NODE RECEIVE TASK BY MAILBOX 2 */
extern void vTaskCode_NODE_TX(void * pvParameters);/*NODE TRANSMIT TASK BY MAILBOX 1 */
extern void vTaskCode_BTN1_GET(void * pvParameters);/*BTN1 GET STATUS TASK */

#endif /* CAN_H_ */
