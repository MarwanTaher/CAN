/*
 * SPI.c
 *
 *  Created on: Mar 20, 2019
 *      Author: AVE-LAP-063
 */


#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "SPI.h"

#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "utils/uartstdio.h"
#include "driverlib/sysctl.h"
#include "inc/hw_memmap.h"
#include "driverlib/ssi.h"

void SPI_RECIEVE_INIT (void)
{

        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

        //
         // Enable the SSI0 peripheral
         //
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

        SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI3);


         //
         // Wait for the SSI0 module to be ready.
         //
         while(!SysCtlPeripheralReady(SYSCTL_PERIPH_SSI3))
         {
         }
         GPIOPinConfigure(GPIO_PD0_SSI3CLK);
             GPIOPinConfigure(GPIO_PD1_SSI3FSS);
             GPIOPinConfigure(GPIO_PD2_SSI3RX);
             GPIOPinConfigure(GPIO_PD3_SSI3TX);
         //
         // Configure the SSI.
         //

         // Enable the SSI module.
         //
         //
            // Configure the GPIO settings for the SSI pins.  This function also gives
            // control of these pins to the SSI hardware.  Consult the data sheet to
            // see which functions are allocated per pin.
            // The pins are assigned as follows:
            //      PA5 - SSI3Tx
            //      PA4 - SSI4Rx
            //      PA3 - SSI4Fss
            //      PA2 - SSI4CLK
            // TODO: change this to select the port/pin you are using.
            //
            GPIOPinTypeSSI(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_3 |
                           GPIO_PIN_2);
            SSIConfigSetExpClk(SSI3_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0,
            SSI_MODE_SLAVE, 2000000, 8);
            //

         SSIEnable(SSI3_BASE);
}

/*********************************************************************************/
/* FUNCTION NAME: SPI_RECIEVE                                                    */
/* @Param: *void                                                                 */
/* return: void                                                                  */
/* FUNCTION Description: receive data from spi                                   */
/*********************************************************************************/


uint32_t SPI_RECIEVE(void)
{
        uint32_t Data_Recieved=0;
        /*This function gets received data from the receive FIFO of the specified SSI module and places that data into
         * the location specified by the ui32Data parameter. If there is no data in the
         * FIFO, then this function returns a zero         .*/
         if(SSIDataGetNonBlocking(SSI3_BASE, &Data_Recieved ))
         {
             /* IF DATA RECIEVED TURN LED ON*/
             GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3 | GPIO_PIN_2|GPIO_PIN_1);//direction OUTPUT

             GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,GPIO_PIN_1);

         }
         return Data_Recieved ;

}
void SPI_INIT (){
    char *pcChars = "SSI Master send data.";
    int32_t i32Idx;
    //
    // Enable the SSI0 peripheral
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);


    //
    // Wait for the SSI0 module to be ready.
    //
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_SSI0))
    {
    }
    GPIOPinConfigure(GPIO_PA2_SSI0CLK);
        GPIOPinConfigure(GPIO_PA3_SSI0FSS);
        GPIOPinConfigure(GPIO_PA4_SSI0RX);
        GPIOPinConfigure(GPIO_PA5_SSI0TX);
    //
    // Configure the SSI.
    //

    // Enable the SSI module.
    //
    //
       // Configure the GPIO settings for the SSI pins.  This function also gives
       // control of these pins to the SSI hardware.  Consult the data sheet to
       // see which functions are allocated per pin.
       // The pins are assigned as follows:
       //      PA5 - SSI0Tx
       //      PA4 - SSI0Rx
       //      PA3 - SSI0Fss
       //      PA2 - SSI0CLK
       // TODO: change this to select the port/pin you are using.
       //
       GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_3 |
                      GPIO_PIN_2);
       SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0,
       SSI_MODE_MASTER, 2000000, 8);
       //

    SSIEnable(SSI0_BASE);
    //
    // Send some data.
    //
}
void SPI_TRANSMIT(uint32_t Data)
{
    SSIDataPut(SSI0_BASE,Data);
}
