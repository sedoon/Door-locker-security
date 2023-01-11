################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../human\ interface/HAL/EEPROM/external_eeprom.c 

OBJS += \
./human\ interface/HAL/EEPROM/external_eeprom.o 

C_DEPS += \
./human\ interface/HAL/EEPROM/external_eeprom.d 


# Each subdirectory must supply rules for building sources it contributes
human\ interface/HAL/EEPROM/external_eeprom.o: ../human\ interface/HAL/EEPROM/external_eeprom.c human\ interface/HAL/EEPROM/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"human interface/HAL/EEPROM/external_eeprom.d" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


