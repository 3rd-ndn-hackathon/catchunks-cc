################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../tools/dissect/main.cpp \
../tools/dissect/ndn-dissect.cpp 

OBJS += \
./tools/dissect/main.o \
./tools/dissect/ndn-dissect.o 

CPP_DEPS += \
./tools/dissect/main.d \
./tools/dissect/ndn-dissect.d 


# Each subdirectory must supply rules for building sources it contributes
tools/dissect/%.o: ../tools/dissect/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__cplusplus=201103L -I/usr/local/include -I/usr/include -I/usr/include/c++ -I/usr/include/c++/5 -I/usr/include/c++/5/bits -I/usr/include/x86_64-linux-gnu -I/usr/include/x86_64-linux-gnu/bits -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


