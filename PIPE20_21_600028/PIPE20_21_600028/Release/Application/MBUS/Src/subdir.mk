################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/MBUS/Src/mbus.c \
../Application/MBUS/Src/mbus_protocol.c \
../Application/MBUS/Src/mbus_protocol_aux.c \
../Application/MBUS/Src/mbus_slave_table_manager.c \
../Application/MBUS/Src/serial_mbus.c 

O_SRCS += \
../Application/MBUS/Src/mbus.o \
../Application/MBUS/Src/mbus_protocol.o \
../Application/MBUS/Src/mbus_protocol_aux.o \
../Application/MBUS/Src/mbus_slave_table_manager.o \
../Application/MBUS/Src/serial_mbus.o 

OBJS += \
./Application/MBUS/Src/mbus.o \
./Application/MBUS/Src/mbus_protocol.o \
./Application/MBUS/Src/mbus_protocol_aux.o \
./Application/MBUS/Src/mbus_slave_table_manager.o \
./Application/MBUS/Src/serial_mbus.o 

C_DEPS += \
./Application/MBUS/Src/mbus.d \
./Application/MBUS/Src/mbus_protocol.d \
./Application/MBUS/Src/mbus_protocol_aux.d \
./Application/MBUS/Src/mbus_slave_table_manager.d \
./Application/MBUS/Src/serial_mbus.d 


# Each subdirectory must supply rules for building sources it contributes
Application/MBUS/Src/%.o Application/MBUS/Src/%.su Application/MBUS/Src/%.cyclo: ../Application/MBUS/Src/%.c Application/MBUS/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/dlms_client/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/dlms_log/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/json/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/LocalTool/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/MBUS/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/ME910/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/MQTT/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/Pulses/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/Sensor/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/UNE82326/Inc" -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/Common/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/Datalogger/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/dlms/Inc" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-MBUS-2f-Src

clean-Application-2f-MBUS-2f-Src:
	-$(RM) ./Application/MBUS/Src/mbus.cyclo ./Application/MBUS/Src/mbus.d ./Application/MBUS/Src/mbus.o ./Application/MBUS/Src/mbus.su ./Application/MBUS/Src/mbus_protocol.cyclo ./Application/MBUS/Src/mbus_protocol.d ./Application/MBUS/Src/mbus_protocol.o ./Application/MBUS/Src/mbus_protocol.su ./Application/MBUS/Src/mbus_protocol_aux.cyclo ./Application/MBUS/Src/mbus_protocol_aux.d ./Application/MBUS/Src/mbus_protocol_aux.o ./Application/MBUS/Src/mbus_protocol_aux.su ./Application/MBUS/Src/mbus_slave_table_manager.cyclo ./Application/MBUS/Src/mbus_slave_table_manager.d ./Application/MBUS/Src/mbus_slave_table_manager.o ./Application/MBUS/Src/mbus_slave_table_manager.su ./Application/MBUS/Src/serial_mbus.cyclo ./Application/MBUS/Src/serial_mbus.d ./Application/MBUS/Src/serial_mbus.o ./Application/MBUS/Src/serial_mbus.su

.PHONY: clean-Application-2f-MBUS-2f-Src

