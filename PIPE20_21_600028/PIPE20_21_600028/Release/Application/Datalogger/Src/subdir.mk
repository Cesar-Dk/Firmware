################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/Datalogger/Src/datalogger_buffer.c \
../Application/Datalogger/Src/log.c \
../Application/Datalogger/Src/message_queue.c 

O_SRCS += \
../Application/Datalogger/Src/datalogger_buffer.o \
../Application/Datalogger/Src/log.o \
../Application/Datalogger/Src/message_queue.o 

OBJS += \
./Application/Datalogger/Src/datalogger_buffer.o \
./Application/Datalogger/Src/log.o \
./Application/Datalogger/Src/message_queue.o 

C_DEPS += \
./Application/Datalogger/Src/datalogger_buffer.d \
./Application/Datalogger/Src/log.d \
./Application/Datalogger/Src/message_queue.d 


# Each subdirectory must supply rules for building sources it contributes
Application/Datalogger/Src/%.o Application/Datalogger/Src/%.su Application/Datalogger/Src/%.cyclo: ../Application/Datalogger/Src/%.c Application/Datalogger/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/dlms_client/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/dlms_log/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/json/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/LocalTool/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/MBUS/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/ME910/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/MQTT/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/Pulses/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/Sensor/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/UNE82326/Inc" -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/Common/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/Datalogger/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/dlms/Inc" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-Datalogger-2f-Src

clean-Application-2f-Datalogger-2f-Src:
	-$(RM) ./Application/Datalogger/Src/datalogger_buffer.cyclo ./Application/Datalogger/Src/datalogger_buffer.d ./Application/Datalogger/Src/datalogger_buffer.o ./Application/Datalogger/Src/datalogger_buffer.su ./Application/Datalogger/Src/log.cyclo ./Application/Datalogger/Src/log.d ./Application/Datalogger/Src/log.o ./Application/Datalogger/Src/log.su ./Application/Datalogger/Src/message_queue.cyclo ./Application/Datalogger/Src/message_queue.d ./Application/Datalogger/Src/message_queue.o ./Application/Datalogger/Src/message_queue.su

.PHONY: clean-Application-2f-Datalogger-2f-Src

