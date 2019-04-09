

#include "inc/spi.h"
#include "driverlib/ssi.h"


/***********************************************************************************************************************
 * Function name :- SPI_init
 * Function job :- initiate spi module
 * Function argument :- N/A
 * Function return :- N/A
 ***********************************************************************************************************************/
void SPI_init_M(void)
{
    // Enable the SSI0 peripheral
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
    //
    // Wait for the SSI0 module to be ready.
    //
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_SSI0))
    {
    }
    //
    // Configure the SSI.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA))
       {
       }

    SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0,
       SSI_MODE_MASTER, 2000000, 8);

    GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_2 |
                         GPIO_PIN_3);


    //
    // Enable the SSI module.
    //
    GPIOPinConfigure(GPIO_PA2_SSI0CLK);
             GPIOPinConfigure(GPIO_PA3_SSI0FSS);
             GPIOPinConfigure(GPIO_PA4_SSI0RX);
             GPIOPinConfigure(GPIO_PA5_SSI0TX);



       SSIEnable(SSI0_BASE);

}

/***********************************************************************************************************************
 * Function name :- SPI_init
 * Function job :- initiate spi module
 * Function argument :- N/A
 * Function return :- N/A
 ***********************************************************************************************************************/
void SPI_init_S(void)
{
    // Enable the SSI0 peripheral
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI3);
    //
    // Wait for the SSI0 module to be ready.
    //
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_SSI3))
    {
    }
    //
    // Configure the SSI.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
       while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD))
          {
          }

    SSIConfigSetExpClk(SSI3_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0,
       SSI_MODE_SLAVE, 2000000, 8);
    GPIOPinTypeSSI(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 |
                      GPIO_PIN_3);

    //
    // Enable the SSI module.
    //

    GPIOPinConfigure(GPIO_PD0_SSI3CLK);
           GPIOPinConfigure(GPIO_PD1_SSI3FSS);
           GPIOPinConfigure(GPIO_PD2_SSI3RX);
           GPIOPinConfigure(GPIO_PD3_SSI3TX);

    SSIEnable(SSI3_BASE);

    /*
    GPIOPinConfigure(GPIO_PA2_SSI0CLK);
       GPIOPinConfigure(GPIO_PA3_SSI0FSS);
       GPIOPinConfigure(GPIO_PA4_SSI0RX);
       GPIOPinConfigure(GPIO_PA5_SSI0TX);
       */

}

/***********************************************************************************************************************
 * Function name :- SPI_Send
 * Function job :- sending data
 * Function argument :- N/A
 * Function return :- N/A
 ***********************************************************************************************************************/
void SPI_Send(uint16_t data)
{

    /* send required data */
    SSIDataPut(SSI0_BASE, data);
    /* wiath until send completed */

    while(SSIBusy(SSI0_BASE))
      {
      }

}

/***********************************************************************************************************************
 * Function name :- SPI_Recieve
 * Function job :- recieving data
 * Function argument :- N/A
 * Function return :- N/A
 ***********************************************************************************************************************/
uint32_t SPI_Recieve(void)
{

    uint32_t data;
    SSIDataGetNonBlocking(SSI3_BASE,&data);
    return data ;
}
