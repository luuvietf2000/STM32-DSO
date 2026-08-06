################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/UI/Src/MainScreen.c \
../Core/UI/Src/MainScrenBackgroundConfig.c \
../Core/UI/Src/MeasurementBarConfig.c \
../Core/UI/Src/MeasurementBarLayoutConfig.c \
../Core/UI/Src/StatusBarConfig.c \
../Core/UI/Src/StatusBarLayoutConfig.c \
../Core/UI/Src/WaveformConfig.c \
../Core/UI/Src/WaveformLayoutConfig.c 

OBJS += \
./Core/UI/Src/MainScreen.o \
./Core/UI/Src/MainScrenBackgroundConfig.o \
./Core/UI/Src/MeasurementBarConfig.o \
./Core/UI/Src/MeasurementBarLayoutConfig.o \
./Core/UI/Src/StatusBarConfig.o \
./Core/UI/Src/StatusBarLayoutConfig.o \
./Core/UI/Src/WaveformConfig.o \
./Core/UI/Src/WaveformLayoutConfig.o 

C_DEPS += \
./Core/UI/Src/MainScreen.d \
./Core/UI/Src/MainScrenBackgroundConfig.d \
./Core/UI/Src/MeasurementBarConfig.d \
./Core/UI/Src/MeasurementBarLayoutConfig.d \
./Core/UI/Src/StatusBarConfig.d \
./Core/UI/Src/StatusBarLayoutConfig.d \
./Core/UI/Src/WaveformConfig.d \
./Core/UI/Src/WaveformLayoutConfig.d 


# Each subdirectory must supply rules for building sources it contributes
Core/UI/Src/%.o Core/UI/Src/%.su Core/UI/Src/%.cyclo: ../Core/UI/Src/%.c Core/UI/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H750xx -c -I../Core/Inc -I"D:/Code/STM32/STM32-DSO/Stm32h750_Single_DSO/Drivers/ST7789/Inc" -I"D:/Code/STM32/STM32-DSO/Stm32h750_Single_DSO/Core/Graphics/Inc" -I"D:/Code/STM32/STM32-DSO/Stm32h750_Single_DSO/Core/UI/Inc" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-UI-2f-Src

clean-Core-2f-UI-2f-Src:
	-$(RM) ./Core/UI/Src/MainScreen.cyclo ./Core/UI/Src/MainScreen.d ./Core/UI/Src/MainScreen.o ./Core/UI/Src/MainScreen.su ./Core/UI/Src/MainScrenBackgroundConfig.cyclo ./Core/UI/Src/MainScrenBackgroundConfig.d ./Core/UI/Src/MainScrenBackgroundConfig.o ./Core/UI/Src/MainScrenBackgroundConfig.su ./Core/UI/Src/MeasurementBarConfig.cyclo ./Core/UI/Src/MeasurementBarConfig.d ./Core/UI/Src/MeasurementBarConfig.o ./Core/UI/Src/MeasurementBarConfig.su ./Core/UI/Src/MeasurementBarLayoutConfig.cyclo ./Core/UI/Src/MeasurementBarLayoutConfig.d ./Core/UI/Src/MeasurementBarLayoutConfig.o ./Core/UI/Src/MeasurementBarLayoutConfig.su ./Core/UI/Src/StatusBarConfig.cyclo ./Core/UI/Src/StatusBarConfig.d ./Core/UI/Src/StatusBarConfig.o ./Core/UI/Src/StatusBarConfig.su ./Core/UI/Src/StatusBarLayoutConfig.cyclo ./Core/UI/Src/StatusBarLayoutConfig.d ./Core/UI/Src/StatusBarLayoutConfig.o ./Core/UI/Src/StatusBarLayoutConfig.su ./Core/UI/Src/WaveformConfig.cyclo ./Core/UI/Src/WaveformConfig.d ./Core/UI/Src/WaveformConfig.o ./Core/UI/Src/WaveformConfig.su ./Core/UI/Src/WaveformLayoutConfig.cyclo ./Core/UI/Src/WaveformLayoutConfig.d ./Core/UI/Src/WaveformLayoutConfig.o ./Core/UI/Src/WaveformLayoutConfig.su

.PHONY: clean-Core-2f-UI-2f-Src

