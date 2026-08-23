################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/UI/MainScreenUI/Waveform/Waveform.c \
../Core/UI/MainScreenUI/Waveform/WaveformVar.c 

OBJS += \
./Core/UI/MainScreenUI/Waveform/Waveform.o \
./Core/UI/MainScreenUI/Waveform/WaveformVar.o 

C_DEPS += \
./Core/UI/MainScreenUI/Waveform/Waveform.d \
./Core/UI/MainScreenUI/Waveform/WaveformVar.d 


# Each subdirectory must supply rules for building sources it contributes
Core/UI/MainScreenUI/Waveform/%.o Core/UI/MainScreenUI/Waveform/%.su Core/UI/MainScreenUI/Waveform/%.cyclo: ../Core/UI/MainScreenUI/Waveform/%.c Core/UI/MainScreenUI/Waveform/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H750xx -c -I"D:/Code/STM32/STM32-DSO/Stm32h750_Single_DSO/Core/UI" -I"D:/Code/STM32/STM32-DSO/Stm32h750_Single_DSO/Core/UI/MainScreenUI" -I"D:/Code/STM32/STM32-DSO/Stm32h750_Single_DSO/Core/Task/St7789DriverTask/Inc" -I"D:/Code/STM32/STM32-DSO/Stm32h750_Single_DSO/Core/UI" -I"D:/Code/STM32/STM32-DSO/Stm32h750_Single_DSO/Core/Graphics/Inc" -I../Core/Inc -I"D:/Code/STM32/STM32-DSO/Stm32h750_Single_DSO/Drivers/ST7789/Inc" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-UI-2f-MainScreenUI-2f-Waveform

clean-Core-2f-UI-2f-MainScreenUI-2f-Waveform:
	-$(RM) ./Core/UI/MainScreenUI/Waveform/Waveform.cyclo ./Core/UI/MainScreenUI/Waveform/Waveform.d ./Core/UI/MainScreenUI/Waveform/Waveform.o ./Core/UI/MainScreenUI/Waveform/Waveform.su ./Core/UI/MainScreenUI/Waveform/WaveformVar.cyclo ./Core/UI/MainScreenUI/Waveform/WaveformVar.d ./Core/UI/MainScreenUI/Waveform/WaveformVar.o ./Core/UI/MainScreenUI/Waveform/WaveformVar.su

.PHONY: clean-Core-2f-UI-2f-MainScreenUI-2f-Waveform

