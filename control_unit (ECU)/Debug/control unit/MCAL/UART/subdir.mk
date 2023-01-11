################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../control\ unit/MCAL/UART/uart.c 

OBJS += \
./control\ unit/MCAL/UART/uart.o 

C_DEPS += \
./control\ unit/MCAL/UART/uart.d 


# Each subdirectory must supply rules for building sources it contributes
control\ unit/MCAL/UART/uart.o: ../control\ unit/MCAL/UART/uart.c control\ unit/MCAL/UART/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"control unit/MCAL/UART/uart.d" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


