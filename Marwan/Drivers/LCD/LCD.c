#include"inc/LCD.h"
#include "../../FreeRTOS/Includes/FreeRTOS.h"
#include "../../FreeRTOS/Includes/task.h"
/*********************************************************************************
 *
 * Function: LCD_init
 *
 * @param: void
 * @return: void
 *
 * Description: function to initialize the pins of the LCD as output and gives the LCD
 * its initial commands
 *
 ********************************************************************************/
void LCD_init(){

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA));
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC));

    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,GPIO_PIN_2 |GPIO_PIN_3|GPIO_PIN_4);
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE,GPIO_PIN_4 |GPIO_PIN_5|GPIO_PIN_6 | GPIO_PIN_7);



LCD_sendCommand(CMD_LCD4BIT33);
vTaskDelay(1);
LCD_sendCommand(CMD_LCD4BIT32);
vTaskDelay(1);
LCD_sendCommand(CMD_LCD_2_LINES_5X7);
vTaskDelay(1);
LCD_sendCommand(CMD_CURSOR_ON);
vTaskDelay(1);
LCD_sendCommand(CMD_RESET);
vTaskDelay(1);
LCD_sendCommand(CMD_SHIFT_DISPLAY_LEFT);
vTaskDelay(1);
LCD_sendCommand(0x80);
}

/*********************************************************************************
 *
 * Function: LCD_sendCommand
 *
 * @param: 
		input : cmd , the command given to the LCD 
 * @return: void
 *
 * Description: function to send commands to the LCD
 *
 *
 ********************************************************************************/
void LCD_sendCommand(uint8_t cmd){

/*    Write The MOST significant bits of the command in the 4 bits of the LCD	*/


GPIOPinWrite(GPIO_PORTC_BASE,LCD_D4, (Get_Bit(cmd,BIT4) ));

GPIOPinWrite(GPIO_PORTC_BASE,LCD_D5, (Get_Bit(cmd,BIT5) ));

GPIOPinWrite(GPIO_PORTC_BASE,LCD_D6, (Get_Bit(cmd,BIT6) ));

GPIOPinWrite(GPIO_PORTC_BASE,LCD_D7, (Get_Bit(cmd,BIT7) ));


GPIOPinWrite(GPIO_PORTA_BASE,LCD_RS | LCD_RW |LCD_EN ,0|0|LCD_EN);
vTaskDelay(5);
GPIOPinWrite(GPIO_PORTA_BASE,LCD_EN ,0);
vTaskDelay(5);



GPIOPinWrite(GPIO_PORTC_BASE,LCD_D4, (Get_Bit(cmd,BIT0) <<4));

GPIOPinWrite(GPIO_PORTC_BASE,LCD_D5, (Get_Bit(cmd,BIT1)  <<4));
GPIOPinWrite(GPIO_PORTC_BASE,LCD_D6, (Get_Bit(cmd,BIT2)  <<4));
GPIOPinWrite(GPIO_PORTC_BASE,LCD_D7, (Get_Bit(cmd,BIT3)  <<4));

GPIOPinWrite(GPIO_PORTA_BASE,LCD_EN ,LCD_EN);
vTaskDelay(5);
GPIOPinWrite(GPIO_PORTA_BASE,LCD_EN ,0);
}


/*********************************************************************************
 *
 * Function: LCD_displayChar
 *
 * @param: 
		input : c , the character given to the LCD 
 * @return: void
 *
 * Description: function to print a character on the LCD
 *
 *
 ********************************************************************************/
