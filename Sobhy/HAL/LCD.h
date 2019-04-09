/*
 * LCD.h
 *
 *  Created on: Mar 13, 2019
 *      Author: AVE-LAP-032
 */

#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

void LCD_INIT(void);
void LCD_Send_Command (uint8_t cmd);
void LCD_displayChar (uint8_t data);
void LCD_Send_String (uint8_t * data);
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
#define NUM_10 10
#define NUM_0 0
#define NUM_6 6
#define NUM_1 1
#define ZeroAscii  0x30
#define Get_Bit(Register,Bit)    (((Register&(1<<Bit))))
void LCD_Send_Data (uint8_t cmd);
void LCD_gotoRowColumn (uint8_t row,uint8_t col);
void PrintDecimalNum(uint16_t NUM);


#endif /* LCD_H_ */
