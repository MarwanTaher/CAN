


#ifndef SPI_H_
#define SPI_H_


#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

#define SSI_MODE_MASTER         0x00000000  // SSI master
#define SSI_MODE_SLAVE          0x00000001  // SSI slave
#define SSI_FRF_MOTO_MODE_0     0x00000000  // Moto fmt, polarity 0, phase 0
#define SSI_FRF_MOTO_MODE_1     0x00000002  // Moto fmt, polarity 0, phase 1
#define SSI_FRF_MOTO_MODE0     0x00000000


/***********************************************************************************************************************
 * Function name :- SPI_init
 * Function job :- initiate spi module
 * Function argument :- N/A
 * Function return :- N/A
 ***********************************************************************************************************************/
void SPI_init_M(void);

/***********************************************************************************************************************
 * Function name :- SPI_init
 * Function job :- initiate spi module
 * Function argument :- N/A
 * Function return :- N/A
 ***********************************************************************************************************************/
void SPI_init_S(void);
/***********************************************************************************************************************
 * Function name :- SPI_Send
 * Function job :- sending data
 * Function argument :- N/A
 * Function return :- N/A
 ***********************************************************************************************************************/
void SPI_Send(uint16_t data);

/***********************************************************************************************************************
 * Function name :- SPI_Recieve
 * Function job :- recieving data
 * Function argument :- N/A
 * Function return :- N/A
 ***********************************************************************************************************************/
uint32_t SPI_Recieve(void);

#endif