void LCD_displayChar(uint8_t c){
	
/*    Write The MOST significant bits of the command in the 4 bits of the LCD	*/

    GPIOPinWrite(GPIO_PORTC_BASE,LCD_D4, (Get_Bit(c,BIT4)));
    GPIOPinWrite(GPIO_PORTC_BASE,LCD_D5, (Get_Bit(c,BIT5)));
    GPIOPinWrite(GPIO_PORTC_BASE,LCD_D6, (Get_Bit(c,BIT6)));
    GPIOPinWrite(GPIO_PORTC_BASE,LCD_D7, (Get_Bit(c,BIT7)));

    GPIOPinWrite(GPIO_PORTA_BASE,LCD_RS | LCD_RW |LCD_EN ,LCD_RS|0|LCD_EN);

    vTaskDelay(5);
    GPIOPinWrite(GPIO_PORTA_BASE,LCD_EN ,0);

    vTaskDelay(5);

/*    Write The LEAST significant bits of the command in the 4 bits of the LCD	*/

GPIOPinWrite(GPIO_PORTC_BASE,LCD_D4, (Get_Bit(c,BIT0) <<4));
GPIOPinWrite(GPIO_PORTC_BASE,LCD_D5, (Get_Bit(c,BIT1) <<4));
GPIOPinWrite(GPIO_PORTC_BASE,LCD_D6, (Get_Bit(c,BIT2) <<4));
GPIOPinWrite(GPIO_PORTC_BASE,LCD_D7, (Get_Bit(c,BIT3) <<4));



GPIOPinWrite(GPIO_PORTA_BASE,LCD_RS | LCD_RW |LCD_EN ,LCD_RS|0|LCD_EN);
vTaskDelay(5);
    GPIOPinWrite(GPIO_PORTA_BASE,LCD_EN ,0);
}	


/************************************************************************/
/* Function: LCD Display String                                         */
/* @param: Str[], array of strings                                      */
/* return: void                                                         */
/* Description: function display String on LCD                          */
/************************************************************************/
void LCD_displayString(uint8_t* Str)
{
        uint8_t i = NUM_0;
        while(Str[i] != NULL_CHAR)
        {
            LCD_displayChar(Str[i]);
            i++;
        }
}



/************************************************************************/
/* Function: LCD Clear                                                  */
/* @param: void                                                         */
/* return: void                                                         */
/* Description: function clears LCD                                     */
/************************************************************************/
void LCD_Clear(void)
{
    LCD_sendCommand(LCD_CLEAR);
}


uint8_t Random_num(void)
{
    uint8_t rand1;
    rand1 = rand() % 10;
    return rand1;
}



void LCD_intgerToString(int data)
{
   uint8_t buff[16]; /* String to hold the ascii result */
  // itoa(data,buff,10); /* 10 for decimal */
   LCD_displayString(buff);
}


void LCD_gotoRowColumn(uint8_t ROW,uint8_t COL)
{
    if (ROW == LCD_ROW1) /* goto row 1 */
        {
            LCD_sendCommand(LCD_CURSOR_LINE_ONE);
            uint8_t i;
            for (i = NUM_0 ; i<COL; i++)
            {
                LCD_sendCommand(LCD_SHIFT_CURSOR_RIGHT);
            }
        }
        else if(ROW == LCD_ROW2)
        {
            LCD_sendCommand(LCD_CURSOR_LINE_TWO);
            uint8_t i;
            for (i = NUM_0; i<COL; i++)
            {
                LCD_sendCommand(LCD_SHIFT_CURSOR_RIGHT);
            }
        }
        else
        {
            LCD_sendCommand(LCD_CURSOR_LINE_ONE);
            uint8_t i;
            for (i = NUM_0; i<COL; i++)
            {
                LCD_sendCommand(LCD_SHIFT_CURSOR_RIGHT);
            }
        }
}

void LCD_Display_NUM(uint8_t Num)
{
    if (Num <= 9)
    {
        LCD_displayChar((Num)+48);
    }
    else if (Num > 9 && Num <= 99)
    {
        LCD_gotoRowColumn(0, 0);
        LCD_displayChar((Num / 10) + 48);
        LCD_gotoRowColumn(0, 1);
        LCD_displayChar((Num % 10) + 48);

    }
    else if (Num > 99)
    {
        LCD_gotoRowColumn(0, 0);
        LCD_displayChar((Num / 100) + 48);
        LCD_gotoRowColumn(0, 1);
        LCD_displayChar(((Num / 10) % 10) + 48);
        LCD_gotoRowColumn(0, 2);
        LCD_displayChar((Num % 10) + 48);
    }
}
