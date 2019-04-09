################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
BTN.obj: ../BTN.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/ARM_CM4F" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/MemMang" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/include" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="BTN.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

BUZZER.obj: ../BUZZER.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/ARM_CM4F" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/MemMang" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/include" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="BUZZER.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CAN.obj: ../CAN.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/ARM_CM4F" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/MemMang" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/include" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="CAN.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

LCD.obj: ../LCD.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/ARM_CM4F" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/MemMang" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/include" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="LCD.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

LED.obj: ../LED.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/ARM_CM4F" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/MemMang" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/include" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="LED.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

My_Task.obj: ../My_Task.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/ARM_CM4F" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/MemMang" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/include" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="My_Task.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

croutine.obj: ../croutine.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/ARM_CM4F" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/MemMang" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/include" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="croutine.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

event_groups.obj: ../event_groups.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/ARM_CM4F" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/MemMang" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/include" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="event_groups.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

list.obj: ../list.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/ARM_CM4F" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/MemMang" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/include" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="list.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/ARM_CM4F" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/MemMang" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/include" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="main.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

queue.obj: ../queue.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/ARM_CM4F" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/MemMang" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/include" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="queue.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

stream_buffer.obj: ../stream_buffer.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/ARM_CM4F" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/MemMang" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/include" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="stream_buffer.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

tasks.obj: ../tasks.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/ARM_CM4F" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/MemMang" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/include" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="tasks.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

timers.obj: ../timers.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/ARM_CM4F" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/MemMang" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/include" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="timers.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

tm4c123gh6pm_startup_ccs.obj: ../tm4c123gh6pm_startup_ccs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/ARM_CM4F" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/MemMang" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/include" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="tm4c123gh6pm_startup_ccs.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

uartstdio.obj: ../uartstdio.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/ARM_CM4F" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/MemMang" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/include" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="uartstdio.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


