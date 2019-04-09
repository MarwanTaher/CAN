/*
 * CAN.h
 *
 *  Created on: Apr 3, 2019
 *      Author: AVE-LAP-016
 */

#ifndef CAN_H_
#define CAN_H_

#define TRANSMIT_STATUS 1
#define RECEIVE_STATUS 2
#define MAX_NUM_OF_NODES 3
#define NODE_1_ID    0x01
#define NODE_2_ID    0x02
#define NODE_3_ID    0x03
#define NODE_4_ID    0x04
#define MY_ID        NODE_2_ID
#define FRONT_NODE_ID     (MY_ID + 0x01)
#define BACK_NODE_ID      (MY_ID - 0x01)
#define LAST_NODE MAX_NUM_OF_NODES
#define STARTUP_STATE 0
#define NORMAL_STATE  1
void SimpleDelay(void);
void CAN0_init(void);
void CAN0_Transmit_task(void);
void CAN0_Receive_task(void);
//void CAN0_Tranceive_task(void *pvParameters);
void CAN0_Upgraded_Tranceive_task(void *pvParameters);
#endif /* CAN_H_ */
