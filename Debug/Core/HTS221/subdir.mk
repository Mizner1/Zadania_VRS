################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/HTS221/HTS221.c 

OBJS += \
./Core/HTS221/HTS221.o 

C_DEPS += \
./Core/HTS221/HTS221.d 


# Each subdirectory must supply rules for building sources it contributes
Core/HTS221/%.o Core/HTS221/%.su Core/HTS221/%.cyclo: ../Core/HTS221/%.c Core/HTS221/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303x8 -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-HTS221

clean-Core-2f-HTS221:
	-$(RM) ./Core/HTS221/HTS221.cyclo ./Core/HTS221/HTS221.d ./Core/HTS221/HTS221.o ./Core/HTS221/HTS221.su

.PHONY: clean-Core-2f-HTS221

