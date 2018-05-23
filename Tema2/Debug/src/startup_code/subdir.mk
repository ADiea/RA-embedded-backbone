################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS_QUOTED += \
"../src/startup_code/startup_S32K144.S" \

S_UPPER_SRCS += \
../src/startup_code/startup_S32K144.S \

OBJS_OS_FORMAT += \
./src/startup_code/startup_S32K144.o \

OBJS += \
./src/startup_code/startup_S32K144.o \

OBJS_QUOTED += \
"./src/startup_code/startup_S32K144.o" \


# Each subdirectory must supply rules for building sources it contributes
src/startup_code/startup_S32K144.o: ../src/startup_code/startup_S32K144.S
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: Standard S32DS Assembler'
	arm-none-eabi-gcc "@src/startup_code/startup_S32K144.args" -o "src/startup_code/startup_S32K144.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


