################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/led1202/led1202.c \
../Drivers/BSP/Components/led1202/led1202_reg.c 

C_DEPS += \
./Drivers/BSP/Components/led1202/led1202.d \
./Drivers/BSP/Components/led1202/led1202_reg.d 

OBJS += \
./Drivers/BSP/Components/led1202/led1202.o \
./Drivers/BSP/Components/led1202/led1202_reg.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/led1202/%.o Drivers/BSP/Components/led1202/%.su Drivers/BSP/Components/led1202/%.cyclo: ../Drivers/BSP/Components/led1202/%.c Drivers/BSP/Components/led1202/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G0B1xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-led1202

clean-Drivers-2f-BSP-2f-Components-2f-led1202:
	-$(RM) ./Drivers/BSP/Components/led1202/led1202.cyclo ./Drivers/BSP/Components/led1202/led1202.d ./Drivers/BSP/Components/led1202/led1202.o ./Drivers/BSP/Components/led1202/led1202.su ./Drivers/BSP/Components/led1202/led1202_reg.cyclo ./Drivers/BSP/Components/led1202/led1202_reg.d ./Drivers/BSP/Components/led1202/led1202_reg.o ./Drivers/BSP/Components/led1202/led1202_reg.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-led1202

