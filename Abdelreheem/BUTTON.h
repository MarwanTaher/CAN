#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>

extern void BUTTON_Init(void);
extern uint8_t Get_BUTTON(void);
extern uint8_t Debouncing();

//extern QueueHandle_t xQueue;
#endif
