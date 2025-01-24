################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lib/I2C_DS3231.c \
../lib/LCD_I2C.c \
../lib/cli_command_list_user.c \
../lib/command_excute.c \
../lib/function_cli.c \
../lib/print_cli.c \
../lib/queue.c \
../lib/sht2x_for_stm32_hal.c \
../lib/uart.c 

OBJS += \
./lib/I2C_DS3231.o \
./lib/LCD_I2C.o \
./lib/cli_command_list_user.o \
./lib/command_excute.o \
./lib/function_cli.o \
./lib/print_cli.o \
./lib/queue.o \
./lib/sht2x_for_stm32_hal.o \
./lib/uart.o 

C_DEPS += \
./lib/I2C_DS3231.d \
./lib/LCD_I2C.d \
./lib/cli_command_list_user.d \
./lib/command_excute.d \
./lib/function_cli.d \
./lib/print_cli.d \
./lib/queue.d \
./lib/sht2x_for_stm32_hal.d \
./lib/uart.d 


# Each subdirectory must supply rules for building sources it contributes
lib/%.o lib/%.su lib/%.cyclo: ../lib/%.c lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/tkhtn_final/002_Non_Preemptive_Event_Triggered/lib" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-lib

clean-lib:
	-$(RM) ./lib/I2C_DS3231.cyclo ./lib/I2C_DS3231.d ./lib/I2C_DS3231.o ./lib/I2C_DS3231.su ./lib/LCD_I2C.cyclo ./lib/LCD_I2C.d ./lib/LCD_I2C.o ./lib/LCD_I2C.su ./lib/cli_command_list_user.cyclo ./lib/cli_command_list_user.d ./lib/cli_command_list_user.o ./lib/cli_command_list_user.su ./lib/command_excute.cyclo ./lib/command_excute.d ./lib/command_excute.o ./lib/command_excute.su ./lib/function_cli.cyclo ./lib/function_cli.d ./lib/function_cli.o ./lib/function_cli.su ./lib/print_cli.cyclo ./lib/print_cli.d ./lib/print_cli.o ./lib/print_cli.su ./lib/queue.cyclo ./lib/queue.d ./lib/queue.o ./lib/queue.su ./lib/sht2x_for_stm32_hal.cyclo ./lib/sht2x_for_stm32_hal.d ./lib/sht2x_for_stm32_hal.o ./lib/sht2x_for_stm32_hal.su ./lib/uart.cyclo ./lib/uart.d ./lib/uart.o ./lib/uart.su

.PHONY: clean-lib

