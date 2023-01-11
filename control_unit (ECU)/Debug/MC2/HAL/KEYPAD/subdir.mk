################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MC2/HAL/KEYPAD/keypad.c 

OBJS += \
./MC2/HAL/KEYPAD/keypad.o 

C_DEPS += \
./MC2/HAL/KEYPAD/keypad.d 


# Each subdirectory must supply rules for building sources it contributes
MC2/HAL/KEYPAD/%.o: ../MC2/HAL/KEYPAD/%.c MC2/HAL/KEYPAD/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


