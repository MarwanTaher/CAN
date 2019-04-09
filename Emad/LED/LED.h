/*
 * LED.h
 *
 *  Created on: Mar 13, 2019
 *      Author: AVE-LAP-44
 */

#ifndef LED_LED_H_
#define LED_LED_H_


#define LED0               0
#define LED1               1
#define LED2               2


extern void Led_init();
extern void Led_on(uint8 num);
extern void Led_off(uint8 num);

#endif /* LED_LED_H_ */
