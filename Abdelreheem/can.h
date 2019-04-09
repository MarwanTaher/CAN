/*
 * can.h
 *
 *  Created on: Apr 4, 2019
 *      Author: Ahmed Abdlrehem
 */

#ifndef CAN_H_
#define CAN_H_
/************************************************************************************/
typedef struct{
     uint8_t pui8MsgData[8];
    uint32_t ID;

}strData_Id;
/*******************************Can_APIS**********************************************/
extern void Can_Transmit(uint32_t Copy_u32Data,uint32_t Copy_u32Id);
extern strData_Id Can_Receive();
extern void Can_Init();

/*****************************************************************************/
extern volatile uint8_t g_bErrFlag;

/*****************************************************************************/
extern volatile uint8_t Rx_flag;
/******************************************************************************/


#endif /* CAN_H_ */
