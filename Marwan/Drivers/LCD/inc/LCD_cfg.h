#ifndef LCD_CFG_H_
#define LCD_CFG_H_

#include <stdint.h>

#define LCD_RS GPIO_PIN_2
#define LCD_RW GPIO_PIN_3
#define LCD_EN GPIO_PIN_4

#define LCD_PORT PortA
#define LCD_D4 GPIO_PIN_4
#define LCD_D5 GPIO_PIN_5
#define LCD_D6 GPIO_PIN_6
#define LCD_D7 GPIO_PIN_7

#define LCD_Operation_BIT_NUMBER 4 
#define Mask_LowerByte 0x0F
#define Mask_UpperByte 0xF0

#define CMD_RESET 0x01
#define CMD_LCD4BIT33 0x33
#define CMD_LCD4BIT32 0x32
#define CMD_LCD_2_LINES_5X7 0x28
#define CMD_CURSOR_ON 0x0E
#define CMD_SHIFT_DISPLAY_LEFT 0x06
#define CMD_SHIFT_CURSOR_RIGHT 0x14
#define CMD_SHIFT_CURSOR_LEFT 0x10
#define CMD_INCREMENT_CURSOR 0x06
#define CMD_DECREMENT_CURSOR 0x04
#define CMD_CURSOR_TO_LINE1 0x80
#define CMD_CURSOR_TO_LINE2 0xC0
#define CMD_FIRST_ALLOWED_ADDRESS_IN_CGRAM 0x40
#define CMD_END_ALLOWED_ADDRESS_IN_CGRAM 0x80

#define NULL_CHARACTER '\0' 
#define LCD_CLEAR                   0x01 /* clear screen */
#define TWO_MS 2

#define FIRST_ROW 1
#define SECOND_ROW 2




/************************************************************************/
/* LCD Commands                                                         */
/************************************************************************/
#define LCD_FOUR_BIT_TWO_LINE_MODE  0x02 /* initialize LCD in Four bits two lines mode*/
#define LCD_FOUR_BIT_DATA_MODE      0x28 /* Four Bit mode */
#define LCD_EIGHT_BIT_MODE          0x38 /* Eight Bit mode */
#define LCD_CLEAR                   0x01 /* clear screen */
#define LCD_SET_CURSOR_LOCATION     0x80 /* Set cursor at the first line */
#define LCD_CURSOR_ON               0x0E /* display cursor */
#define LCD_CURSOR_OFF              0x0C /* turn cursor off*/
#define LCD_SHIFT_CURSOR_RIGHT      0x14 /* shift cursor right */
#define LCD_CURSOR_LINE_ONE         0x80 /* set cursor at the first line*/
#define LCD_CURSOR_LINE_TWO         0xC0 /* set cursor to the second line*/
#define LCD_MASK_HIGH_NIBBLES       0x0F /* mask higher nibbles */
#define LCD_MASK_LOW_NIBBLES        0xF0 /* mask lower nibbles */



/************************************************************************/
/* define number of rows in LCD                                         */
/************************************************************************/
#define LCD_ROW1                0
#define LCD_ROW2                1
#define LCD_ROW3                2
/************************************************************************/
/* define number of columns                                             */
/************************************************************************/
#define LCD_COL1                0
#define LCD_COL2                1
#define LCD_COL3                2
#define LCD_COL4                3
#define LCD_COL5                4
#define LCD_COL6                5
#define LCD_COL7                6
#define LCD_COL8                7
#define LCD_COL9                8
#define LCD_COL10               9
#define LCD_COL11               10
#define LCD_COL12               11
#define LCD_COL13               12
#define LCD_COL14               13
#define LCD_COL15               14
#define LCD_COL16               16



#endif /* LCD_CFG_H_ */
