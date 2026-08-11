################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Task/St7789DriverTask/Src/St7789DmaMemory.c \
../Core/Task/St7789DriverTask/Src/St7789Queue.c \
../Core/Task/St7789DriverTask/Src/St7789Task.c 

OBJS += \
./Core/Task/St7789DriverTask/Src/St7789DmaMemory.o \
./Core/Task/St7789DriverTask/Src/St7789Queue.o \
./Core/Task/St7789DriverTask/Src/St7789Task.o 

C_DEPS += \
./Core/Task/St7789DriverTask/Src/St7789DmaMemory.d \
./Core/Task/St7789DriverTask/Src/St7789Queue.d \
./Core/Task/St7789DriverTask/Src/St7789Task.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Task/St7789DriverTask/Src/%.o Core/Task/St7789DriverTask/Src/%.su Core/Task/St7789DriverTask/Src/%.cyclo: ../Core/Task/St7789DriverTask/Src/%.c Core/Task/St7789DriverTask/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_PWR_LDO_SUPPLY -DUSE_HAL_DRIVER -DSTM32H750xx -c -I"D:/Code/STM32/STM32-DSO/Stm32h750_Single_DSO/Core/Task/St7789DriverTask/Inc" -I../Core/Inc -I"D:/Code/STM32/STM32-DSO/Stm32h750_Single_DSO/Drivers/ST7789/Inc" -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Task-2f-St7789DriverTask-2f-Src

clean-Core-2f-Task-2f-St7789DriverTask-2f-Src:
	-$(RM) ./Core/Task/St7789DriverTask/Src/St7789DmaMemory.cyclo ./Core/Task/St7789DriverTask/Src/St7789DmaMemory.d ./Core/Task/St7789DriverTask/Src/St7789DmaMemory.o ./Core/Task/St7789DriverTask/Src/St7789DmaMemory.su ./Core/Task/St7789DriverTask/Src/St7789Queue.cyclo ./Core/Task/St7789DriverTask/Src/St7789Queue.d ./Core/Task/St7789DriverTask/Src/St7789Queue.o ./Core/Task/St7789DriverTask/Src/St7789Queue.su ./Core/Task/St7789DriverTask/Src/St7789Task.cyclo ./Core/Task/St7789DriverTask/Src/St7789Task.d ./Core/Task/St7789DriverTask/Src/St7789Task.o ./Core/Task/St7789DriverTask/Src/St7789Task.su

.PHONY: clean-Core-2f-Task-2f-St7789DriverTask-2f-Src

