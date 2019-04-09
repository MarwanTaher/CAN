/*
 * Lcd.c
 *
 * Created: 2/19/2019 12:23:46 PM
 *  Author: AVE-LAP-44
 */ 
#include "lcd.h"
#if(LCD_TYPE==LCD_4BIT_TYPE)
/************************************************************************************
* Function Name:        LCD_init
* Parameters (in):      void
* Parameters (inout):   LCD_RS ,LCD_RW,LCD_E,LCD_D4,LCD_D5,LCD_D6,LCD_D7 
* Parameters (out):     void
* Return value:         void
* Description:          Function that initialize the LCD 
************************************************************************************/
uint8 LCD_ready=FALSE;
void LCD_init()
{

        SysCtlPeripheralEnable(LCD_RS_clk);
        SysCtlPeripheralEnable(LCD_RW_clk);
        SysCtlPeripheralEnable(LCD_E_clk);
        SysCtlPeripheralEnable(LCD_D4_clk);
        SysCtlPeripheralEnable(LCD_D5_clk);
        SysCtlPeripheralEnable(LCD_D6_clk);
        SysCtlPeripheralEnable(LCD_D7_clk);

        /* Set LCD_RS OUTPUT */
        GPIOPinTypeGPIOOutput(LCD_RS_PORT,LCD_RS_PIN);
        /* Set LCD_RW OUTPUT */
        GPIOPinTypeGPIOOutput(LCD_RW_PORT,LCD_RW_PIN);
        /* Set LCD_E OUTPUT */
        GPIOPinTypeGPIOOutput(LCD_E_PORT,LCD_E_PIN);
        /* Set LCD_D4 OUTPUT */
        GPIOPinTypeGPIOOutput(LCD_D4_PORT,LCD_D4_PIN);
        /* Set LCD_D5 OUTPUT */
        GPIOPinTypeGPIOOutput(LCD_D5_PORT,LCD_D5_PIN);
        /* Set LCD_D6 OUTPUT */
        GPIOPinTypeGPIOOutput(LCD_D6_PORT,LCD_D6_PIN);
        /* Set LCD_D7 OUTPUT */
        GPIOPinTypeGPIOOutput(LCD_D7_PORT,LCD_D7_PIN);
        /* Disable LCD*/
        GPIOPinWrite (LCD_E_PORT, LCD_E_PIN, LOW);
        /* LCD_RS =0, Command*/
        GPIOPinWrite (LCD_RS_PORT, LCD_RS_PIN, LOW);
        /* LCD_Rw =0, Write */
        GPIOPinWrite (LCD_RW_PORT, LCD_RW_PIN, LOW);
        /* Disable LCD*/
        GPIOPinWrite (LCD_D4_PORT, LCD_D4_PIN, LOW);
        /* LCD_RS =0, Command*/
        GPIOPinWrite (LCD_D5_PORT, LCD_D5_PIN, LOW);
        /* LCD_Rw =0, Write */
        GPIOPinWrite (LCD_D6_PORT, LCD_D6_PIN, LOW);

        GPIOPinWrite (LCD_D7_PORT, LCD_D7_PIN, LOW);


	
    vTaskDelay( NUM_30 / portTICK_RATE_MS );              /* Delay 30m second until the power steady */
    LCD_sendCommand(LCD_WAKEUP);                          /* Send command to wake up #1 */
	vTaskDelay( NUM_10 / portTICK_RATE_MS );              /* Must delay more than 5m second */
	LCD_sendCommand(LCD_WAKEUP);                          /* Send command to wake up #2 */
	vTaskDelay( NUM_5 / portTICK_RATE_MS );               /* Must delay more than 1m second */
	LCD_sendCommand(LCD_WAKEUP);                          /* Send command to wake up #3 */
	vTaskDelay( NUM_5 / portTICK_RATE_MS );               /* Must delay more than 1m second */
	LCD_sendCommand(LCD_HOME);                            /* Send Home (0x02) command which initializes LCD 16x2 in 4-bit mode */
	LCD_sendCommand(LCD_4BIT_MODE);                       /* Send 4BIT_MODE (0x28) command which configures LCD in 2-line, 4-bit mode and 5x8 dots */
	LCD_sendCommand(LCD_DISPLAY_ON);      /* SEND LCD_DISPLAY_ON(0X0F) display on,CURSOR_ON*/
	LCD_sendCommand(LCD_CLEAR);           /* Clear Screen */
	LCD_ready=TRUE;

}
/************************************************************************************
* Function Name:       LCD_sendCommand
* Parameters (in):     uint8 command
* Parameters (inout):  LCD_RS ,LCD_RW,LCD_E,LCD_D4,LCD_D5,LCD_D6,LCD_D7
* Parameters (out):    void
* Return value:        void
* Description:         Function that send acommand to the LCD
************************************************************************************/
void LCD_sendCommand(uint32 command)
{
	static uint32 LCD_D4_value;
	static uint32 LCD_D5_value;
	static uint32 LCD_D6_value;
	static uint32 LCD_D7_value;
	/* For 4_bit_Mode we have to divide the uint8 to 2 (4bits) and send the most 4bits then send the least 4bits
	 * for example :command = 0x52 which is 0b 0101 0010
	 * so we have to send 0b0101 (0x5) first then send 0b0010 (0x2)
	 * first  send   LCD_D7_value =0 ,LCD_D6_value=1 LCD_D5_value=0  LCD_D4_value=1
	 * second send   LCD_D7_value =0 ,LCD_D6_value=0 LCD_D5_value=1  LCD_D4_value=0
	 *  sequence : 1- Make E 0 RS O (Command) RW 0 (write) 
	              2- Get #1 LCD_D4:D7_value using Get_Bit
	              3- Write Data Pins with Values
				  4- Enable
				  5- delay
				  6- disable
				  7- Get #2 LCD_D4:D7_value using Get_Bit
				  8- Write Data Pins with Values
				  9- Enable
				  10-delay
				  11-disable*/
	 /* Disable LCD*/
	GPIOPinWrite (LCD_E_PORT, LCD_E_PIN, LOW);
	/* LCD_RS =0, Command*/
    GPIOPinWrite (LCD_RS_PORT, LCD_RS_PIN, LOW);
    /* LCD_Rw =0, Write */
    GPIOPinWrite (LCD_RW_PORT, LCD_RW_PIN, LOW);


	LCD_D4_value=Get_Bit(command,BIT4);     /* Get #1 LCD_D4:D7_value using Get_Bit*/
	LCD_D5_value=Get_Bit(command,BIT5);
	LCD_D6_value=Get_Bit(command,BIT6);
	LCD_D7_value=Get_Bit(command,BIT7);

    /* Write Data Pins with Values */
	if(NUM_1==LCD_D4_value)
	    {
	        GPIOPinWrite (LCD_D4_PORT, LCD_D4_PIN, LCD_D4_PIN);
	    }
	    else
	    {
	        GPIOPinWrite (LCD_D4_PORT, LCD_D4_PIN, LOW);
	    }
	    if(NUM_1==LCD_D5_value)
	       {
	           GPIOPinWrite (LCD_D5_PORT, LCD_D5_PIN, LCD_D5_PIN);
	       }
	   else
	       {
	           GPIOPinWrite (LCD_D5_PORT, LCD_D5_PIN, LOW);
	       }
	    if(NUM_1==LCD_D6_value)
	          {
	              GPIOPinWrite (LCD_D6_PORT, LCD_D6_PIN, LCD_D6_PIN);
	          }
	    else
	          {
	              GPIOPinWrite (LCD_D6_PORT, LCD_D6_PIN, LOW);
	          }
	    if(NUM_1==LCD_D7_value)
	              {
	                  GPIOPinWrite (LCD_D7_PORT, LCD_D7_PIN, LCD_D7_PIN);
	              }
	   else
	              {
	                  GPIOPinWrite (LCD_D7_PORT, LCD_D7_PIN, LOW);
	              }

	GPIOPinWrite (LCD_E_PORT, LCD_E_PIN, LCD_E_PIN);              /* Enable */
	vTaskDelay( NUM_2 / portTICK_RATE_MS );                      /* delay */
	GPIOPinWrite (LCD_E_PORT, LCD_E_PIN, LOW);                                     /* disable */
	LCD_D4_value=Get_Bit(command,BIT0);                         /* Get #2 LCD_D4:D7_value using Get_Bit */
	LCD_D5_value=Get_Bit(command,BIT1);
	LCD_D6_value=Get_Bit(command,BIT2);
	LCD_D7_value=Get_Bit(command,BIT3);
    if(NUM_1==LCD_D4_value)
    {
        GPIOPinWrite (LCD_D4_PORT, LCD_D4_PIN, LCD_D4_PIN);
    }
    else
    {
        GPIOPinWrite (LCD_D4_PORT, LCD_D4_PIN, LOW);
    }
    if(NUM_1==LCD_D5_value)
       {
           GPIOPinWrite (LCD_D5_PORT, LCD_D5_PIN, LCD_D5_PIN);
       }
   else
       {
           GPIOPinWrite (LCD_D5_PORT, LCD_D5_PIN, LOW);
       }
    if(NUM_1==LCD_D6_value)
          {
              GPIOPinWrite (LCD_D6_PORT, LCD_D6_PIN, LCD_D6_PIN);
          }
    else
          {
              GPIOPinWrite (LCD_D6_PORT, LCD_D6_PIN, LOW);
          }
    if(NUM_1==LCD_D7_value)
              {
                  GPIOPinWrite (LCD_D7_PORT, LCD_D7_PIN, LCD_D7_PIN);
              }
   else
              {
                  GPIOPinWrite (LCD_D7_PORT, LCD_D7_PIN, LOW);
              }
	/* Write Data Pins with Values */

	GPIOPinWrite (LCD_E_PORT, LCD_E_PIN, LCD_E_PIN);              /* Enable */
	vTaskDelay( NUM_2 / portTICK_RATE_MS );               /* delay */
	GPIOPinWrite (LCD_E_PORT, LCD_E_PIN, LOW);	           /* disable */
}


