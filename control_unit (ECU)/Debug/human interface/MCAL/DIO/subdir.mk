################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../human\ interface/MCAL/DIO/gpio.c 

OBJS += \
./human\ interface/MCAL/DIO/gpio.o 

C_DEPS += \
./human\ interface/MCAL/DIO/gpio.d 


# Each subdirectory must supply rules for building sources it contributes
human\ interface/MCAL/DIO/gpio.o: ../human\ interface/MCAL/DIO/gpio.c human\ interface/MCAL/DIO/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"human interface/MCAL/DIO/gpio.d" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


