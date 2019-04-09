#ifndef LCD_CONFIG_H
#define LCD_CONFIG_H

#define  LCD_RS_PORT      GPIO_PORTA_BASE
#define  LCD_RW_PORT      GPIO_PORTA_BASE
#define  LCD_E_PORT       GPIO_PORTA_BASE
#define  LCD_D4_PORT      GPIO_PORTC_BASE
#define  LCD_D5_PORT      GPIO_PORTC_BASE
#define  LCD_D6_PORT      GPIO_PORTC_BASE
#define  LCD_D7_PORT      GPIO_PORTC_BASE


#define  LCD_RS_clk       SYSCTL_PERIPH_GPIOA
#define  LCD_RW_clk       SYSCTL_PERIPH_GPIOA
#define  LCD_E_clk        SYSCTL_PERIPH_GPIOA
#define  LCD_D4_clk       SYSCTL_PERIPH_GPIOC
#define  LCD_D5_clk       SYSCTL_PERIPH_GPIOC
#define  LCD_D6_clk       SYSCTL_PERIPH_GPIOC
#define  LCD_D7_clk       SYSCTL_PERIPH_GPIOC


#define  LCD_RS_PIN       GPIO_PIN_2
#define  LCD_RW_PIN       GPIO_PIN_3
#define  LCD_E_PIN        GPIO_PIN_4
#define  LCD_D4_PIN       GPIO_PIN_4
#define  LCD_D5_PIN       GPIO_PIN_5
#define  LCD_D6_PIN       GPIO_PIN_6
#define  LCD_D7_PIN       GPIO_PIN_7



#define LCD_TYPE LCD_4BIT_TYPE


#endif
