################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
MemMang/heap_1.obj: ../MemMang/heap_1.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/ARM_CM4F" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/MemMang" --include_path="C:/Users/AVE-LAP-051/Desktop/TIVA_PROJECT_UART/Free_RTOS_Porting/include" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.1.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="MemMang/heap_1.d_raw" --obj_directory="MemMang" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


