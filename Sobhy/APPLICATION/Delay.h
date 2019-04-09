/*
 * Delay.h
 *
 *  Created on: Mar 13, 2019
 *      Author: AVE-LAP-032
 */

#ifndef DELAY_H_
#define DELAY_H_

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/sysctl.h"

void delayMs(uint32_t ui32Ms) ;

void delayUs(uint32_t ui32Us) ;

#endif /* DELAY_H_ */
