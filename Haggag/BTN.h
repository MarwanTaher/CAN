#ifndef BTN_H_
#define BTN_H_
#include <stdint.h>

#define PUSHBTN0PORT GPIO_PORTF_BASE
#define PUSHBTN0PIN GPIO_PIN_0

#define PUSHBTN1PORT GPIO_PORTF_BASE
#define PUSHBTN1PIN GPIO_PIN_4
#define ZERO 0
#define BTN1_ON 1
#define BTN1_OFF 0
#define BTN2_ON 1
#define BTN2_OFF 0
extern void Btns_Init(void);
extern uint32_t Btn1_Read(void);
uint32_t Btn2_Read(void);



#endif /* BTN_H_ */
