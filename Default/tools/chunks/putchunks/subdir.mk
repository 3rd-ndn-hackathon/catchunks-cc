################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../tools/chunks/putchunks/ndnputchunks.cpp \
../tools/chunks/putchunks/producer.cpp 

OBJS += \
./tools/chunks/putchunks/ndnputchunks.o \
./tools/chunks/putchunks/producer.o 

CPP_DEPS += \
./tools/chunks/putchunks/ndnputchunks.d \
./tools/chunks/putchunks/producer.d 


# Each subdirectory must supply rules for building sources it contributes
tools/chunks/putchunks/%.o: ../tools/chunks/putchunks/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__cplusplus=201103L -I/usr/local/include -I/usr/include -I/usr/include/c++ -I/usr/include/c++/5 -I/usr/include/c++/5/bits -I/usr/include/x86_64-linux-gnu -I/usr/include/x86_64-linux-gnu/bits -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


