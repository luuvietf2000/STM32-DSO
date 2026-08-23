################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/UI/MainScreenUI/MeasurementBar/MeasurementBar.c \
../Core/UI/MainScreenUI/MeasurementBar/MeasurementBarVar.c 

OBJS += \
./Core/UI/MainScreenUI/MeasurementBar/MeasurementBar.o \
./Core/UI/MainScreenUI/MeasurementBar/MeasurementBarVar.o 

C_DEPS += \
./Core/UI/MainScreenUI/MeasurementBar/MeasurementBar.d \
./Core/UI/MainScreenUI/MeasurementBar/MeasurementBarVar.d 


# Each subdirectory must supply rules for building sources it contributes
Core/UI/MainScreenUI/MeasurementBar/%.o Core/UI/MainScreenUI/MeasurementBar/%.su Core/UI/MainScreenUI/MeasurementBar/%.cyclo: ../Core/UI/MainScreenUI/MeasurementBar/%.c Core/UI/MainScreenUI/MeasurementBar/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H750xx -c -I"D:/Code/STM32/STM32-DSO/Stm32h750_Single_DSO/Core/UI" -I"D:/Code/STM32/STM32-DSO/Stm32h750_Single_DSO/Core/UI/MainScreenUI" -I"D:/Code/STM32/STM32-DSO/Stm32h750_Single_DSO/Core/Task/St7789DriverTask/Inc" -I"D:/Code/STM32/STM32-DSO/Stm32h750_Single_DSO/Core/UI" -I"D:/Code/STM32/STM32-DSO/Stm32h750_Single_DSO/Core/Graphics/Inc" -I../Core/Inc -I"D:/Code/STM32/STM32-DSO/Stm32h750_Single_DSO/Drivers/ST7789/Inc" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-UI-2f-MainScreenUI-2f-MeasurementBar

clean-Core-2f-UI-2f-MainScreenUI-2f-MeasurementBar:
	-$(RM) ./Core/UI/MainScreenUI/MeasurementBar/MeasurementBar.cyclo ./Core/UI/MainScreenUI/MeasurementBar/MeasurementBar.d ./Core/UI/MainScreenUI/MeasurementBar/MeasurementBar.o ./Core/UI/MainScreenUI/MeasurementBar/MeasurementBar.su ./Core/UI/MainScreenUI/MeasurementBar/MeasurementBarVar.cyclo ./Core/UI/MainScreenUI/MeasurementBar/MeasurementBarVar.d ./Core/UI/MainScreenUI/MeasurementBar/MeasurementBarVar.o ./Core/UI/MainScreenUI/MeasurementBar/MeasurementBarVar.su

.PHONY: clean-Core-2f-UI-2f-MainScreenUI-2f-MeasurementBar

