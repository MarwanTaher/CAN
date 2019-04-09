

/*****************************************************************************************************
 * includes section
 ****************************************************************************************************/



#include "can.h"
#include "can_cfg.h"
#include "LED.h"
volatile  uint8_t tx_flag = NUM_0; /* flag to indicate that can has sent data to bus */
volatile  uint8_t rx_flag = NUM_0; /* flag to indicate that can has received  data to bus */
volatile  uint8_t err_flag = NUM_0; /* flag to indicate that can has an error on the bus bus */



extern tCANMsgObject sMsgObjectRx ;
extern tCANMsgObject sMsgObjectTx ;


/********************************************************************************************************************************************
 * Function name :- CAN_init
 * Function job :- initialize can module
 * Function arguments :- selected can module number
 * Function return :- N/A
 ************************************************************************************************************************************************/

void CAN_init( uint8_t CAN_MODULE_NUM )
{
/* determine which can module is configured */

    switch(CAN_MODULE_NUM)
    {
    /* if can 0 is selected */
    case CAN0 :

        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

                  //
                  // Check if the peripheral access is enabled.
                  //
                  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB))
                  {
                  }

        GPIOPinTypeCAN(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5);

        /*
        // Enable the CAN0 module.
        */
        SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);
        /*
        // Wait for the CAN0 module to be ready.
        */
        while(!SysCtlPeripheralReady(SYSCTL_PERIPH_CAN0));
        //
        // Reset the state of all the message objects and the state of the CAN
        // module to a known state.
        //
        GPIOPinConfigure(GPIO_PB4_CAN0RX);
                    GPIOPinConfigure(GPIO_PB5_CAN0TX);

        //
        CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 500000);

        CANInit(CAN0_BASE);
        /* enable master interrupt */
        CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);
        //
        // Enable the CAN interrupt on the processor (NVIC).
        //
        IntEnable(INT_CAN0);
        MAILBOX_REC_init();
        //
        // Take the CAN0 device out of INIT state.
        //
        CANEnable(CAN0_BASE);
        break ;

    case CAN1 :
        /*
               // Enable the CAN0 module.
               */
               SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN1);
               /*
               // Wait for the CAN0 module to be ready.
               */
               while(!SysCtlPeripheralReady(SYSCTL_PERIPH_CAN1));
               //
               // Reset the state of all the message objects and the state of the CAN
               // module to a known state.
               //
               CANInit(CAN1_BASE);
               //
               // Configure the controller for 1 Mbit operation.
               //
              // CANSetBitTiming(CAN1_BASE, &CANBitClk);
               //
               // Take the CAN0 device out of INIT state.
               //
               CANEnable(CAN1_BASE);
              break ;

    }


}

/********************************************************************************************************************************************
 * Function name :- MAILBOX_REC_init
 * Function job :- initialize recieving mail box
 * Function arguments :- N/A
 * Function return :- N/A
 ************************************************************************************************************************************************/
void MAILBOX_REC_init(void)
{
    CANMessageSet(CAN0_BASE,RX_MAILBOX, &sMsgObjectRx, MSG_OBJ_TYPE_RX);
}

/********************************************************************************************************************************************
 * Function name :- CAN_Transmit
 * Function job :- send value by can
 * Function arguments :- value sent
 * Function return :- N/A
 ************************************************************************************************************************************************/
void CAN_Transmit(uint8_t data)
{
 uint8_t *p_data=(uint8_t *)&data;
    /*  take input adress and put it into data member */
    sMsgObjectTx.pui8MsgData = p_data;
    /* send data to can bus on mail box 3 */
    CANMessageSet(CAN0_BASE,TX_MAILBOX, &sMsgObjectTx, MSG_OBJ_TYPE_TX);


}

/********************************************************************************************************************************************
 * Function name :- CAN_Transmit
 * Function job :- send value by can
 * Function arguments :- value sent
 * Function return :- N/A
 ************************************************************************************************************************************************/
uint8_t* CAN_Recieve(void)
{
   /* set mail box 1 to receive any data from bus */
        static uint8_t pudata[8];
        sMsgObjectRx.pui8MsgData=pudata;
       CANMessageGet(CAN0_BASE,RX_MAILBOX , &sMsgObjectRx, 0);

     return pudata;

}


/*****************************************************************************************************************************/

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


        ui32Status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);

        /*
        * Set a flag to indicate some errors may have occurred.
        */
      err_flag = 1;


    }

    //
    // Check if the cause is message object 1, which what we are using for
    // sending messages.
    //
     if(ui32Status == TX_MAILBOX )
    {


        //
        // Getting to this point means that the TX interrupt occurred on
        // message object 1, and the message TX is complete.  Clear the
        // message object interrupt.
        //
        CANIntClear(CAN0_BASE, TX_MAILBOX);

       tx_flag = NUM_1;
        /*
        * Since the message was sent, clear any error flags.
        */
       err_flag = NUM_0;

    }
     /* if case of interrupt is receiving msg */
     else  if(ui32Status == RX_MAILBOX )
    {



        //
        // Getting to this point means that the TX interrupt occurred on
        // message object 1, and the message TX is complete.  Clear the
        // message object interrupt.
        //
        CANIntClear(CAN0_BASE, RX_MAILBOX);

        // Increment a counter to keep track of how many messages have been
        // sent.  In a real application this could be used to set flags to
        // indicate when a message is sent.
        //
       // g_ui32MsgCount++;

        //
        // Since the message was sent, clear any error flags.
        //
        rx_flag = 1;
       err_flag = NUM_0 ;
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

