################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MC2/MCAL/UART/uart.c 

OBJS += \
./MC2/MCAL/UART/uart.o 

C_DEPS += \
./MC2/MCAL/UART/uart.d 


# Each subdirectory must supply rules for building sources it contributes
MC2/MCAL/UART/%.o: ../MC2/MCAL/UART/%.c MC2/MCAL/UART/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


