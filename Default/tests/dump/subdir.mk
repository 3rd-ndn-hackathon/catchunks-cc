################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../tests/dump/ndndump.t.cpp 

OBJS += \
./tests/dump/ndndump.t.o 

CPP_DEPS += \
./tests/dump/ndndump.t.d 


# Each subdirectory must supply rules for building sources it contributes
tests/dump/%.o: ../tests/dump/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__cplusplus=201103L -I/usr/local/include -I/usr/include -I/usr/include/c++ -I/usr/include/c++/5 -I/usr/include/c++/5/bits -I/usr/include/x86_64-linux-gnu -I/usr/include/x86_64-linux-gnu/bits -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


