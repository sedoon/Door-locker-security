################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../human\ interface/MCAL/PWM/pwm_timer0.c 

OBJS += \
./human\ interface/MCAL/PWM/pwm_timer0.o 

C_DEPS += \
./human\ interface/MCAL/PWM/pwm_timer0.d 


# Each subdirectory must supply rules for building sources it contributes
human\ interface/MCAL/PWM/pwm_timer0.o: ../human\ interface/MCAL/PWM/pwm_timer0.c human\ interface/MCAL/PWM/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"human interface/MCAL/PWM/pwm_timer0.d" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


