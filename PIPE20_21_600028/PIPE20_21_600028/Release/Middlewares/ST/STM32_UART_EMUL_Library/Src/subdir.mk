################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/STM32_UART_EMUL_Library/Src/stm32l4xx_hal_uart_emul.c 

O_SRCS += \
../Middlewares/ST/STM32_UART_EMUL_Library/Src/stm32l4xx_hal_uart_emul.o 

OBJS += \
./Middlewares/ST/STM32_UART_EMUL_Library/Src/stm32l4xx_hal_uart_emul.o 

C_DEPS += \
./Middlewares/ST/STM32_UART_EMUL_Library/Src/stm32l4xx_hal_uart_emul.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/STM32_UART_EMUL_Library/Src/%.o Middlewares/ST/STM32_UART_EMUL_Library/Src/%.su Middlewares/ST/STM32_UART_EMUL_Library/Src/%.cyclo: ../Middlewares/ST/STM32_UART_EMUL_Library/Src/%.c Middlewares/ST/STM32_UART_EMUL_Library/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/dlms_client/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/dlms_log/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/json/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/LocalTool/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/MBUS/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/ME910/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/MQTT/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/Pulses/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/Sensor/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/UNE82326/Inc" -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/Common/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/Datalogger/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/dlms/Inc" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-ST-2f-STM32_UART_EMUL_Library-2f-Src

clean-Middlewares-2f-ST-2f-STM32_UART_EMUL_Library-2f-Src:
	-$(RM) ./Middlewares/ST/STM32_UART_EMUL_Library/Src/stm32l4xx_hal_uart_emul.cyclo ./Middlewares/ST/STM32_UART_EMUL_Library/Src/stm32l4xx_hal_uart_emul.d ./Middlewares/ST/STM32_UART_EMUL_Library/Src/stm32l4xx_hal_uart_emul.o ./Middlewares/ST/STM32_UART_EMUL_Library/Src/stm32l4xx_hal_uart_emul.su

.PHONY: clean-Middlewares-2f-ST-2f-STM32_UART_EMUL_Library-2f-Src

