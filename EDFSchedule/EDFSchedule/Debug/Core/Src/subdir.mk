################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/I2C_DS3231.c \
../Core/Src/cli_command_list_user.c \
../Core/Src/command_excute.c \
../Core/Src/freertos.c \
../Core/Src/function_cli.c \
../Core/Src/i2c-lcd.c \
../Core/Src/main.c \
../Core/Src/print_cli.c \
../Core/Src/sht2x_for_stm32_hal.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c 

OBJS += \
./Core/Src/I2C_DS3231.o \
./Core/Src/cli_command_list_user.o \
./Core/Src/command_excute.o \
./Core/Src/freertos.o \
./Core/Src/function_cli.o \
./Core/Src/i2c-lcd.o \
./Core/Src/main.o \
./Core/Src/print_cli.o \
./Core/Src/sht2x_for_stm32_hal.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o 

C_DEPS += \
./Core/Src/I2C_DS3231.d \
./Core/Src/cli_command_list_user.d \
./Core/Src/command_excute.d \
./Core/Src/freertos.d \
./Core/Src/function_cli.d \
./Core/Src/i2c-lcd.d \
./Core/Src/main.d \
./Core/Src/print_cli.d \
./Core/Src/sht2x_for_stm32_hal.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/Admin/Downloads/EDFSchedule/EDFSchedule/Middlewares/Third_Party/SEGGER/Config" -I"C:/Users/Admin/Downloads/EDFSchedule/EDFSchedule/Middlewares/Third_Party/SEGGER/OS" -I"C:/Users/Admin/Downloads/EDFSchedule/EDFSchedule/Middlewares/Third_Party/SEGGER/SEGGER" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/I2C_DS3231.cyclo ./Core/Src/I2C_DS3231.d ./Core/Src/I2C_DS3231.o ./Core/Src/I2C_DS3231.su ./Core/Src/cli_command_list_user.cyclo ./Core/Src/cli_command_list_user.d ./Core/Src/cli_command_list_user.o ./Core/Src/cli_command_list_user.su ./Core/Src/command_excute.cyclo ./Core/Src/command_excute.d ./Core/Src/command_excute.o ./Core/Src/command_excute.su ./Core/Src/freertos.cyclo ./Core/Src/freertos.d ./Core/Src/freertos.o ./Core/Src/freertos.su ./Core/Src/function_cli.cyclo ./Core/Src/function_cli.d ./Core/Src/function_cli.o ./Core/Src/function_cli.su ./Core/Src/i2c-lcd.cyclo ./Core/Src/i2c-lcd.d ./Core/Src/i2c-lcd.o ./Core/Src/i2c-lcd.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/print_cli.cyclo ./Core/Src/print_cli.d ./Core/Src/print_cli.o ./Core/Src/print_cli.su ./Core/Src/sht2x_for_stm32_hal.cyclo ./Core/Src/sht2x_for_stm32_hal.d ./Core/Src/sht2x_for_stm32_hal.o ./Core/Src/sht2x_for_stm32_hal.su ./Core/Src/stm32f4xx_hal_msp.cyclo ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.cyclo ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.cyclo ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su

.PHONY: clean-Core-2f-Src

