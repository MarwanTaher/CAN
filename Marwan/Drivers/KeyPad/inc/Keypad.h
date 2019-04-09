/*
 * Keypad.h
 *
 *  Created on: Mar 12, 2019
 *      Author: AVE-LAP-071
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_



#include "Keypad_cfg.h"
#include "CommonDefinations.h"
#include "CommonNumbers.h"
#include "types.h"

/************************************************************************/
/* Function: KeyPad Init                                                */
/* @param: void                                                         */
/* return: void                                                         */
/* Description: Initialize keypad pins directions                      */
/************************************************************************/

void Keypad_Init(void);


/************************************************************************/
/* Function: Keypad_Task                                                */
/* @param: void                                                         */
/* return: uint8                                                         */
/* Description: Task to return the key pressed                           */
/************************************************************************/
uint8 Keypad_func(void);

#endif /* KEYPAD_H_ */
