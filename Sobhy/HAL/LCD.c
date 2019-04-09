/*
 * LCD.c
 *
 *  Created on: Mar 13, 2019
 *      Author: AVE-LAP-032
 */

#include"LCD.h"
#include"Magic_Num.h"

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
    SysCtlDelay(200000);
    LCD_Send_Command (CMND2_4BITMODE);
            SysCtlDelay(200000);
            LCD_Send_Command (CMND3_4BITMODE);
            SysCtlDelay(200000);
            LCD_Send_Command (CURSOR_ON);
            SysCtlDelay(200000);
            LCD_Send_Command (CLEAR_LCD);
            SysCtlDelay(200000);

}


void LCD_Send_Command (uint8_t cmd){

 //   uint8_t J=((Get_Bit(cmd,THREE))) ;

  //  uint8_t i=((Get_Bit(cmd,THREE))<<SEVEN) ;
    GPIOPinWrite(PORT2_LCD, LCD_D4,Get_Bit(cmd,FOUR) );
    GPIOPinWrite(PORT2_LCD, LCD_D5,Get_Bit(cmd,FIVE) );
    GPIOPinWrite(PORT2_LCD, LCD_D6,Get_Bit(cmd,SIX) );
    GPIOPinWrite(PORT2_LCD, LCD_D7,Get_Bit(cmd,SEVEN));
    GPIOPinWrite(PORT1_LCD, LCD_RS,0x0);
    GPIOPinWrite(PORT1_LCD, LCD_RW,0x0);
    GPIOPinWrite(PORT1_LCD, LCD_E,LCD_E);
    SysCtlDelay(200000);
    GPIOPinWrite(PORT1_LCD, LCD_E,0x0);
    SysCtlDelay(200000);

    GPIOPinWrite(PORT2_LCD, LCD_D4,((Get_Bit(cmd,ZERO))<<FOUR) );
    GPIOPinWrite(PORT2_LCD, LCD_D5,((Get_Bit(cmd,ONE))<<FOUR  ));
    GPIOPinWrite(PORT2_LCD, LCD_D6,((Get_Bit(cmd,TWO)) <<FOUR) );
    GPIOPinWrite(PORT2_LCD, LCD_D7,((Get_Bit(cmd,THREE))<<FOUR) );
    GPIOPinWrite(PORT1_LCD, LCD_E,LCD_E);
    SysCtlDelay(200000);
    GPIOPinWrite(PORT1_LCD, LCD_E,0x0);
    SysCtlDelay(200000);
}
void LCD_Send_Data (uint8_t cmd){

    GPIOPinWrite(PORT2_LCD, LCD_D4,Get_Bit(cmd,FOUR) );
    GPIOPinWrite(PORT2_LCD, LCD_D5,Get_Bit(cmd,FIVE) );
    GPIOPinWrite(PORT2_LCD, LCD_D6,Get_Bit(cmd,SIX) );
    GPIOPinWrite(PORT2_LCD, LCD_D7,Get_Bit(cmd,SEVEN));
    GPIOPinWrite(PORT1_LCD, LCD_RS,LCD_RS);
    GPIOPinWrite(PORT1_LCD, LCD_RW,0x0);
    GPIOPinWrite(PORT1_LCD, LCD_E,LCD_E);
    SysCtlDelay(200000);
    GPIOPinWrite(PORT1_LCD, LCD_E,0x0);
    SysCtlDelay(200000);

    GPIOPinWrite(PORT2_LCD, LCD_D4,((Get_Bit(cmd,ZERO))<<FOUR) );
    GPIOPinWrite(PORT2_LCD, LCD_D5,((Get_Bit(cmd,ONE))<<FOUR  ));
    GPIOPinWrite(PORT2_LCD, LCD_D6,((Get_Bit(cmd,TWO)) <<FOUR) );
    GPIOPinWrite(PORT2_LCD, LCD_D7,((Get_Bit(cmd,THREE))<<FOUR) );
    GPIOPinWrite(PORT1_LCD, LCD_E,LCD_E);
    SysCtlDelay(200000);
    GPIOPinWrite(PORT1_LCD, LCD_E,0x0);
    SysCtlDelay(200000);
}

void LCD_Send_String (uint8_t * data)
{
    uint8_t i=0;
    while(data[i] !=0)
        {
             LCD_Send_Data (data[i]);
             i++;
        }
}

void LCD_gotoRowColumn (uint8_t row,uint8_t col){

uint8_t arr[]={FIRST_ROW,SECOND_ROW};

return(LCD_Send_Command(arr[row-ONE]+col));

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





