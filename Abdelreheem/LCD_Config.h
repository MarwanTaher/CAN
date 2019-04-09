

/*
 * LCD_Config.h
 *
 * Created: 2/19/2019 12:17:10 PM
 *  Author: AVE-LAP-005
 */


#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_
/*Choose four bit mode */
#define FOUR_BIT_MODE

/* Eight bit mode pins*/
#define LCD_PIN0 8
#define LCD_PIN1 9
#define LCD_PIN2 10
#define LCD_PIN3 11
#define LCD_PIN4 12
#define LCD_PIN5 13
#define LCD_PIN6 14
#define LCD_PIN7 15

/*LCD Control Pins*/
#define LCD_RS 1
#define LCD_RW 2
#define LCD_EN 3
/* pins to send data in four bit mode*/
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7
/* mask for every bit to send this bit*/
#define LCD_CMD_BIT_ZERO  0b00000001
#define LCD_CMD_BIT_ONE   0b00000010
#define LCD_CMD_BIT_TWO   0b00000100
#define LCD_CMD_BIT_THREE 0b00001000
#define LCD_CMD_BIT_FOUR  0b00010000
#define LCD_CMD_BIT_FIVE  0b00100000
#define LCD_CMD_BIT_SIX   0b01000000
#define LCD_CMD_BIT_SEVEN 0b10000000
/* mask for every bit to send this bit*/
#define LCD_DATA_BIT_ZERO   0b00000001
#define LCD_DATA_BIT_ONE    0b00000010
#define LCD_DATA_BIT_TWO    0b00000100
#define LCD_DATA_BIT_THREE  0b00001000
#define LCD_DATA_BIT_FOUR   0b00010000
#define LCD_DATA_BIT_FIVE   0b00100000
#define LCD_DATA_BIT_SIX    0b01000000
#define LCD_DATA_BIT_SEVEN  0b10000000
/*delays used */
#define t_1ms 1
#define t_15ms 15

/* define Commands */
#define LCD_INIT_PHASE_ONE 0x33
#define LCD_INIT_PHASE_TWO 0x32
#define LCD_INIT_PHASE_THREE 0x28
#define LCD_DISPLAY_OPTIONS 0x0E
#define LCD_CLEAR 0x01
#define LCD_INCREMENT_CURSOR 0x06
/* define number of shifts for each bit*/
#define LCD_SHIFT_ZERO  0
#define LCD_SHIFT_ONE   1
#define LCD_SHIFT_TWO   2
#define LCD_SHIFT_THREE 3
#define LCD_SHIFT_FOUR  4
#define LCD_SHIFT_FIVE  5
#define LCD_SHIFT_SIX   6
#define LCD_SHIFT_SEVEN 7

#define ROW_ONE 1
#define ROW_TWO 2
#define LCD_START_LINE_ONE 0x80
#define LCD_START_LINE_TWO 0xC0

#endif /* LCD_CONFIG_H_ */

