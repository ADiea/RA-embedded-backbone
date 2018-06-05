################################################################################
# Automatically-generated file. Do not edit!
################################################################################

#Progress monitor hint: 11
first : all
-include ../makefile.init

# This file contains definitions of environment variables used in the makefiles and .args files if exist.
-include makefile.local

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include linker_scripts/subdir.mk
-include src/subdir.mk
-include src/sys/subdir.mk
-include src/sys/startup_code/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
hello_s32k144.elf \

EXECUTABLES_QUOTED += \
"hello_s32k144.elf" \

EXECUTABLES_OS_FORMAT += \
hello_s32k144.elf \

SECONDARY_SIZE += \
hello_s32k144.siz \
hello_s32k144.siz \

SECONDARY_SIZE_QUOTED += \
"hello_s32k144.siz" \
"hello_s32k144.siz" \

SECONDARY_SIZE_OS_FORMAT += \
hello_s32k144.siz \
hello_s32k144.siz \

SECONDARY_SIZE += \
hello_s32k144.siz \
hello_s32k144.siz \

SECONDARY_SIZE_QUOTED += \
"hello_s32k144.siz" \
"hello_s32k144.siz" \

SECONDARY_SIZE_OS_FORMAT += \
hello_s32k144.siz \
hello_s32k144.siz \


# All Target
all: warning-messages explicit-dependencies hello_s32k144.elf secondary-outputs

# Tool invocations
hello_s32k144.elf: $(OBJS) C:/Users/Andrei/Desktop/prj/rinfacad/racad_bbone/RA-embedded-backbone/project/linker_scripts/S32K1xx_flash.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Executing target #12 $@'
	@echo 'Invoking: Standard S32DS C Linker'
	arm-none-eabi-gcc -o "hello_s32k144.elf" "@hello_s32k144.args"  $(USER_OBJS_QUOTED) $(LIBS_QUOTED)
	@echo 'Finished building target: $@'
	@echo ' '

hello_s32k144.siz: $(EXECUTABLES)
	@echo 'Executing target #13 $@'
	@echo 'Invoking: Standard S32DS Print Size'
	arm-none-eabi-size --format=berkeley $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) ./*/*/*.d ./*/*.d  ./*/*/*/*.o ./*/*/*.o ./*/*.o  $(SECONDARY_SIZE_QUOTED) $(EXECUTABLES_QUOTED)
	-@echo ' '

secondary-outputs: $(SECONDARY_SIZE) $(SECONDARY_SIZE)

.PHONY: all clean dependents explicit-dependencies warning-messages
.SECONDARY:

-include ../makefile.targets

explicit-dependencies: 

warning-messages: 

