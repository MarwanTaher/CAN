#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "LCD.h"
#include "Magic_Num.h"



/*LCD_INIT */
/* Parameters : N/A */
/* I/p : N/A */
/* O/p : N/A */
/* Return : void */
/* Function that initiate LCD   */
void LCD_INIT()
{

      /*Enable the GPIO port that is used for the on-board LED.*/
      SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
      /*Check if the peripheral access is enabled.*/
      while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA))
      {
      }
      /* Enable the GPIO port that is used for the on-board LED.*/
      SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
      /* Check if the peripheral access is enabled.*/
      while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC))
      {
      }

      /* Enable the GPIO pin for the LED (PF3).  Set the direction as output, and*/
      /* enable the GPIO pin for digital function.*/

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


/*LCD_Send_Command */
/* Parameters : uint8_t cmd */
/* I/p :uint8_t cmd */
/* O/p : N/A */
/* Return : void */
/* Function that command for LCD  */
void LCD_Send_Command (uint8_t cmd){

    GPIOPinWrite(PORT2_LCD, LCD_D4,Get_Bit(cmd,FOUR) );
    GPIOPinWrite(PORT2_LCD, LCD_D5,Get_Bit(cmd,FIVE) );
    GPIOPinWrite(PORT2_LCD, LCD_D6,Get_Bit(cmd,SIX) );
    GPIOPinWrite(PORT2_LCD, LCD_D7,Get_Bit(cmd,SEVEN));
    GPIOPinWrite(PORT1_LCD, LCD_RS,0x0);
    GPIOPinWrite(PORT1_LCD, LCD_RW,0x0);
    GPIOPinWrite(PORT1_LCD, LCD_E,LCD_E);
    SysCtlDelay(15000);
    GPIOPinWrite(PORT1_LCD, LCD_E,0x0);
    SysCtlDelay(15000);

    GPIOPinWrite(PORT2_LCD, LCD_D4,((Get_Bit(cmd,ZERO))<<FOUR) );
    GPIOPinWrite(PORT2_LCD, LCD_D5,((Get_Bit(cmd,ONE))<<FOUR  ));
    GPIOPinWrite(PORT2_LCD, LCD_D6,((Get_Bit(cmd,TWO)) <<FOUR) );
    GPIOPinWrite(PORT2_LCD, LCD_D7,((Get_Bit(cmd,THREE))<<FOUR) );
    GPIOPinWrite(PORT1_LCD, LCD_E,LCD_E);
    SysCtlDelay(15000);
    GPIOPinWrite(PORT1_LCD, LCD_E,0x0);
    SysCtlDelay(15000);
}

/*LCD_Send_Data */
/* Parameters : uint8_t cmd */
/* I/p :uint8_t cmd */
/* O/p : N/A */
/* Return : void */
/* Function that send data for LCD  */
void LCD_Send_Data (uint8_t cmd){

    GPIOPinWrite(PORT2_LCD, LCD_D4,Get_Bit(cmd,FOUR) );
    GPIOPinWrite(PORT2_LCD, LCD_D5,Get_Bit(cmd,FIVE) );
    GPIOPinWrite(PORT2_LCD, LCD_D6,Get_Bit(cmd,SIX) );
    GPIOPinWrite(PORT2_LCD, LCD_D7,Get_Bit(cmd,SEVEN));
    GPIOPinWrite(PORT1_LCD, LCD_RS,LCD_RS);
    GPIOPinWrite(PORT1_LCD, LCD_RW,0x0);
    GPIOPinWrite(PORT1_LCD, LCD_E,LCD_E);
    SysCtlDelay(15000);
    GPIOPinWrite(PORT1_LCD, LCD_E,0x0);
    SysCtlDelay(15000);
    GPIOPinWrite(PORT2_LCD, LCD_D4,((Get_Bit(cmd,ZERO))<<FOUR) );
    GPIOPinWrite(PORT2_LCD, LCD_D5,((Get_Bit(cmd,ONE))<<FOUR  ));
    GPIOPinWrite(PORT2_LCD, LCD_D6,((Get_Bit(cmd,TWO)) <<FOUR) );
    GPIOPinWrite(PORT2_LCD, LCD_D7,((Get_Bit(cmd,THREE))<<FOUR) );
    GPIOPinWrite(PORT1_LCD, LCD_E,LCD_E);
    SysCtlDelay(15000);
    GPIOPinWrite(PORT1_LCD, LCD_E,0x0);
    SysCtlDelay(15000);
}


/*LCD_displayString */
/* Parameters : uint8_t* */
/* I/p : uint8_t* */
/* O/p : N/A */
/* Return : void */
/* Function that SET FLAG BY CALL THIS FUN INSIDE ISR */
void LCD_displayString(uint8_t* STRING){

    while(*STRING != ('\0' )){
    LCD_Send_Data(*STRING);
    *STRING++;
}
}

/*LCD_DISPLAY FOR BTN 2  */
/* Parameters : N/A */
/* I/p : N/A */
/* O/p : N/A */
/* Return : void */
/* Function that display string on LCD  */
void LCD_DISPLAY2(uint8_t COUNTER)
{
       LCD_Send_Command(0x80);
       LCD_displayString("COUNTER2= ");
       LCD_Send_Data(COUNTER+48);/*ascii zero */
}

/*LCD_DISPLAY FOR BTN1  */
/* Parameters : N/A */
/* I/p : N/A */
/* O/p : N/A */
/* Return : void */
/* Function that display string on LCD  */
void LCD_DISPLAY1(uint8_t COUNTER)
{
       LCD_Send_Command(0xC0);
       LCD_displayString("COUNTER1= ");/*ascii zero */
       LCD_Send_Data(COUNTER+48);/*ascii zero */

}

void LCD(void)
{
       LCD_Send_Command(0xC0);
       LCD_displayString("COUNTER1= ");/*ascii zero */

}

