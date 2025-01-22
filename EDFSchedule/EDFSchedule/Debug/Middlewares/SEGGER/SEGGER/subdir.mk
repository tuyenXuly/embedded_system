################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/SEGGER/SEGGER/SEGGER_RTT.c \
../Middlewares/SEGGER/SEGGER/SEGGER_RTT_printf.c \
../Middlewares/SEGGER/SEGGER/SEGGER_SYSVIEW.c 

S_UPPER_SRCS += \
../Middlewares/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.S 

OBJS += \
./Middlewares/SEGGER/SEGGER/SEGGER_RTT.o \
./Middlewares/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.o \
./Middlewares/SEGGER/SEGGER/SEGGER_RTT_printf.o \
./Middlewares/SEGGER/SEGGER/SEGGER_SYSVIEW.o 

S_UPPER_DEPS += \
./Middlewares/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.d 

C_DEPS += \
./Middlewares/SEGGER/SEGGER/SEGGER_RTT.d \
./Middlewares/SEGGER/SEGGER/SEGGER_RTT_printf.d \
./Middlewares/SEGGER/SEGGER/SEGGER_SYSVIEW.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/SEGGER/SEGGER/%.o Middlewares/SEGGER/SEGGER/%.su Middlewares/SEGGER/SEGGER/%.cyclo: ../Middlewares/SEGGER/SEGGER/%.c Middlewares/SEGGER/SEGGER/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/Admin/Downloads/EDFSchedule/EDFSchedule/Middlewares/Third_Party/SEGGER/Config" -I"C:/Users/Admin/Downloads/EDFSchedule/EDFSchedule/Middlewares/Third_Party/SEGGER/OS" -I"C:/Users/Admin/Downloads/EDFSchedule/EDFSchedule/Middlewares/Third_Party/SEGGER/SEGGER" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/SEGGER/SEGGER/%.o: ../Middlewares/SEGGER/SEGGER/%.S Middlewares/SEGGER/SEGGER/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Middlewares-2f-SEGGER-2f-SEGGER

clean-Middlewares-2f-SEGGER-2f-SEGGER:
	-$(RM) ./Middlewares/SEGGER/SEGGER/SEGGER_RTT.cyclo ./Middlewares/SEGGER/SEGGER/SEGGER_RTT.d ./Middlewares/SEGGER/SEGGER/SEGGER_RTT.o ./Middlewares/SEGGER/SEGGER/SEGGER_RTT.su ./Middlewares/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.d ./Middlewares/SEGGER/SEGGER/SEGGER_RTT_ASM_ARMv7M.o ./Middlewares/SEGGER/SEGGER/SEGGER_RTT_printf.cyclo ./Middlewares/SEGGER/SEGGER/SEGGER_RTT_printf.d ./Middlewares/SEGGER/SEGGER/SEGGER_RTT_printf.o ./Middlewares/SEGGER/SEGGER/SEGGER_RTT_printf.su ./Middlewares/SEGGER/SEGGER/SEGGER_SYSVIEW.cyclo ./Middlewares/SEGGER/SEGGER/SEGGER_SYSVIEW.d ./Middlewares/SEGGER/SEGGER/SEGGER_SYSVIEW.o ./Middlewares/SEGGER/SEGGER/SEGGER_SYSVIEW.su

.PHONY: clean-Middlewares-2f-SEGGER-2f-SEGGER

