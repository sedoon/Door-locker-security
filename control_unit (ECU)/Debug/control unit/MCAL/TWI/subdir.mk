################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../control\ unit/MCAL/TWI/twi.c 

OBJS += \
./control\ unit/MCAL/TWI/twi.o 

C_DEPS += \
./control\ unit/MCAL/TWI/twi.d 


# Each subdirectory must supply rules for building sources it contributes
control\ unit/MCAL/TWI/twi.o: ../control\ unit/MCAL/TWI/twi.c control\ unit/MCAL/TWI/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"control unit/MCAL/TWI/twi.d" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


