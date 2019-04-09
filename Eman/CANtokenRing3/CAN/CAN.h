/*
 * CAN.h
 *
 *  Created on: Apr 3, 2019
 *      Author: AVE-LABS-50
 */

#ifndef CAN_CAN_H_
#define CAN_CAN_H_


//*****************************************************************************
//
// Configure the CAN and enter a loop to transmit periodic CAN messages.
//
//*****************************************************************************

extern tCANMsgObject sCANMessage;

extern volatile bool g_bErrFlag ;
extern volatile bool g_bRXFlag ;
extern volatile bool g_bRXFlag1;
extern volatile bool g_bRXFlag2;

extern volatile uint32_t g_ui32MsgCount ;

void CANIntHandler(void);
void
SimpleDelay(void);
void CAN0RX_INIT(void);
void CAN0TX_INIT(void);
void CAN0_RX(void);
void CAN0_TX_node1(uint8_t data);
void CAN0_TX_node2(uint8_t data);
void CAN0_TX_node3(uint8_t data);

#endif /* CAN_CAN_H_ */
