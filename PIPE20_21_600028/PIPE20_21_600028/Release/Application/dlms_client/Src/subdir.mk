################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/dlms_client/Src/communication.c \
../Application/dlms_client/Src/connection.c \
../Application/dlms_client/Src/dlms_client.c \
../Application/dlms_client/Src/dlms_client_on_demand_comm.c \
../Application/dlms_client/Src/dlms_client_table.c 

O_SRCS += \
../Application/dlms_client/Src/communication.o \
../Application/dlms_client/Src/connection.o \
../Application/dlms_client/Src/dlms_client.o \
../Application/dlms_client/Src/dlms_client_on_demand_comm.o \
../Application/dlms_client/Src/dlms_client_table.o 

OBJS += \
./Application/dlms_client/Src/communication.o \
./Application/dlms_client/Src/connection.o \
./Application/dlms_client/Src/dlms_client.o \
./Application/dlms_client/Src/dlms_client_on_demand_comm.o \
./Application/dlms_client/Src/dlms_client_table.o 

C_DEPS += \
./Application/dlms_client/Src/communication.d \
./Application/dlms_client/Src/connection.d \
./Application/dlms_client/Src/dlms_client.d \
./Application/dlms_client/Src/dlms_client_on_demand_comm.d \
./Application/dlms_client/Src/dlms_client_table.d 


# Each subdirectory must supply rules for building sources it contributes
Application/dlms_client/Src/%.o Application/dlms_client/Src/%.su Application/dlms_client/Src/%.cyclo: ../Application/dlms_client/Src/%.c Application/dlms_client/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/dlms_client/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/dlms_log/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/json/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/LocalTool/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/MBUS/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/ME910/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/MQTT/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/Pulses/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/Sensor/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/UNE82326/Inc" -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/Common/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/Datalogger/Inc" -I"/home/desarrollo02/prueba_fw/PIPE20_21_600028_2/PIPE20_21_600028/PIPE20_21_600028/Application/dlms/Inc" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-dlms_client-2f-Src

clean-Application-2f-dlms_client-2f-Src:
	-$(RM) ./Application/dlms_client/Src/communication.cyclo ./Application/dlms_client/Src/communication.d ./Application/dlms_client/Src/communication.o ./Application/dlms_client/Src/communication.su ./Application/dlms_client/Src/connection.cyclo ./Application/dlms_client/Src/connection.d ./Application/dlms_client/Src/connection.o ./Application/dlms_client/Src/connection.su ./Application/dlms_client/Src/dlms_client.cyclo ./Application/dlms_client/Src/dlms_client.d ./Application/dlms_client/Src/dlms_client.o ./Application/dlms_client/Src/dlms_client.su ./Application/dlms_client/Src/dlms_client_on_demand_comm.cyclo ./Application/dlms_client/Src/dlms_client_on_demand_comm.d ./Application/dlms_client/Src/dlms_client_on_demand_comm.o ./Application/dlms_client/Src/dlms_client_on_demand_comm.su ./Application/dlms_client/Src/dlms_client_table.cyclo ./Application/dlms_client/Src/dlms_client_table.d ./Application/dlms_client/Src/dlms_client_table.o ./Application/dlms_client/Src/dlms_client_table.su

.PHONY: clean-Application-2f-dlms_client-2f-Src

