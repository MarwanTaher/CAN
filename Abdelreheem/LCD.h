

/*
 * LCD.h
 *
 * Created: 2/19/2019 11:14:29 AM
 *  Author: AVE-LAP-005
 */


#ifndef LCD_H_
#define LCD_H_

/* LCD APIS */
void LCD_init();
void LCD_sendCommand(uint8 command);
void LCD_displayChar(uint8 Char);
void LCD_displayString(uint8* data);
void LCD_displayStringRowColumn(uint8 row,uint8 col,uint8* data);
void LCD_clear();
void LCD_gotoRowColumn(uint8 row,uint8 col);



#endif /* LCD_H_ */

