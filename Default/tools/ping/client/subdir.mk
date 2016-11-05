################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../tools/ping/client/ndn-ping.cpp \
../tools/ping/client/ping.cpp \
../tools/ping/client/statistics-collector.cpp \
../tools/ping/client/tracer.cpp 

OBJS += \
./tools/ping/client/ndn-ping.o \
./tools/ping/client/ping.o \
./tools/ping/client/statistics-collector.o \
./tools/ping/client/tracer.o 

CPP_DEPS += \
./tools/ping/client/ndn-ping.d \
./tools/ping/client/ping.d \
./tools/ping/client/statistics-collector.d \
./tools/ping/client/tracer.d 


# Each subdirectory must supply rules for building sources it contributes
tools/ping/client/%.o: ../tools/ping/client/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__cplusplus=201103L -I/usr/local/include -I/usr/include -I/usr/include/c++ -I/usr/include/c++/5 -I/usr/include/c++/5/bits -I/usr/include/x86_64-linux-gnu -I/usr/include/x86_64-linux-gnu/bits -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


