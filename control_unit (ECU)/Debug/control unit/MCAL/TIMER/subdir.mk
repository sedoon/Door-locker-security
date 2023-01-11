################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../control\ unit/MCAL/TIMER/timer0.c \
../control\ unit/MCAL/TIMER/timer2.c 

OBJS += \
./control\ unit/MCAL/TIMER/timer0.o \
./control\ unit/MCAL/TIMER/timer2.o 

C_DEPS += \
./control\ unit/MCAL/TIMER/timer0.d \
./control\ unit/MCAL/TIMER/timer2.d 


# Each subdirectory must supply rules for building sources it contributes
control\ unit/MCAL/TIMER/timer0.o: ../control\ unit/MCAL/TIMER/timer0.c control\ unit/MCAL/TIMER/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"control unit/MCAL/TIMER/timer0.d" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

control\ unit/MCAL/TIMER/timer2.o: ../control\ unit/MCAL/TIMER/timer2.c control\ unit/MCAL/TIMER/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"control unit/MCAL/TIMER/timer2.d" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


