################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MC2/HAL/LCD/lcd.c 

OBJS += \
./MC2/HAL/LCD/lcd.o 

C_DEPS += \
./MC2/HAL/LCD/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
MC2/HAL/LCD/%.o: ../MC2/HAL/LCD/%.c MC2/HAL/LCD/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


