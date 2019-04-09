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
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "utils/uartstdio.h"
#include "FreeRTOS.h"
#include "task.h"
#include "BTN.h"
#include "LED.h"
#include "CAN.h"

volatile uint8_t TOKIN = 0;  /* VARIABLE TO KNOW WHICH NODE IS RUNNING */
volatile uint8_t TX_FLAG = 0; /* VARIABLE TO ACTIVE NORMAL MODE */
volatile uint8_t REVERS_FLAG = 0; /* VARIABLE TO ACTIVE REVERSE MODE */
//*****************************************************************************
// A flag for the interrupt handler to indicate that a message was received.
//*****************************************************************************
volatile bool g_bRXFlag = 0;
volatile bool g_bRXFlag1 = 0; /* MAILBOX 1 FLAG */
volatile bool g_bRXFlag2 = 0; /* MAILBOX 2 FLAG */
volatile bool g_bRXFlag3 = 0; /* MAILBOX 3 FLAG */

//*****************************************************************************
// A flag to indicate that some reception error occurred.
//*****************************************************************************
volatile bool g_bErrFlag = 0;

/*vTaskCode_INIT_CAN_ZERO */
/* Parameters : N/A */
/* I/p : N/A */
/* O/p : N/A */
/* Return : void  */
/* Function that init CAN 0    */
void vTaskCode_INIT_CAN_ZERO(void * pvParameters)/* init task for transmit ecu */
{

    while (1)
    {
#if defined(TARGET_IS_TM4C129_RA0) ||                                         \
    defined(TARGET_IS_TM4C129_RA1) ||                                         \
    defined(TARGET_IS_TM4C129_RA2)
        uint32_t ui32SysClock;
#endif

        /* Set the clocking to run directly from the external crystal/oscillator.
         TODO: The SYSCTL_XTAL_ value must be changed to match the value of the
         crystal used on your board. */

#if defined(TARGET_IS_TM4C129_RA0) ||                                         \
    defined(TARGET_IS_TM4C129_RA1) ||                                         \
    defined(TARGET_IS_TM4C129_RA2)
        ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ |
                        SYSCTL_OSC_MAIN |
                        SYSCTL_USE_OSC)
                25000000);
#else
        SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
        SYSCTL_XTAL_16MHZ);
#endif

        /* Set up the serial console to use for displaying messages.  This is
         just for this example program and is not needed for CAN operation.
         */
        /*
         Enable GPIO port A which is used for UART0 pins.
         TODO: change this to whichever GPIO port you are using.
         */
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

        /* Configure the pin muxing for UART0 functions on port A0 and A1.
         This step is not necessary if your part does not support pin muxing.
         TODO: change this to select the port/pin you are using.
         */
        GPIOPinConfigure(GPIO_PA0_U0RX);
        GPIOPinConfigure(GPIO_PA1_U0TX);

        /* Enable UART0 so that we can configure the clock.*/

        SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

        /* Use the internal 16MHz oscillator as the UART clock source.*/

        UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

        /* Select the alternate (UART) function for these pins.
         TODO: change this to select the port/pin you are using.
         */
        GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

        /* Initialize the UART for console I/O.*/

        UARTStdioConfig(0, 115200, 16000000);

        /* For this example CAN0 is used with RX and TX pins on port B4 and B5.
         The actual port and pins used may be different on your part, consult
         the data sheet for more information.
         GPIO port B needs to be enabled so these pins can be used.
         TODO: change this to whichever GPIO port you are using
         */
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

        /* Configure the GPIO pin muxing to select CAN0 functions for these pins.
         This step selects which alternate function is available for these pins.
         This is necessary if your part supports GPIO pin function muxing.
         Consult the data sheet to see which functions are allocated per pin.
         TODO: change this to select the port/pin you are using
         */
        GPIOPinConfigure(GPIO_PB4_CAN0RX);
        GPIOPinConfigure(GPIO_PB5_CAN0TX);

        /* Enable the alternate function on the GPIO pins.  The above step selects
         which alternate function is available.  This step actually enables the
         alternate function instead of GPIO for these pins.
         TODO: change this to match the port/pin you are using
         */
        GPIOPinTypeCAN(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5);

        // The GPIO port and pins have been set up for CAN.  The CAN peripheral
        // must be enabled.
        SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);

        // Initialize the CAN controller
        CANInit(CAN0_BASE);

        // Set up the bit rate for the CAN bus.  This function sets up the CAN
        // bus timing for a nominal configuration.  You can achieve more control
        // over the CAN bus timing by using the function CANBitTimingSet() instead
        // of this one, if needed.
        // In this example, the CAN bus is set to 500 kHz.  In the function below,
        // the call to SysCtlClockGet() or ui32SysClock is used to determine the
        // clock rate that is used for clocking the CAN peripheral.  This can be
        // replaced with a  fixed value if you know the value of the system clock,
        // saving the extra function call.  For some parts, the CAN peripheral is
        // clocked by a fixed 8 MHz regardless of the system clock in which case
        // the call to SysCtlClockGet() or ui32SysClock should be replaced with
        // 8000000.  Consult the data sheet for more information about CAN
        // peripheral clocking.
