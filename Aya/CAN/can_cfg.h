



/*************************************************************************************************************
 *                                               guard file
 ****************************************************************************************************************/
#ifndef  CAN_CFG_H_
#define  CAN_CFG_H_

/*****************************************************************************************************
 *                                          includes section
 ****************************************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "inc/hw_can.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/can.h"




/*   define recieving  member of message object of can */
// tCANMsgObject sMsgObjectRx;
 /*   define sending  member of message object of can */
 //tCANMsgObject sMsgObjectTx;


extern tCANMsgObject sMsgObjectRx;
extern  tCANMsgObject sMsgObjectTx;

#define  MY_ID 1







#endif    /*  end of CAN_CFG_H_   */
