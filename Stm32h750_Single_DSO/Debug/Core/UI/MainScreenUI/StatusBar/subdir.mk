################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/UI/MainScreenUI/StatusBar/StatusBar.c \
../Core/UI/MainScreenUI/StatusBar/StatusBarVar.c 

OBJS += \
./Core/UI/MainScreenUI/StatusBar/StatusBar.o \
./Core/UI/MainScreenUI/StatusBar/StatusBarVar.o 

C_DEPS += \
./Core/UI/MainScreenUI/StatusBar/StatusBar.d \
./Core/UI/MainScreenUI/StatusBar/StatusBarVar.d 


# Each subdirectory must supply rules for building sources it contributes
Core/UI/MainScreenUI/StatusBar/%.o Core/UI/MainScreenUI/StatusBar/%.su Core/UI/MainScreenUI/StatusBar/%.cyclo: ../Core/UI/MainScreenUI/StatusBar/%.c Core/UI/MainScreenUI/StatusBar/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H750xx -c -I"D:/Code/STM32/STM32-DSO/Stm32h750_Single_DSO/Core/UI" -I"D:/Code/STM32/STM32-DSO/Stm32h750_Single_DSO/Core/UI/MainScreenUI" -I"D:/Code/STM32/STM32-DSO/Stm32h750_Single_DSO/Core/Task/St7789DriverTask/Inc" -I"D:/Code/STM32/STM32-DSO/Stm32h750_Single_DSO/Core/UI" -I"D:/Code/STM32/STM32-DSO/Stm32h750_Single_DSO/Core/Graphics/Inc" -I../Core/Inc -I"D:/Code/STM32/STM32-DSO/Stm32h750_Single_DSO/Drivers/ST7789/Inc" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-UI-2f-MainScreenUI-2f-StatusBar

clean-Core-2f-UI-2f-MainScreenUI-2f-StatusBar:
	-$(RM) ./Core/UI/MainScreenUI/StatusBar/StatusBar.cyclo ./Core/UI/MainScreenUI/StatusBar/StatusBar.d ./Core/UI/MainScreenUI/StatusBar/StatusBar.o ./Core/UI/MainScreenUI/StatusBar/StatusBar.su ./Core/UI/MainScreenUI/StatusBar/StatusBarVar.cyclo ./Core/UI/MainScreenUI/StatusBar/StatusBarVar.d ./Core/UI/MainScreenUI/StatusBar/StatusBarVar.o ./Core/UI/MainScreenUI/StatusBar/StatusBarVar.su

.PHONY: clean-Core-2f-UI-2f-MainScreenUI-2f-StatusBar

