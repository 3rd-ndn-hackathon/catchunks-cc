################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm

# All of the sources participating in the build are defined here
-include sources.mk
-include tools/ping/server/subdir.mk
-include tools/ping/client/subdir.mk
-include tools/pib/encoding/subdir.mk
-include tools/pib/subdir.mk
-include tools/peek/ndnpeek/subdir.mk
-include tools/peek/subdir.mk
-include tools/dump/subdir.mk
-include tools/dissect/subdir.mk
-include tools/chunks/putchunks/subdir.mk
-include tools/chunks/catchunks/subdir.mk
-include tests/ping/server/subdir.mk
-include tests/ping/client/subdir.mk
-include tests/ping/subdir.mk
-include tests/pib/subdir.mk
-include tests/peek/subdir.mk
-include tests/dump/subdir.mk
-include tests/chunks/subdir.mk
-include tests/subdir.mk
-include core/subdir.mk
-include build/tools/ping/server/subdir.mk
-include build/tools/ping/client/subdir.mk
-include build/tools/pib/encoding/subdir.mk
-include build/tools/pib/subdir.mk
-include build/tools/peek/ndnpeek/subdir.mk
-include build/tools/peek/subdir.mk
-include build/tools/dump/subdir.mk
-include build/tools/dissect/subdir.mk
-include build/tools/chunks/putchunks/subdir.mk
-include build/tools/chunks/catchunks/subdir.mk
-include build/core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: ndn-tools

# Tool invocations
ndn-tools: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++  -o "ndn-tools" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(C_UPPER_DEPS)$(CXX_DEPS)$(OBJS)$(CPP_DEPS)$(C_DEPS) ndn-tools
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
