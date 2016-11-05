################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../tests/chunks/aimd-rtt-estimator.t.cpp \
../tests/chunks/consumer.t.cpp \
../tests/chunks/discover-version-fixed.t.cpp \
../tests/chunks/discover-version-iterative.t.cpp \
../tests/chunks/pipeline-interests-aimd.t.cpp \
../tests/chunks/pipeline-interests-fixed-window.t.cpp \
../tests/chunks/producer.t.cpp 

OBJS += \
./tests/chunks/aimd-rtt-estimator.t.o \
./tests/chunks/consumer.t.o \
./tests/chunks/discover-version-fixed.t.o \
./tests/chunks/discover-version-iterative.t.o \
./tests/chunks/pipeline-interests-aimd.t.o \
./tests/chunks/pipeline-interests-fixed-window.t.o \
./tests/chunks/producer.t.o 

CPP_DEPS += \
./tests/chunks/aimd-rtt-estimator.t.d \
./tests/chunks/consumer.t.d \
./tests/chunks/discover-version-fixed.t.d \
./tests/chunks/discover-version-iterative.t.d \
./tests/chunks/pipeline-interests-aimd.t.d \
./tests/chunks/pipeline-interests-fixed-window.t.d \
./tests/chunks/producer.t.d 


# Each subdirectory must supply rules for building sources it contributes
tests/chunks/%.o: ../tests/chunks/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__cplusplus=201103L -I/usr/local/include -I/usr/include -I/usr/include/c++ -I/usr/include/c++/5 -I/usr/include/c++/5/bits -I/usr/include/x86_64-linux-gnu -I/usr/include/x86_64-linux-gnu/bits -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


