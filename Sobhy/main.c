//*****************************************************************************
//
// simple_rx.c - Example demonstrating simple CAN message reception.
//
// Copyright (c) 2010-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
//   Redistribution and use in source and binary forms, with or without
//   modification, are permitted provided that the following conditions
//   are met:
//
//   Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
//
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the
//   distribution.
//
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision 2.1.4.178 of the Tiva Firmware Development Package.
//
//*****************************************************************************

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/can.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"


#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "FreeRTOS_Files/FreeRTOS.h"
#include "FreeRTOS_Files/task.h"
#include "FreeRTOS_Files/queue.h"
#include "FreeRTOS_Files/semphr.h"
#include "FreeRTOS_Files/event_groups.h"
#include "HAL/LCD.h"
#include "HAL/Magic_Num.h"
#include "APPLICATION/Delay.h"
#include "APPLICATION/App_Tasks.h"
#include "driverlib/ssi.h"


//*****************************************************************************
//
//! \addtogroup can_examples_list
//! <h1>Simple CAN RX (simple_rx)</h1>
//!
//! This example shows the basic setup of CAN in order to receive messages
//! from the CAN bus.  The CAN peripheral is configured to receive messages
//! with any CAN ID and then print the message contents to the console.
//!
//! This example uses the following peripherals and I/O signals.  You must
//! review these and change as needed for your own board:
//! - CAN0 peripheral
//! - GPIO port B peripheral (for CAN0 pins)
//! - CAN0RX - PB4
//! - CAN0TX - PB5
//!
//! The following UART signals are configured only for displaying console
//! messages for this example.  These are not required for operation of CAN.
//! - GPIO port A peripheral (for UART0 pins)
//! - UART0RX - PA0
//! - UART0TX - PA1
//!
//! This example uses the following interrupt handlers.  To use this example
//! in your own application you must add these interrupt handlers to your
//! vector table.
//! - INT_CAN0 - CANIntHandler
//
//*****************************************************************************


void
main(void)
{


      /*Task to initilaize System */
      xTaskCreate((TaskFunction_t)Init_Task ,NULL, 100, NULL,FOUR, NULL);

     /* Task with periodicity 1000ms*/
     xTaskCreate((TaskFunction_t)CAN_NODE0_TASK,NULL, 100, NULL,THREE, NULL);

     /* Task with periodicity 100ms*/
     xTaskCreate((TaskFunction_t)BUTTON_TASK,NULL, 100, NULL,TWO, NULL);

     /*
     ** Start the scheduler.  This should not return.
     */
     vTaskStartScheduler();

}
