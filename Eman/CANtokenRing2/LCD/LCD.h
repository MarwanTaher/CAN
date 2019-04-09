/*
 * LCD.h
 *
 *  Created on: Mar 13, 2019
 *      Author: AVE-LABS-50
 */

#ifndef LCD_LCD_H_
#define LCD_LCD_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

/************************************************************************/
/* FUNCTION NAME: LCD_INIT                                              */
/* @Param: void                                                         */
/* return: void                                                         */
/* FUNCTION Description: Initialization of LCD                          */
/************************************************************************/
void LCD_INIT(void);
/************************************************************************/
/* FUNCTION NAME: LCD_Send_Data                                         */
/* @Param: Character                                                    */
/* return: void                                                         */
/* FUNCTION Description: Display Character on LCD                       */
/************************************************************************/
void LCD_Send_Data (uint8_t cmd);

/************************************************************************/
/* FUNCTION NAME: LCD_sendCommand                                       */
/* @Param: Command                                                      */
/* return: void                                                         */
/* FUNCTION Description: Sending LCD Commands                           */
/************************************************************************/
void LCD_Send_Command (uint8_t cmd);

void LCD_displayChar (uint8_t data);

/************************************************************************/
/* FUNCTION NAME: LCD_gotoRowColumn                                     */
/* @Param: the row and column of LCD cell                               */
/* return: void                                                         */
/* FUNCTION Description: go to certain the row, column on LCD           */
/************************************************************************/
void LCD_gotoRowColumn(uint8_t line, uint8_t digit);

/************************************************************************/
/* FUNCTION NAME: LCD_displayString                                     */
/* @Param: Array of String and it's size                                */
/* return: void                                                         */
/* FUNCTION Description: Display String on LCD                          */
/************************************************************************/
void LCD_displayString(const uint8_t* ARR, uint8_t SIZE);

/*********************************************************************************/
/* FUNCTION NAME: PrintDecimalNum                                                */
/* @Param: Decimal Number                                                        */
/* return: void                                                                  */
/* FUNCTION Description: print Decimal Number consists of more than 1 digit      */
/*********************************************************************************/
void PrintDecimalNum(uint16_t NUM);

/* LCD Lines */

#define FirstLine 0
#define SecondLine 1
#define FirstLineADD  0x80
#define SecondLineADD 0xC0


#define ZeroAscii  0x30

#define First_Bit 0x01
#define LCD_RS GPIO_PIN_2
#define LCD_RW GPIO_PIN_3
#define LCD_E GPIO_PIN_4
#define LCD_D4 GPIO_PIN_4
#define LCD_D5 GPIO_PIN_5
#define LCD_D6 GPIO_PIN_6
#define LCD_D7 GPIO_PIN_7
#define PORT1_LCD  GPIO_PORTA_BASE
#define PORT2_LCD  GPIO_PORTC_BASE
#define CMND1_4BITMODE 0X33
#define CMND2_4BITMODE 0x32
#define CMND3_4BITMODE 0X28
#define CURSOR_ON 0X0E
#define  CLEAR_LCD 0X01
#define FIRST_ROW 0x80
#define SECOND_ROW 0xC0
#define Get_Bit(Register,Bit)    (((Register&(1<<Bit))))




#endif /* LCD_LCD_H_ */
