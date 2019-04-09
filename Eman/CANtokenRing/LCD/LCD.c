/*
 * LCD.c
 *
 *  Created on: Mar 13, 2019
 *      Author: AVE-LABS-50
 */

#include"LCD.h"
#include"Config.h"

/************************************************************************/
/* FUNCTION NAME: LCD_INIT                                              */
/* @Param: void                                                         */
/* return: void                                                         */
/* FUNCTION Description: Initialization of LCD                          */
/************************************************************************/
void LCD_INIT()
{

    //
    // Enable the GPIO port that is used for the on-board LED.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    //
    // Check if the peripheral access is enabled.
    //
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA))
    {
    }
    //
      // Enable the GPIO port that is used for the on-board LED.
      //
      SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
      //
      // Check if the peripheral access is enabled.
      //
      while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC))
      {
      }
    //
    // Enable the GPIO pin for the LED (PF3).  Set the direction as output, and
    // enable the GPIO pin for digital function.
    //
    GPIOPinTypeGPIOOutput(PORT1_LCD,LCD_RS|LCD_RW|LCD_E);
    GPIOPinTypeGPIOOutput(PORT2_LCD,LCD_D4|LCD_D5|LCD_D6|LCD_D7);

    LCD_Send_Command (CMND1_4BITMODE);
    SysCtlDelay(8334);
    LCD_Send_Command (CMND2_4BITMODE);
    SysCtlDelay(8334);
    LCD_Send_Command (CMND3_4BITMODE);
    SysCtlDelay(8334);
    LCD_Send_Command (CURSOR_ON);
    SysCtlDelay(8334);
    LCD_Send_Command (CLEAR_LCD);
    SysCtlDelay(8334);


    //

    // Loop forever.
    //

}

/************************************************************************/
/* FUNCTION NAME: LCD_sendCommand                                       */
/* @Param: Command                                                      */
/* return: void                                                         */
/* FUNCTION Description: Sending LCD Commands                           */
/************************************************************************/
void LCD_Send_Command (uint8_t cmd){

    GPIOPinWrite(PORT2_LCD, LCD_D4,Get_Bit(cmd,FOUR) );
    GPIOPinWrite(PORT2_LCD, LCD_D5,Get_Bit(cmd,FIVE) );
    GPIOPinWrite(PORT2_LCD, LCD_D6,Get_Bit(cmd,SIX) );
    GPIOPinWrite(PORT2_LCD, LCD_D7,Get_Bit(cmd,SEVEN));
    GPIOPinWrite(PORT1_LCD, LCD_RS,0x0);
    GPIOPinWrite(PORT1_LCD, LCD_RW,0x0);
    GPIOPinWrite(PORT1_LCD, LCD_E,LCD_E);
    SysCtlDelay(8334);
    GPIOPinWrite(PORT1_LCD, LCD_E,0x0);
    SysCtlDelay(8334);

    GPIOPinWrite(PORT2_LCD, LCD_D4,((Get_Bit(cmd,ZERO))<<FOUR) );
    GPIOPinWrite(PORT2_LCD, LCD_D5,((Get_Bit(cmd,ONE))<<FOUR  ));
    GPIOPinWrite(PORT2_LCD, LCD_D6,((Get_Bit(cmd,TWO)) <<FOUR) );
    GPIOPinWrite(PORT2_LCD, LCD_D7,((Get_Bit(cmd,THREE))<<FOUR) );
    GPIOPinWrite(PORT1_LCD, LCD_E,LCD_E);
    SysCtlDelay(8334);
    GPIOPinWrite(PORT1_LCD, LCD_E,0x0);
    SysCtlDelay(8334);
}


/************************************************************************/
/* FUNCTION NAME: LCD_Send_Data                                         */
/* @Param: Character                                                    */
/* return: void                                                         */
/* FUNCTION Description: Display Character on LCD                       */
/************************************************************************/
void LCD_Send_Data (uint8_t cmd){

    GPIOPinWrite(PORT2_LCD, LCD_D4,Get_Bit(cmd,FOUR) );
    GPIOPinWrite(PORT2_LCD, LCD_D5,Get_Bit(cmd,FIVE) );
    GPIOPinWrite(PORT2_LCD, LCD_D6,Get_Bit(cmd,SIX) );
    GPIOPinWrite(PORT2_LCD, LCD_D7,Get_Bit(cmd,SEVEN));
    GPIOPinWrite(PORT1_LCD, LCD_RS,LCD_RS);
    GPIOPinWrite(PORT1_LCD, LCD_RW,0x0);
    GPIOPinWrite(PORT1_LCD, LCD_E,LCD_E);
    SysCtlDelay(8334);
    GPIOPinWrite(PORT1_LCD, LCD_E,0x0);
    SysCtlDelay(8334);

    GPIOPinWrite(PORT2_LCD, LCD_D4,((Get_Bit(cmd,ZERO))<<FOUR) );
    GPIOPinWrite(PORT2_LCD, LCD_D5,((Get_Bit(cmd,ONE))<<FOUR  ));
    GPIOPinWrite(PORT2_LCD, LCD_D6,((Get_Bit(cmd,TWO)) <<FOUR) );
    GPIOPinWrite(PORT2_LCD, LCD_D7,((Get_Bit(cmd,THREE))<<FOUR) );
    GPIOPinWrite(PORT1_LCD, LCD_E,LCD_E);
    SysCtlDelay(8334);
    GPIOPinWrite(PORT1_LCD, LCD_E,0x0);
    SysCtlDelay(8334);
}

/************************************************************************/
/* FUNCTION NAME: LCD_displayString                                     */
/* @Param: Array of String and it's size                                */
/* return: void                                                         */
/* FUNCTION Description: Display String on LCD                          */
/************************************************************************/
void LCD_displayString(const uint8_t* ARR, uint8_t SIZE)
{
    uint8_t i;
    for(i=ZERO ; i < SIZE; i++)
    {
        LCD_Send_Data(ARR[i]);
        SysCtlDelay(8334);

    }
}
/************************************************************************/
/* FUNCTION NAME: LCD_gotoRowColumn                                     */
/* @Param: the row and column of LCD cell                               */
/* return: void                                                         */
/* FUNCTION Description: go to certain the row, column on LCD           */
/************************************************************************/
void LCD_gotoRowColumn(uint8_t line, uint8_t digit)
{
    if ((digit >= ZERO) && (digit < SIXTEN))
    {
        switch(line)
        {
            case FirstLine : LCD_Send_Command(FirstLineADD + digit); break;
            case SecondLine : LCD_Send_Command(SecondLineADD + digit); break;
            default:  break;
        }
    }

}

/*********************************************************************************/
/* FUNCTION NAME: PrintDecimalNum                                                */
/* @Param: Decimal Number                                                        */
/* return: void                                                                  */
/* FUNCTION Description: print Decimal Number consists of more than 1 digit      */
/*********************************************************************************/
void PrintDecimalNum(uint16_t NUM)
{
    uint8_t i=NUM_0 ,Digit ,Num[NUM_6] ;

        while( NUM != NUM_0 )
        {
            Num[i++] =(NUM % NUM_10);
            NUM = NUM/NUM_10;
        }
        Num[i++]=(NUM % NUM_10);
        Digit = i -1 ;

        for (i = NUM_0 ;i<Digit;i++)
        {
            LCD_Send_Data((Num[Digit-i-1]+ZeroAscii));
        }
}