/************************************************************************************
* Function Name:       LCD_displayChar
* Parameters (in):     uint8 data
* Parameters (inout):  LCD_RS ,LCD_RW,LCD_E,LCD_D4,LCD_D5,LCD_D6,LCD_D7 
* Parameters (out):    void
* Return value:        void
* Description:         Function that display a char on the LCD
************************************************************************************/
void LCD_displayChar(uint8 data)
{
    static uint8 LCD_D4_value;
    static uint8 LCD_D5_value;
    static uint8 LCD_D6_value;
    static uint8 LCD_D7_value;
	/* For 4_bit_Mode we have to divide the uint8 to 2 (4bits) and send the most 4bits then send the least 4bits
	   for example :data = 0x52 which is 0b 0101 0010
	   so we have to send 0b0101 (0x5) first then send 0b0010 (0x2)
	   first  send   LCD_D7_value =0 ,LCD_D6_value=1 LCD_D5_value=0  LCD_D4_value=1
	   second send   LCD_D7_value =0 ,LCD_D6_value=0 LCD_D5_value=1  LCD_D4_value=0
	   sequence : 1- Make E 0 RS 1 (data) RW 0 (write) 
	              2- Get #1 LCD_D4:D7_value using Get_Bit
	              3- Write Data Pins with Values
				  4- Enable
				  5- delay
				  6- disable
				  7- Get #2 LCD_D4:D7_value using Get_Bit
				  8- Write Data Pins with Values
				  9- Enable
				  10-delay
				  11-disable*/

	/* Disable LCD*/
	GPIOPinWrite (LCD_E_PORT, LCD_E_PIN, LOW);
	/* LCD_RS =1, Data*/
	GPIOPinWrite (LCD_RS_PORT, LCD_RS_PIN, LCD_RS_PIN);
	/* LCD_Rw =0, Write */
	GPIOPinWrite (LCD_RW_PORT, LCD_RW_PIN, LOW);

	LCD_D4_value=Get_Bit(data,BIT4);         /* Get #1 LCD_D4:D7_value using Get_Bit */
	LCD_D5_value=Get_Bit(data,BIT5);
	LCD_D6_value=Get_Bit(data,BIT6);
	LCD_D7_value=Get_Bit(data,BIT7);

	/* Write Data Pins with Values */
	if(NUM_1==LCD_D4_value)
	    {
	        GPIOPinWrite (LCD_D4_PORT, LCD_D4_PIN, LCD_D4_PIN);
	    }
	    else
	    {
	        GPIOPinWrite (LCD_D4_PORT, LCD_D4_PIN, LOW);
	    }
	    if(NUM_1==LCD_D5_value)
	       {
	           GPIOPinWrite (LCD_D5_PORT, LCD_D5_PIN, LCD_D5_PIN);
	       }
	   else
	       {
	           GPIOPinWrite (LCD_D5_PORT, LCD_D5_PIN, LOW);
	       }
	    if(NUM_1==LCD_D6_value)
	          {
	              GPIOPinWrite (LCD_D6_PORT, LCD_D6_PIN, LCD_D6_PIN);
	          }
	    else
	          {
	              GPIOPinWrite (LCD_D6_PORT, LCD_D6_PIN, LOW);
	          }
	    if(NUM_1==LCD_D7_value)
	              {
	                  GPIOPinWrite (LCD_D7_PORT, LCD_D7_PIN, LCD_D7_PIN);
	              }
	   else
	              {
	                  GPIOPinWrite (LCD_D7_PORT, LCD_D7_PIN, LOW);
	              }

    GPIOPinWrite (LCD_E_PORT, LCD_E_PIN, LCD_E_PIN);              /* Enable */
    vTaskDelay( NUM_2 / portTICK_RATE_MS );                      /* delay */
    GPIOPinWrite (LCD_E_PORT, LCD_E_PIN, LOW);                                     /* disable */
        LCD_D4_value=Get_Bit(data,BIT0);                         /* Get #2 LCD_D4:D7_value using Get_Bit */
        LCD_D5_value=Get_Bit(data,BIT1);
        LCD_D6_value=Get_Bit(data,BIT2);
        LCD_D7_value=Get_Bit(data,BIT3);
        /* Write Data Pins with Values */
        if(NUM_1==LCD_D4_value)
            {
                GPIOPinWrite (LCD_D4_PORT, LCD_D4_PIN, LCD_D4_PIN);
            }
            else
            {
                GPIOPinWrite (LCD_D4_PORT, LCD_D4_PIN, LOW);
            }
            if(NUM_1==LCD_D5_value)
               {
                   GPIOPinWrite (LCD_D5_PORT, LCD_D5_PIN, LCD_D5_PIN);
               }
           else
               {
                   GPIOPinWrite (LCD_D5_PORT, LCD_D5_PIN, LOW);
               }
            if(NUM_1==LCD_D6_value)
                  {
                      GPIOPinWrite (LCD_D6_PORT, LCD_D6_PIN, LCD_D6_PIN);
                  }
            else
                  {
                      GPIOPinWrite (LCD_D6_PORT, LCD_D6_PIN, LOW);
                  }
            if(NUM_1==LCD_D7_value)
                      {
                          GPIOPinWrite (LCD_D7_PORT, LCD_D7_PIN, LCD_D7_PIN);
                      }
           else
                      {
                          GPIOPinWrite (LCD_D7_PORT, LCD_D7_PIN, LOW);
                      }
        GPIOPinWrite (LCD_E_PORT, LCD_E_PIN, LCD_E_PIN);              /* Enable */
        vTaskDelay( NUM_2 / portTICK_RATE_MS );               /* delay */
        GPIOPinWrite (LCD_E_PORT, LCD_E_PIN, LOW);               /* disable */

}

