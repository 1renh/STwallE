################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/LED12A1/led12a1.c 

C_DEPS += \
./Drivers/BSP/LED12A1/led12a1.d 

OBJS += \
./Drivers/BSP/LED12A1/led12a1.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/LED12A1/%.o Drivers/BSP/LED12A1/%.su Drivers/BSP/LED12A1/%.cyclo: ../Drivers/BSP/LED12A1/%.c Drivers/BSP/LED12A1/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G0B1xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-LED12A1

clean-Drivers-2f-BSP-2f-LED12A1:
	-$(RM) ./Drivers/BSP/LED12A1/led12a1.cyclo ./Drivers/BSP/LED12A1/led12a1.d ./Drivers/BSP/LED12A1/led12a1.o ./Drivers/BSP/LED12A1/led12a1.su

.PHONY: clean-Drivers-2f-BSP-2f-LED12A1