#if defined(TARGET_IS_TM4C129_RA0) ||                                         \
    defined(TARGET_IS_TM4C129_RA1) ||                                         \
    defined(TARGET_IS_TM4C129_RA2)
        CANBitRateSet(CAN0_BASE, ui32SysClock, 500000);
#else
        CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 500000);
#endif

        //
        // Enable interrupts on the CAN peripheral.  This example uses static
        // allocation of interrupt handlers which means the name of the handler
        // is in the vector table of startup code.  If you want to use dynamic
        // allocation of the vector table, then you must also call CANIntRegister()
        // here.
        //
        // CANIntRegister(CAN0_BASE, CANIntHandler); // if using dynamic vectors
        //
        CANIntEnable(CAN0_BASE,
        CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);

        /* Enable the CAN interrupt on the processor (NVIC). */
        IntEnable(INT_CAN0);

        /*Enable the CAN for operation.*/
        CANEnable(CAN0_BASE);
        LEDTaskInit();
        Btns_Init();
        vTaskSuspend(NULL); /*susspend for init tasks */

    }
}

/* CANIntHandler  */
/* Parameters : N/A */
/* I/p : N/A */
/* O/p : N/A */
/* Return : void  */
/* CAN 0 HANDLER */
void CANIntHandler(void)
{
    uint32_t ui32Status;

    ui32Status = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE);

    if (ui32Status == CAN_INT_INTID_STATUS)
    {
        ui32Status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);
        //
        // Set a flag to indicate some errors may have occurred.
        //
        g_bErrFlag = 1;
    }
    //
    // Check if the cause is message object 1. MAILBOX 1
    //
    else if (ui32Status == 1)
    {
        CANIntClear(CAN0_BASE, 1);
        g_bRXFlag1 = 1;/*receive flag mailbox 1 */
        g_bErrFlag = 0;
    }
    //
    // Check if the cause is message object 2. MAILBOX 2
    //
    else if (ui32Status == 2)
    {
        CANIntClear(CAN0_BASE, 2);
        g_bRXFlag2 = 1;/*receive flag mailbox 2 */
        g_bErrFlag = 0;/*error flag */
    }

    //
    // Check if the cause is message object 3. MAILBOX 3
    //
    else if (ui32Status == 3)
    {
        CANIntClear(CAN0_BASE, 3);
        g_bRXFlag3 = 1;/*receive flag mail box 3  */
        g_bErrFlag = 0;/*error flag mail box 3  */
    }

}

