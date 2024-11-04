################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/LPS25HB/LPS25HB.c 

OBJS += \
./Core/LPS25HB/LPS25HB.o 

C_DEPS += \
./Core/LPS25HB/LPS25HB.d 


# Each subdirectory must supply rules for building sources it contributes
Core/LPS25HB/%.o Core/LPS25HB/%.su Core/LPS25HB/%.cyclo: ../Core/LPS25HB/%.c Core/LPS25HB/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303x8 -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-LPS25HB

clean-Core-2f-LPS25HB:
	-$(RM) ./Core/LPS25HB/LPS25HB.cyclo ./Core/LPS25HB/LPS25HB.d ./Core/LPS25HB/LPS25HB.o ./Core/LPS25HB/LPS25HB.su

.PHONY: clean-Core-2f-LPS25HB

