################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MC1/HAL/DC_MOTOR/dc_motor.c 

OBJS += \
./MC1/HAL/DC_MOTOR/dc_motor.o 

C_DEPS += \
./MC1/HAL/DC_MOTOR/dc_motor.d 


# Each subdirectory must supply rules for building sources it contributes
MC1/HAL/DC_MOTOR/%.o: ../MC1/HAL/DC_MOTOR/%.c MC1/HAL/DC_MOTOR/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


