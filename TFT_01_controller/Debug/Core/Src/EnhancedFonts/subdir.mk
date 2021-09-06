################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/EnhancedFonts/ArialBlack_28pts_bold.c \
../Core/Src/EnhancedFonts/arialBlack_20ptFontInfo.c 

OBJS += \
./Core/Src/EnhancedFonts/ArialBlack_28pts_bold.o \
./Core/Src/EnhancedFonts/arialBlack_20ptFontInfo.o 

C_DEPS += \
./Core/Src/EnhancedFonts/ArialBlack_28pts_bold.d \
./Core/Src/EnhancedFonts/arialBlack_20ptFontInfo.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/EnhancedFonts/%.o: ../Core/Src/EnhancedFonts/%.c Core/Src/EnhancedFonts/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