/*vTaskCode_NODE_ZERO_START */
/* Parameters : N/A */
/* I/p : N/A */
/* O/p : N/A */
/* Return : void  */
/* Function that START the network and it excute only once and susspended    */
void vTaskCode_NODE_ZERO_START(void * pvParameters)
{
    tCANMsgObject sCANMessage;
    uint32_t ui32MsgData;
    uint8_t *pui8MsgData;/* pointer to check data */

    ui32MsgData = DATA_N; /* DATA = 1 LED ON */
    pui8MsgData = (uint8_t *) &ui32MsgData;
    sCANMessage.ui32MsgID = 1; /* at the start the node zero will send msg for node 1 to start network NODE 1 ID */
    sCANMessage.ui32MsgIDMask = 0;
    sCANMessage.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
    sCANMessage.ui32MsgLen = sizeof(pui8MsgData);
    sCANMessage.pui8MsgData = pui8MsgData;

    while (1)
    {
        CANMessageSet(CAN0_BASE, 1, &sCANMessage, MSG_OBJ_TYPE_TX);/*transmit by mailbox 1 */

        if (g_bErrFlag)/* error occure */
        {
            UARTprintf(" error - cable connected?\n");
        }

        vTaskSuspend(NULL); /*susspend for init tasks */
    }

}

/*vTaskCode_NODE_RX*/
/* Parameters : N/A */
/* I/p : N/A */
/* O/p : N/A */
/* Return : void  */
/* node receive task by mailbox 2   */
void vTaskCode_NODE_RX(void * pvParameters)/*RECIVE TASK*/
{
    tCANMsgObject sCANMessage;
    uint8_t pui8MsgData[8];

    sCANMessage.ui32MsgID = ID_RX_N;/*RECEIVED ID */
    sCANMessage.ui32MsgIDMask = 0;
    sCANMessage.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
    sCANMessage.ui32MsgLen = 8;

    CANMessageSet(CAN0_BASE, 2, &sCANMessage, MSG_OBJ_TYPE_RX); /* receive on mailbox 2 */
    uint8_t state = ZERO;
    state = Btn1_Read();
    /**************************************/
    //tCANMsgObject sCANMessage_R;
    //uint8_t pui8MsgData_R[8];
    //sCANMessage_R.ui32MsgID = ID_RX_R;/*ID 0 */
    //sCANMessage_R.ui32MsgIDMask = 0;
    //sCANMessage_R.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
    //sCANMessage_R.ui32MsgLen = 8;
    //CANMessageSet(CAN0_BASE, 2, &sCANMessage_R, MSG_OBJ_TYPE_RX); /* receive on mailbox 2 */
    while (1)
    {
        if (g_bRXFlag2)/*check if CAN Receive msg on mailbox 2 g_bRXFlag2 set when msg received on mailbox 2   */
        {
            sCANMessage.pui8MsgData = pui8MsgData;

            CANMessageGet(CAN0_BASE, 2, &sCANMessage, 0);

            if (sCANMessage.ui32MsgID == ID_RX_N)
            {
                if (*sCANMessage.pui8MsgData == DATA_N)
                {
                    GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_1), GPIO_PIN_1);/* LED ON */
                    TOKIN = 1;/* TOKIN to know which node has this token and loop */
                    vTaskDelay(200);
                    GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_1), 0x0);/* LED OFF */
                    if (Btn1_Read() == BTN1_ON)/*CHECK IF BTN 1 PRESSED */
                    {
                        TX_FLAG = 0;/*NORMAL MODE FLAG */
                        REVERS_FLAG = 1;/*REVERS MODE FLAG */
                    }
                    else
                    {
                        TX_FLAG = 1;/*NORMAL MODE FLAG */
                        REVERS_FLAG = 0;/*REVERS MODE FLAG */
                    }
                    TOKIN = 0;
                }
                else if (*sCANMessage.pui8MsgData == DATA_R)
                {
                    GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_1), GPIO_PIN_1);/* LED ON */
                    TOKIN = 1;/* TOKIN to know which node has this token and loop */
                    vTaskDelay(200);
                    GPIOPinWrite(GPIO_PORTF_BASE, (GPIO_PIN_1), 0x0);/* LED OFF */
                    if (Btn1_Read() == BTN1_ON) /*CHECK IF BTN 1 PRESSED */
                    {
                        TX_FLAG = 1; /*NORMAL MODE FLAG */
                        REVERS_FLAG = 0; /*REVERS MODE FLAG */
                    }
                    else
                    {
                        TX_FLAG = 0;/*NORMAL MODE FLAG */
                        REVERS_FLAG = 1;/*REVERS MODE FLAG */
                    }
                    TOKIN = 0;
                }
            }

            g_bRXFlag2 = 0; /* clear the mailbox 2 receive flag */
            if (sCANMessage.ui32Flags & MSG_OBJ_DATA_LOST)
            {
                UARTprintf("CAN message loss detected\n");
            }
        }
        vTaskDelay(70);
    }
}

