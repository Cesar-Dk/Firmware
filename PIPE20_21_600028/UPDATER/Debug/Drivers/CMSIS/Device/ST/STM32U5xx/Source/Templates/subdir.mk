################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/Device/ST/STM32U5xx/Source/Templates/system_stm32u5xx_ns.c 

OBJS += \
./Drivers/CMSIS/Device/ST/STM32U5xx/Source/Templates/system_stm32u5xx_ns.o 

C_DEPS += \
./Drivers/CMSIS/Device/ST/STM32U5xx/Source/Templates/system_stm32u5xx_ns.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/Device/ST/STM32U5xx/Source/Templates/%.o Drivers/CMSIS/Device/ST/STM32U5xx/Source/Templates/%.su: ../Drivers/CMSIS/Device/ST/STM32U5xx/Source/Templates/%.c Drivers/CMSIS/Device/ST/STM32U5xx/Source/Templates/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32U575xx -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fcommon -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-Device-2f-ST-2f-STM32U5xx-2f-Source-2f-Templates

clean-Drivers-2f-CMSIS-2f-Device-2f-ST-2f-STM32U5xx-2f-Source-2f-Templates:
	-$(RM) ./Drivers/CMSIS/Device/ST/STM32U5xx/Source/Templates/system_stm32u5xx_ns.d ./Drivers/CMSIS/Device/ST/STM32U5xx/Source/Templates/system_stm32u5xx_ns.o ./Drivers/CMSIS/Device/ST/STM32U5xx/Source/Templates/system_stm32u5xx_ns.su

.PHONY: clean-Drivers-2f-CMSIS-2f-Device-2f-ST-2f-STM32U5xx-2f-Source-2f-Templates

