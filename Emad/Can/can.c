/*
 * can.c
 *
 *  Created on: Apr 3, 2019
 *      Author: AVE-LAP-44
 */



#include "../STD/Std_Types.h"
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/can.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/can.h"

#include "can.h"

#define mailbox1    1
#define mailbox2    2

#define mailbox3    3
#define mailbox4    4



volatile uint8 error_flag;
volatile uint8  receive_flag;



void Can_init(uint8 can_channel )
{
    switch(can_channel)
    {
        case CAN0:
        {
            /* Enable PORTB CLK to use CAN0 with RX and TX pins on B4 and B5 */
            SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

            /* Config. Pin B4 as CAN0 RX */
            GPIOPinConfigure(GPIO_PB4_CAN0RX);

            /* Config. Pin B5 as CAN0 TX */
            GPIOPinConfigure(GPIO_PB5_CAN0TX);

            /* Enable the alternate function on the GPIO pins 4,5 */
            GPIOPinTypeCAN(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5);

            /* Set the clk of CAN0 */
            SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);

            /* Init CAN0 */
            CANInit(CAN0_BASE);

            /* Set up the bit rate for the CAN bus */
            CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 500000);

            /* Enable interrupts on the CAN peripheral */
            CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);

            /* Enable the CAN interrupt on the processor (NVIC) */
            IntEnable(INT_CAN0);

            /* Enable the CAN for operation */
            CANEnable(CAN0_BASE);
            break;


        }
        default :
            break;
    }






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
        // The act of reading this status will clear the interrupt.  If the
        // CAN peripheral is not connected to a CAN bus with other CAN devices
        // present, then errors will occur and will be indicated in the
        // controller status.
        //
        ui32Status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);

        //
        // Set a flag to indicate some errors may have occurred.
        //
        error_flag = 1;
    }


    /* Check if the cause is message object 1, which what we are using for*/
    else if(mailbox1==ui32Status)
    {

        CANIntClear(CAN0_BASE, mailbox1);
        error_flag = STD_LOW;

    }


    else if(mailbox2==ui32Status)
    {

           CANIntClear(CAN0_BASE, mailbox2);
           receive_flag=STD_HIGH;
           error_flag = STD_LOW;
    }
    else if(mailbox3==ui32Status)
    {
        CANIntClear(CAN0_BASE, mailbox3);
        error_flag = STD_LOW;
    }
    else
    {

    }
}


