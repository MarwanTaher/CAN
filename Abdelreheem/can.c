#include "Types.h"
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/can.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "driverlib/sysctl.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "LCD.h"
#include "driverlib/can.h"
#include "can.h"

volatile uint8_t g_bErrFlag = 0;

/*****************************************************************************/
volatile uint8_t Rx_flag=0;
static tCANMsgObject sCANMessage_tx;
static tCANMsgObject sCANMessage_rx;
static strData_Id D_I_Str;
/***********************Can_Init()*********************
 * I/P:NONE
 * O/P:NONE
 * Description:This function initializes can and enables the interrupts on tranmit and receiving
 ********************************************************/
void Can_Init()
{
    InitConsole();
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinConfigure(GPIO_PB4_CAN0RX);
    GPIOPinConfigure(GPIO_PB5_CAN0TX);
    GPIOPinTypeCAN(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);
    CANInit(CAN0_BASE);
    CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 500000);
    CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);
    IntEnable(INT_CAN0);
    CANEnable(CAN0_BASE);
    sCANMessage_rx.ui32MsgID = 0;
    sCANMessage_rx.ui32MsgIDMask = 0;
    sCANMessage_rx.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
    sCANMessage_rx.ui32MsgLen = 8;
    CANMessageSet(CAN0_BASE, 2, &sCANMessage_rx, MSG_OBJ_TYPE_RX);

}
/***********************can_Transmit*********************
 * I/P:uint32_t and uint32_t
 * O/P:NOTHING
 * Description:This function transmits to the can bus using id and data sent
 ********************************************************/
void Can_Transmit(uint32_t Copy_u32Data,uint32_t Copy_u32Id)
{
   // static tCANMsgObject sCANMessage;
    static uint8_t *pui8MsgData;

    pui8MsgData = (uint8_t *) &Copy_u32Data;

    sCANMessage_tx.ui32MsgID = Copy_u32Id;
    sCANMessage_tx.ui32MsgIDMask = 0;
    sCANMessage_tx.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
    sCANMessage_tx.ui32MsgLen = sizeof(pui8MsgData);
    sCANMessage_tx.pui8MsgData = pui8MsgData;
    CANMessageSet(CAN0_BASE, 1, &sCANMessage_tx, MSG_OBJ_TYPE_TX);
   // UARTprintf(" transmitted data:%d\n",*pui8MsgData);
}

/***********************can_Receive*********************
 * I/P:NONE
 * O/P:strData_ID
 * Description:this function returns structure that contains data and id of received messages
 ********************************************************/
strData_Id Can_Receive()
{

    sCANMessage_rx.pui8MsgData = D_I_Str.pui8MsgData;

    CANMessageGet(CAN0_BASE, 2, &sCANMessage_rx, 0);
    D_I_Str.ID=sCANMessage_rx.ui32MsgID;
    UARTprintf(" received data:%d\n",sCANMessage_rx.ui32MsgID);
    return D_I_Str;

}

void CANIntHandler(void)
{
    uint32_t ui32Status;

       //
       // Read the CAN interrupt status to find the cause of the interrupt
       //
       ui32Status = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE);

       //
       // If the cause is a controller status interrupt, then get the status
       //
       if(ui32Status == CAN_INT_INTID_STATUS)
       {
           //
           // Read the controller status.  This will return a field of status
           // error bits that can indicate various errors.  Error processing
           // is not done in this example for simplicity.  Refer to the
           // API documentation for details about the error status bits.
           // The act of reading this status will clear the interrupt.
           //
           ui32Status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);
          // GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);

           //
           // Set a flag to indicate some errors may have occurred.
           //
           g_bErrFlag = 1;
       }

       //
       // Check if the cause is message object 1, which what we are using for
       // receiving messages.
       //
       else if(ui32Status == 1)
       {
           //
           // Getting to this point means that the RX interrupt occurred on
           // message object 1, and the message reception is complete.  Clear the
           // message object interrupt.
           //
           CANIntClear(CAN0_BASE, 1);
           //GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
           //
           // Increment a counter to keep track of how many messages have been
           // received.  In a real application this could be used to set flags to
           // indicate when a message is received.
           //
          // g_ui32MsgCount++;

           //
           // Set flag to indicate received message is pending.


           //
           // Since a message was received, clear any error flags.
           //
           g_bErrFlag = 0;
       }
       else if(ui32Status == 2){
          // GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
           CANIntClear(CAN0_BASE, 2);
           Rx_flag = 1;


       }
       //
       // Otherwise, something unexpected caused the interrupt.  This should
       // never happen.
       //
       else
       {
           //
           // Spurious interrupt handling can go here.
           //
       }
}
