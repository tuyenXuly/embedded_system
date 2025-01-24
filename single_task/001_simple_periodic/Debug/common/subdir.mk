################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../common/I2C_DS3231.c \
../common/LCD_I2C.c \
../common/print_cli.c \
../common/sht2x_for_stm32_hal.c 

OBJS += \
./common/I2C_DS3231.o \
./common/LCD_I2C.o \
./common/print_cli.o \
./common/sht2x_for_stm32_hal.o 

C_DEPS += \
./common/I2C_DS3231.d \
./common/LCD_I2C.d \
./common/print_cli.d \
./common/sht2x_for_stm32_hal.d 


# Each subdirectory must supply rules for building sources it contributes
common/%.o common/%.su common/%.cyclo: ../common/%.c common/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/tkhtn_final/001_simple_periodic/common" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-common

clean-common:
	-$(RM) ./common/I2C_DS3231.cyclo ./common/I2C_DS3231.d ./common/I2C_DS3231.o ./common/I2C_DS3231.su ./common/LCD_I2C.cyclo ./common/LCD_I2C.d ./common/LCD_I2C.o ./common/LCD_I2C.su ./common/print_cli.cyclo ./common/print_cli.d ./common/print_cli.o ./common/print_cli.su ./common/sht2x_for_stm32_hal.cyclo ./common/sht2x_for_stm32_hal.d ./common/sht2x_for_stm32_hal.o ./common/sht2x_for_stm32_hal.su

.PHONY: clean-common