/************************************************************************************
* Function Name:         LCD_displayString
* Parameters (in):       uint8 lcd_string[]   String
*                        uint8 string_size    string_size
* Parameters (inout):    void
* Parameters (out):      void
* Return value:          void
* Description:           Function that display a string
************************************************************************************/
void LCD_displayString(uint8 lcd_string[],uint8 string_size)
{
	uint8 string_index =0;                         
	while(--string_size)                            /*  decrement size for every print*/
	{
	    if(lcd_string[string_index]=='\0')
	    {
	        break;
	    }
		LCD_displayChar(lcd_string[string_index]);  /* print char with the specif index */   
		string_index++;
	};
	
		
}

/************************************************************************************
* Function Name:        LCD_gotoRowColumn
* Parameters (in):      uint8 row ,uint8 column
* Parameters (inout):   void
* Parameters (out):     void
* Return value:         void
* Description:          function that go to specific row and column in the LCD
************************************************************************************/
void LCD_gotoRowColumn(uint8 row ,uint8 column){

	if (LCD_RAW0==row)                     /* Check the row number */
	{
	  LCD_sendCommand(LCD_FIRST_LINE);        
	  while(column--)
	  {
		LCD_sendCommand(LCD_INCREMENT);    /* Increment until reaching the specific column    */
	  }
	}
	else if (LCD_RAW1==row)
	{
		LCD_sendCommand(LCD_SECOND_LINE);
		while(column--)
		{
			LCD_sendCommand(LCD_INCREMENT);  /* Increment until reaching the specific column    */
		}
	}
	
	
}
/************************************************************************************
* Function Name:        LCD_displayStringRowColumn
* Parameters (in):      uint8 lcd_string[],uint8 string_size,uint8  row, uint8 col
* Parameters (inout):   void
* Parameters (out):     void
* Return value:         void
* Description:          Function that display a string in specific row and column
************************************************************************************/
void LCD_displayStringRowColumn(uint8 lcd_string[],uint8 string_size,uint8  row, uint8 col)
{
	LCD_gotoRowColumn(row,col);                    /* Go to  column */
	LCD_displayString(lcd_string,string_size);     
	
}
/************************************************************************************
* Function Name:        LCD_clear
* Parameters (in):      void
* Parameters (inout):   void
* Parameters (out):     void
* Return value:         void
* Description:          Function that clear the LCD
************************************************************************************/
void LCD_clear(void){
	
	LCD_sendCommand(LCD_CLEAR);                    /* Send command clear */
	
}
/************************************************************************************
* Function Name:       LCD_smile_init
* Parameters (in):     void
* Parameters (inout):  void
* Parameters (out):    void
* Return value:        void
* Description:         Function that create smile face
************************************************************************************/
void LCD_smile_init(void)
{
	LCD_sendCommand(LCD_CUSTOM_1);        /* Go to the first custom char place */
	LCD_displayChar(NUM_ZERO);
	LCD_displayChar(NUM_ZERO);
	LCD_displayChar(NUM_10);
	LCD_displayChar(NUM_ZERO);
	LCD_displayChar(NUM_17);
	LCD_displayChar(NUM_14);
	LCD_displayChar(NUM_ZERO);
	LCD_displayChar(NUM_ZERO);
	vTaskDelay( NUM_5 / portTICK_RATE_MS );
	LCD_sendCommand(LCD_FIRST_LINE);      /* Return to the Default config */

}
/************************************************************************************
* Function Name:       LCD_smile_display
* Parameters (in):     void
* Parameters (inout):  void
* Parameters (out):    void
* Return value:        void
* Description:         Function that display smile face
************************************************************************************/
void LCD_smile_display(void)
{
		LCD_displayChar(0);
}



#endif
