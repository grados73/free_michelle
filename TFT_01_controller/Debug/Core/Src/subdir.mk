################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/GFX_Color.c \
../Core/Src/GFX_EnhancedFonts.c \
../Core/Src/TFT_ILI9341.c \
../Core/Src/dma.c \
../Core/Src/functions.c \
../Core/Src/gpio.c \
../Core/Src/main.c \
../Core/Src/parser.c \
../Core/Src/ring_buffer.c \
../Core/Src/spi.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c \
../Core/Src/uartdma.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/GFX_Color.o \
./Core/Src/GFX_EnhancedFonts.o \
./Core/Src/TFT_ILI9341.o \
./Core/Src/dma.o \
./Core/Src/functions.o \
./Core/Src/gpio.o \
./Core/Src/main.o \
./Core/Src/parser.o \
./Core/Src/ring_buffer.o \
./Core/Src/spi.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o \
./Core/Src/uartdma.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/GFX_Color.d \
./Core/Src/GFX_EnhancedFonts.d \
./Core/Src/TFT_ILI9341.d \
./Core/Src/dma.d \
./Core/Src/functions.d \
./Core/Src/gpio.d \
./Core/Src/main.d \
./Core/Src/parser.d \
./Core/Src/ring_buffer.d \
./Core/Src/spi.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d \
./Core/Src/uartdma.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/GFX_Color.d ./Core/Src/GFX_Color.o ./Core/Src/GFX_EnhancedFonts.d ./Core/Src/GFX_EnhancedFonts.o ./Core/Src/TFT_ILI9341.d ./Core/Src/TFT_ILI9341.o ./Core/Src/dma.d ./Core/Src/dma.o ./Core/Src/functions.d ./Core/Src/functions.o ./Core/Src/gpio.d ./Core/Src/gpio.o ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/parser.d ./Core/Src/parser.o ./Core/Src/ring_buffer.d ./Core/Src/ring_buffer.o ./Core/Src/spi.d ./Core/Src/spi.o ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/uartdma.d ./Core/Src/uartdma.o ./Core/Src/usart.d ./Core/Src/usart.o

.PHONY: clean-Core-2f-Src

