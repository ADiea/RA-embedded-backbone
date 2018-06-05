################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../src/application.c" \

C_SRCS += \
../src/application.c \

OBJS_OS_FORMAT += \
./src/application.o \

C_DEPS_QUOTED += \
"./src/application.d" \

OBJS += \
./src/application.o \

OBJS_QUOTED += \
"./src/application.o" \

C_DEPS += \
./src/application.d \


# Each subdirectory must supply rules for building sources it contributes
src/application.o: ../src/application.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/application.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "src/application.o" "$<"
	@echo 'Finished building: $<'
	@echo ' '


