
/*
 * LCD_Program.c
 *
 * Created: 2/19/2019 11:13:35 AM
 *  Author: AVE-LAP-005
 */
#define F_CPU 16000000UL
//#include "../Includes/Types.h"
#include <stdint.h>
#include <stdbool.h>
#include "Types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "LCD.h"
#include "LCD_Config.h"
#define HIGH 1
#define LOW 0

#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define FIVE 5
#define SIX 6
#define SEVEN 7
#define FIVTEEN 15
#define SIXTEEN 16
#define TWINTY 20
#define THIRTY_TWO 32
/***********************LCD_init()***************************
*Parameters:
*           i/P:
*           O/P:
*           I/O:
*Return:
*Description:
*************************************************************/


void LCD_init()
{
    #ifdef FOUR_BIT_MODE



            SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
            SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
            while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA))
            { }
            while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC))
            { }
            /* portA output*/
            GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, (GPIO_PIN_2 | GPIO_PIN_3|GPIO_PIN_4));
            /* portC output*/
            GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, (GPIO_PIN_4 | GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7));

            GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_4,LOW );
            //_delay_ms(t_15ms);
            SysCtlDelay(15*160000UL);
            LCD_sendCommand(LCD_INIT_PHASE_ONE);
            LCD_sendCommand(LCD_INIT_PHASE_TWO);

            /* set function to be 4 bit mode */
            LCD_sendCommand(LCD_INIT_PHASE_THREE);

            /* shift right and i/d=0 */
            LCD_sendCommand(LCD_DISPLAY_OPTIONS);

            /* clear LCD */
                LCD_sendCommand(LCD_CLEAR);

            /* increment cursor */

                LCD_sendCommand(LCD_INCREMENT_CURSOR);




    #elif EIGHT_BIT_MODE
    #endif
}
/***********************LCD_init()***************************
*Parameters:
*           i/P:
*           O/P:
*           I/O:
*Return:
*Description:
*************************************************************/
void LCD_sendCommand(uint8 command)
{
    #ifdef FOUR_BIT_MODE
    uint8_t val=0;


    /* 1- Register select choose send command mode Rs=0 */
    //DIO_WritePin(LCD_RS,LOW);
    GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_2,LOW );
    /* 2- choose write rw =0 */
    GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_3,LOW );
    /* send High nibble */
    val=((LCD_CMD_BIT_FOUR & command)>>LCD_SHIFT_FOUR);
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,(val<<FOUR));
    val=((LCD_CMD_BIT_FIVE & command)>>LCD_SHIFT_FIVE);
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_5,(val<<FIVE));
    val=((LCD_CMD_BIT_SIX & command)>>LCD_SHIFT_SIX);
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,(val<<SIX));
    val=((LCD_CMD_BIT_SEVEN & command)>>LCD_SHIFT_SEVEN);
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_7,(val<<SEVEN));
    /* Latch Enable */
    GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_4,GPIO_PIN_4);

    SysCtlDelay(160000UL);
    GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_4,LOW);

     SysCtlDelay(160000UL);
    /* Send Low Nibble */
       val=((LCD_CMD_BIT_ZERO & command)>>LCD_SHIFT_ZERO);
       GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,(val<<FOUR));
       val=((LCD_CMD_BIT_ONE & command)>>LCD_SHIFT_ONE);
       GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_5,(val<<FIVE));
       val=((LCD_CMD_BIT_TWO & command)>>LCD_SHIFT_TWO);
       GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,(val<<SIX));
       val=((LCD_CMD_BIT_THREE & command)>>LCD_SHIFT_THREE);
       GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_7,(val<<SEVEN));
        /* Latch Enable */
       GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_4,GPIO_PIN_4);

    //_delay_ms(t_1ms);
       SysCtlDelay(160000UL);
       GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_4,LOW);

       SysCtlDelay(160000UL);

   #elif EIGHT_BIT_MODE
    #endif
}
/***********************LCD_init()***************************
*Parameters:
*           i/P:
*           O/P:
*           I/O:
*Return:
*Description:
*************************************************************/
void LCD_displayChar(uint8 Char){
    #ifdef FOUR_BIT_MODE
    uint8_t val=0;

    /* 1- Register select choose send Data mode Rs=1 */
    GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_2,GPIO_PIN_2);
    /* 2- choose write rw =0 */
    GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_3,LOW);
    /* send High nibble */
    val=((LCD_DATA_BIT_FOUR & Char)>>LCD_SHIFT_FOUR);
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,(val<<FOUR));
    val=((LCD_DATA_BIT_FIVE & Char)>>LCD_SHIFT_FIVE);
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_5,(val<<FIVE));
    val=((LCD_DATA_BIT_SIX  & Char)>>LCD_SHIFT_SIX);
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,(val<<SIX));
    val=((LCD_DATA_BIT_SEVEN & Char)>>LCD_SHIFT_SEVEN);
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_7,(val<<SEVEN));
    /* Latch Enable */
    GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_4,GPIO_PIN_4);
    //_delay_ms(t_1ms);
    SysCtlDelay(160000UL);


    GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_4,LOW);

    //_delay_ms(t_1ms);
    SysCtlDelay(160000UL);

        /* Send Low Nibble */
        val=((LCD_DATA_BIT_ZERO & Char)>>LCD_SHIFT_ZERO);
        GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,(val<<FOUR));
        val=((LCD_DATA_BIT_ONE  &  Char)>>LCD_SHIFT_ONE);
        GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_5,(val<<FIVE));
        val=((LCD_DATA_BIT_TWO  &  Char)>>LCD_SHIFT_TWO);
        GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_6,(val<<SIX));
        val=((LCD_DATA_BIT_THREE & Char)>>LCD_SHIFT_THREE);
        GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_7,(val<<SEVEN));
        /* Latch Enable */
        GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_4,GPIO_PIN_4);


    //_delay_ms(t_1ms);
    SysCtlDelay(160000UL);

        GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_4,LOW);

    //_delay_ms(t_1ms);
    SysCtlDelay(160000UL);
    #elif EIGHT_BIT_MODE
    #endif
}
/***********************LCD_init()***************************
*Parameters:
*           i/P:
*           O/P:
*           I/O:
*Return:
*Description:
*************************************************************/
void LCD_displayString(uint8* data){
        uint32_t i=0;
        /* Loop till the Finding the Null Pointer */
        while (data[i] != '\0')
        {
            LCD_displayChar(data[i]);
            i++;
        }
}
/***********************LCD_init()***************************
*Parameters:
*           i/P:
*           O/P:
*           I/O:
*Return:
*Description:
*************************************************************/
void LCD_gotoRowColumn(uint8 row,uint8 col){
    /* Choose Between the two rows then add the coulomn to define the index in the lcd 2*16 */
    switch(row){
        case ROW_ONE:LCD_sendCommand(LCD_START_LINE_ONE+col); break;
        case ROW_TWO:LCD_sendCommand(LCD_START_LINE_TWO+col); break;

    }
}
/***********************LCD_init()***************************
*Parameters:
*           i/P:
*           O/P:
*           I/O:
*Return:
*Description:
*************************************************************/
void LCD_clear(){
    /* Send Command To Clear The LCD */
    LCD_sendCommand(LCD_CLEAR);

}
/***********************LCD_init()***************************
*Parameters:
*           i/P:
*           O/P:
*           I/O:
*Return:
*Description:
*************************************************************/
void LCD_displayStringRowColumn(uint8 row,uint8 col,uint8* data){
    /* Call The two functions write string and goto  */
    LCD_gotoRowColumn(row,col);
    LCD_displayString(data);
}

