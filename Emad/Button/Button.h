/*
 * Button.h
 *
 *  Created on: Mar 18, 2019
 *      Author: AVE-LAP-44
 */

#ifndef BUTTON_BUTTON_H_
#define BUTTON_BUTTON_H_

#define  Button0_PORT      GPIO_PORTF_BASE
#define  Button1_PORT      GPIO_PORTF_BASE


#define  Button0_clk       SYSCTL_PERIPH_GPIOF
#define  Button1_clk       SYSCTL_PERIPH_GPIOF


#define  Button0_PIN       GPIO_PIN_0
#define  Button1_PIN       GPIO_PIN_4




void Button_init();
uint8 get_key(uint8 button_num);

#endif /* BUTTON_BUTTON_H_ */
