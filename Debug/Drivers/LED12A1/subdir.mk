################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/LED12A1/led12a1.c 

C_DEPS += \
./Drivers/LED12A1/led12a1.d 

OBJS += \
./Drivers/LED12A1/led12a1.o 


# Each subdirectory must supply rules for building sources it contributes
Drivers/LED12A1/%.o Drivers/LED12A1/%.su Drivers/LED12A1/%.cyclo: ../Drivers/LED12A1/%.c Drivers/LED12A1/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G0B1xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I../Drivers/LED12A1 -I../Drivers/led1202 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-LED12A1

clean-Drivers-2f-LED12A1:
	-$(RM) ./Drivers/LED12A1/led12a1.cyclo ./Drivers/LED12A1/led12a1.d ./Drivers/LED12A1/led12a1.o ./Drivers/LED12A1/led12a1.su

.PHONY: clean-Drivers-2f-LED12A1

