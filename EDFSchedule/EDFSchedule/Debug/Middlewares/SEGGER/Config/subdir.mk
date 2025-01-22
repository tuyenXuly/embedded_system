################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.c 

OBJS += \
./Middlewares/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.o 

C_DEPS += \
./Middlewares/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/SEGGER/Config/%.o Middlewares/SEGGER/Config/%.su Middlewares/SEGGER/Config/%.cyclo: ../Middlewares/SEGGER/Config/%.c Middlewares/SEGGER/Config/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/Admin/Downloads/EDFSchedule/EDFSchedule/Middlewares/Third_Party/SEGGER/Config" -I"C:/Users/Admin/Downloads/EDFSchedule/EDFSchedule/Middlewares/Third_Party/SEGGER/OS" -I"C:/Users/Admin/Downloads/EDFSchedule/EDFSchedule/Middlewares/Third_Party/SEGGER/SEGGER" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-SEGGER-2f-Config

clean-Middlewares-2f-SEGGER-2f-Config:
	-$(RM) ./Middlewares/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.cyclo ./Middlewares/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.d ./Middlewares/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.o ./Middlewares/SEGGER/Config/SEGGER_SYSVIEW_Config_FreeRTOS.su

.PHONY: clean-Middlewares-2f-SEGGER-2f-Config