/*vTaskCode_NODE_TX*/
/* Parameters : N/A */
/* I/p : N/A */
/* O/p : N/A */
/* Return : void  */
/* node Transmit task by mailbox 2   */
void vTaskCode_NODE_TX(void * pvParameters)
{
    tCANMsgObject sCANMessage;
    uint32_t ui32MsgData;
    uint8_t *pui8MsgData;/* pointer to check data */

    ui32MsgData = DATA_N; /* data in case normal mode */
    pui8MsgData = (uint8_t *) &ui32MsgData;
    sCANMessage.ui32MsgID = ID_TX_N; /* MSG ID IN CASE NORMl MODE */
    sCANMessage.ui32MsgIDMask = 0;
    sCANMessage.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
    sCANMessage.ui32MsgLen = sizeof(pui8MsgData);
    sCANMessage.pui8MsgData = pui8MsgData;

    /*************REVERSE******************/
    tCANMsgObject sCANMessage_R;
    uint32_t ui32MsgData_R;
    uint8_t *pui8MsgData_R;/* pointer to check data */

    ui32MsgData_R = DATA_R; /* data in case normal mode */
    pui8MsgData_R = (uint8_t *) &ui32MsgData_R;
    sCANMessage_R.ui32MsgID = ID_TX_R; /* MSG ID IN CASE REVERS MODE */
    sCANMessage_R.ui32MsgIDMask = 0;
    sCANMessage_R.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
    sCANMessage_R.ui32MsgLen = sizeof(pui8MsgData_R);
    sCANMessage_R.pui8MsgData = pui8MsgData_R;

    while (1)
    {
        if (REVERS_FLAG == 1) /* if revers_flag == 1 it means the system in revers mode */
        {
            CANMessageSet(CAN0_BASE, 1, &sCANMessage_R, MSG_OBJ_TYPE_TX);/* transmit by mailbox 1 */
            REVERS_FLAG = 0;/* clear the revers flag */
        }

        if (TX_FLAG == 1)/* this flag will set if the node received msg successfuly */
        {
            CANMessageSet(CAN0_BASE, 1, &sCANMessage, MSG_OBJ_TYPE_TX);/* transmit by mailbox 1 */
            TX_FLAG = 0; /* clear the transmit flag */
        }

        if (g_bErrFlag)/* if there is error occure the g_bErrFlag will be set */
        {
            UARTprintf(" error - cable connected?\n");
        }
        vTaskDelay(150);
    }

}

/* BTN1 tasks  */
/* Parameters : N/A */
/* I/p : N/A */
/* O/p : N/A */
/* Return : void  */
/* Function that get status of BTN1 */
void vTaskCode_BTN1_GET(void * pvParameters)
{
    static uint8_t state = ZERO;

    for (;;)
    {
        state = Btn1_Read();

        if ((state == BTN1_ON) && (TOKIN == 1))
        {
            REVERS_FLAG = 1;
            TOKIN = 0;
        }

        vTaskDelay(60);

    }
}
