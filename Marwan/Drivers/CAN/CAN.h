/*
 * CAN.h
 *
 *  Created on: Apr 3, 2019
 *      Author: AVE-LAP-071
 */

#ifndef DRIVERS_CAN_CAN_H_
#define DRIVERS_CAN_CAN_H_
#include <stdbool.h>
#include <stdint.h>
#include "driverlib/can.h"

extern void CAN_Init(void);
void CANIntHandler(void);
void SimpleDelay(void);
void StartUpState(void);
void InitConsole(void);

/* A flag to indicate that some transmission error occurred.*/
extern volatile uint8_t g_bErrFlag;
/*****************************************************************************/
/* A flag for the interrupt handler to indicate that a message was received. */
/*****************************************************************************/
extern volatile bool g_bRXFlag1;
extern volatile bool g_bRXFlag2;
extern volatile bool g_bRXFlag3;
extern uint8_t Token;

        /***************************************************/
        /* Define SEND CAN Structures.    */
        /***************************************************/
        extern tCANMsgObject sCANMessageTX;
        extern uint8_t *pui8MsgDataout;
        extern uint32_t ui32MsgDataout;
        /***************************************************/
        /* Define REC CAN Structures.    */
        /***************************************************/
        extern tCANMsgObject sCANMessageRX;
        extern tCANMsgObject sCANMessageRXG;

        extern uint8_t pui8MsgDatain[8];
        extern uint8_t pui8MsgDataing[8];


#endif /* DRIVERS_CAN_CAN_H_ */
