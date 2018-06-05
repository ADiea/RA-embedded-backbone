################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../src/sys/adc.c" \
"../src/sys/button.c" \
"../src/sys/delay.c" \
"../src/sys/gpio.c" \
"../src/sys/interrupt.c" \
"../src/sys/potentiometer.c" \
"../src/sys/rgbLED.c" \
"../src/sys/system.c" \
"../src/sys/timer.c" \

C_SRCS += \
../src/sys/adc.c \
../src/sys/button.c \
../src/sys/delay.c \
../src/sys/gpio.c \
../src/sys/interrupt.c \
../src/sys/potentiometer.c \
../src/sys/rgbLED.c \
../src/sys/system.c \
../src/sys/timer.c \

OBJS_OS_FORMAT += \
./src/sys/adc.o \
./src/sys/button.o \
./src/sys/delay.o \
./src/sys/gpio.o \
./src/sys/interrupt.o \
./src/sys/potentiometer.o \
./src/sys/rgbLED.o \
./src/sys/system.o \
./src/sys/timer.o \

C_DEPS_QUOTED += \
"./src/sys/adc.d" \
"./src/sys/button.d" \
"./src/sys/delay.d" \
"./src/sys/gpio.d" \
"./src/sys/interrupt.d" \
"./src/sys/potentiometer.d" \
"./src/sys/rgbLED.d" \
"./src/sys/system.d" \
"./src/sys/timer.d" \

OBJS += \
./src/sys/adc.o \
./src/sys/button.o \
./src/sys/delay.o \
./src/sys/gpio.o \
./src/sys/interrupt.o \
./src/sys/potentiometer.o \
./src/sys/rgbLED.o \
./src/sys/system.o \
./src/sys/timer.o \

OBJS_QUOTED += \
"./src/sys/adc.o" \
"./src/sys/button.o" \
"./src/sys/delay.o" \
"./src/sys/gpio.o" \
"./src/sys/interrupt.o" \
"./src/sys/potentiometer.o" \
"./src/sys/rgbLED.o" \
"./src/sys/system.o" \
"./src/sys/timer.o" \

C_DEPS += \
./src/sys/adc.d \
./src/sys/button.d \
./src/sys/delay.d \
./src/sys/gpio.d \
./src/sys/interrupt.d \
./src/sys/potentiometer.d \
./src/sys/rgbLED.d \
./src/sys/system.d \
./src/sys/timer.d \


# Each subdirectory must supply rules for building sources it contributes
src/sys/adc.o: ../src/sys/adc.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/sys/adc.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "src/sys/adc.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/sys/button.o: ../src/sys/button.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/sys/button.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "src/sys/button.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/sys/delay.o: ../src/sys/delay.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/sys/delay.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "src/sys/delay.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/sys/gpio.o: ../src/sys/gpio.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/sys/gpio.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "src/sys/gpio.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/sys/interrupt.o: ../src/sys/interrupt.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/sys/interrupt.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "src/sys/interrupt.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/sys/potentiometer.o: ../src/sys/potentiometer.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/sys/potentiometer.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "src/sys/potentiometer.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/sys/rgbLED.o: ../src/sys/rgbLED.c
	@echo 'Building file: $<'
	@echo 'Executing target #8 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/sys/rgbLED.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "src/sys/rgbLED.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/sys/system.o: ../src/sys/system.c
	@echo 'Building file: $<'
	@echo 'Executing target #9 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/sys/system.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "src/sys/system.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/sys/timer.o: ../src/sys/timer.c
	@echo 'Building file: $<'
	@echo 'Executing target #10 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/sys/timer.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "src/sys/timer.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


