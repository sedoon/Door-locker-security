################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../control\ unit/HAL/LCD/lcd.c 

OBJS += \
./control\ unit/HAL/LCD/lcd.o 

C_DEPS += \
./control\ unit/HAL/LCD/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
control\ unit/HAL/LCD/lcd.o: ../control\ unit/HAL/LCD/lcd.c control\ unit/HAL/LCD/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"control unit/HAL/LCD/lcd.d" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


