#ifndef INCLUDES_BUZZER_H_
#define INCLUDES_BUZZER_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#define BUZZERPORT GPIO_PORTD_BASE
#define BUZZERPIN GPIO_PIN_3
#define BUZZER_HIGH GPIO_PIN_3
#define BUZZER_LOW 0

extern void Buzzer_Init(void);
extern void Buzzer_Toggle(void);



#endif /* INCLUDES_BUZZER_H_ */
