################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Graphics/Src/Graphics.c \
../Core/Graphics/Src/GraphicsRectangleWidget.c \
../Core/Graphics/Src/GraphicsTextWidget.c \
../Core/Graphics/Src/GraphicsWaveformWidget.c 

OBJS += \
./Core/Graphics/Src/Graphics.o \
./Core/Graphics/Src/GraphicsRectangleWidget.o \
./Core/Graphics/Src/GraphicsTextWidget.o \
./Core/Graphics/Src/GraphicsWaveformWidget.o 

C_DEPS += \
./Core/Graphics/Src/Graphics.d \
./Core/Graphics/Src/GraphicsRectangleWidget.d \
./Core/Graphics/Src/GraphicsTextWidget.d \
./Core/Graphics/Src/GraphicsWaveformWidget.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Graphics/Src/%.o Core/Graphics/Src/%.su Core/Graphics/Src/%.cyclo: ../Core/Graphics/Src/%.c Core/Graphics/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H750xx -c -I"D:/Code/STM32/STM32-DSO/Stm32h750_Single_DSO/Core/Task/St7789DriverTask/Inc" -I"D:/Code/STM32/STM32-DSO/Stm32h750_Single_DSO/Core/Graphics/Inc" -I../Core/Inc -I"D:/Code/STM32/STM32-DSO/Stm32h750_Single_DSO/Drivers/ST7789/Inc" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Graphics-2f-Src

clean-Core-2f-Graphics-2f-Src:
	-$(RM) ./Core/Graphics/Src/Graphics.cyclo ./Core/Graphics/Src/Graphics.d ./Core/Graphics/Src/Graphics.o ./Core/Graphics/Src/Graphics.su ./Core/Graphics/Src/GraphicsRectangleWidget.cyclo ./Core/Graphics/Src/GraphicsRectangleWidget.d ./Core/Graphics/Src/GraphicsRectangleWidget.o ./Core/Graphics/Src/GraphicsRectangleWidget.su ./Core/Graphics/Src/GraphicsTextWidget.cyclo ./Core/Graphics/Src/GraphicsTextWidget.d ./Core/Graphics/Src/GraphicsTextWidget.o ./Core/Graphics/Src/GraphicsTextWidget.su ./Core/Graphics/Src/GraphicsWaveformWidget.cyclo ./Core/Graphics/Src/GraphicsWaveformWidget.d ./Core/Graphics/Src/GraphicsWaveformWidget.o ./Core/Graphics/Src/GraphicsWaveformWidget.su

.PHONY: clean-Core-2f-Graphics-2f-Src

