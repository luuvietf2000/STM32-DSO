################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/UI/Main_Screen/Src/MainScreen.c 

OBJS += \
./Core/UI/Main_Screen/Src/MainScreen.o 

C_DEPS += \
./Core/UI/Main_Screen/Src/MainScreen.d 


# Each subdirectory must supply rules for building sources it contributes
Core/UI/Main_Screen/Src/%.o Core/UI/Main_Screen/Src/%.su Core/UI/Main_Screen/Src/%.cyclo: ../Core/UI/Main_Screen/Src/%.c Core/UI/Main_Screen/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H750xx -c -I"D:/Code/STM32/STM32-DSO/Stm32h750_Single_DSO/Core/Task/St7789DriverTask/Inc" -I"D:/Code/STM32/STM32-DSO/Stm32h750_Single_DSO/Core/Graphics/Inc" -I../Core/Inc -I"D:/Code/STM32/STM32-DSO/Stm32h750_Single_DSO/Drivers/ST7789/Inc" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-UI-2f-Main_Screen-2f-Src

clean-Core-2f-UI-2f-Main_Screen-2f-Src:
	-$(RM) ./Core/UI/Main_Screen/Src/MainScreen.cyclo ./Core/UI/Main_Screen/Src/MainScreen.d ./Core/UI/Main_Screen/Src/MainScreen.o ./Core/UI/Main_Screen/Src/MainScreen.su

.PHONY: clean-Core-2f-UI-2f-Main_Screen-2f-Src

