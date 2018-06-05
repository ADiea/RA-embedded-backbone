################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS_QUOTED += \
"../src/sys/startup_code/startup_S32K144.S" \

S_UPPER_SRCS += \
../src/sys/startup_code/startup_S32K144.S \

OBJS_OS_FORMAT += \
./src/sys/startup_code/startup_S32K144.o \

OBJS += \
./src/sys/startup_code/startup_S32K144.o \

OBJS_QUOTED += \
"./src/sys/startup_code/startup_S32K144.o" \


# Each subdirectory must supply rules for building sources it contributes
src/sys/startup_code/startup_S32K144.o: ../src/sys/startup_code/startup_S32K144.S
	@echo 'Building file: $<'
	@echo 'Executing target #11 $<'
	@echo 'Invoking: Standard S32DS Assembler'
	arm-none-eabi-gcc "@src/sys/startup_code/startup_S32K144.args" -o "src/sys/startup_code/startup_S32K144.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


