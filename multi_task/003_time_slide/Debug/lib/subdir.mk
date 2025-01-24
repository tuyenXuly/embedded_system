################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/I2C_DS3231.c \
../lib/LCD_I2C.c \
../lib/print_cli.c \
../lib/sht2x_for_stm32_hal.c 

OBJS += \
./lib/I2C_DS3231.o \
./lib/LCD_I2C.o \
./lib/print_cli.o \
./lib/sht2x_for_stm32_hal.o 

C_DEPS += \
./lib/I2C_DS3231.d \
./lib/LCD_I2C.d \
./lib/print_cli.d \
./lib/sht2x_for_stm32_hal.d 


# Each subdirectory must supply rules for building sources it contributes
lib/%.o lib/%.su lib/%.cyclo: ../lib/%.c lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Mastering RTOS Hands on FreeRTOS/RTOS_Workspacee/common/ThirdParty/FreeRTOS/include" -I"D:/Mastering RTOS Hands on FreeRTOS/RTOS_Workspacee/common/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I"D:/Mastering RTOS Hands on FreeRTOS/RTOS_Workspacee/common/ThirdParty/SEGGER/Config" -I"D:/Mastering RTOS Hands on FreeRTOS/RTOS_Workspacee/common/ThirdParty/SEGGER/OS" -I"D:/Mastering RTOS Hands on FreeRTOS/RTOS_Workspacee/common/ThirdParty/SEGGER/SEGGER" -I"D:/tkhtn_final/003_multi_task/common/ThirdParty/FreeRTOS/include" -I"D:/tkhtn_final/003_multi_task/common/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -I"D:/tkhtn_final/003_multi_task/common/ThirdParty/SEGGER/Config" -I"D:/tkhtn_final/003_multi_task/common/ThirdParty/SEGGER/OS" -I"D:/tkhtn_final/003_multi_task/common/ThirdParty/SEGGER/SEGGER" -I"D:/tkhtn_final/003_multi_task/lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lib

clean-lib:
	-$(RM) ./lib/I2C_DS3231.cyclo ./lib/I2C_DS3231.d ./lib/I2C_DS3231.o ./lib/I2C_DS3231.su ./lib/LCD_I2C.cyclo ./lib/LCD_I2C.d ./lib/LCD_I2C.o ./lib/LCD_I2C.su ./lib/print_cli.cyclo ./lib/print_cli.d ./lib/print_cli.o ./lib/print_cli.su ./lib/sht2x_for_stm32_hal.cyclo ./lib/sht2x_for_stm32_hal.d ./lib/sht2x_for_stm32_hal.o ./lib/sht2x_for_stm32_hal.su

.PHONY: clean-lib

