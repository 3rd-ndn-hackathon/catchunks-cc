################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../tools/chunks/catchunks/aimd-rtt-estimator.cpp \
../tools/chunks/catchunks/aimd-statistics-collector.cpp \
../tools/chunks/catchunks/consumer.cpp \
../tools/chunks/catchunks/data-fetcher.cpp \
../tools/chunks/catchunks/discover-version-fixed.cpp \
../tools/chunks/catchunks/discover-version-iterative.cpp \
../tools/chunks/catchunks/discover-version.cpp \
../tools/chunks/catchunks/ndncatchunks.cpp \
../tools/chunks/catchunks/options.cpp \
../tools/chunks/catchunks/pipeline-interests-aimd.cpp \
../tools/chunks/catchunks/pipeline-interests-fixed-window.cpp \
../tools/chunks/catchunks/pipeline-interests.cpp 

OBJS += \
./tools/chunks/catchunks/aimd-rtt-estimator.o \
./tools/chunks/catchunks/aimd-statistics-collector.o \
./tools/chunks/catchunks/consumer.o \
./tools/chunks/catchunks/data-fetcher.o \
./tools/chunks/catchunks/discover-version-fixed.o \
./tools/chunks/catchunks/discover-version-iterative.o \
./tools/chunks/catchunks/discover-version.o \
./tools/chunks/catchunks/ndncatchunks.o \
./tools/chunks/catchunks/options.o \
./tools/chunks/catchunks/pipeline-interests-aimd.o \
./tools/chunks/catchunks/pipeline-interests-fixed-window.o \
./tools/chunks/catchunks/pipeline-interests.o 

CPP_DEPS += \
./tools/chunks/catchunks/aimd-rtt-estimator.d \
./tools/chunks/catchunks/aimd-statistics-collector.d \
./tools/chunks/catchunks/consumer.d \
./tools/chunks/catchunks/data-fetcher.d \
./tools/chunks/catchunks/discover-version-fixed.d \
./tools/chunks/catchunks/discover-version-iterative.d \
./tools/chunks/catchunks/discover-version.d \
./tools/chunks/catchunks/ndncatchunks.d \
./tools/chunks/catchunks/options.d \
./tools/chunks/catchunks/pipeline-interests-aimd.d \
./tools/chunks/catchunks/pipeline-interests-fixed-window.d \
./tools/chunks/catchunks/pipeline-interests.d 


# Each subdirectory must supply rules for building sources it contributes
tools/chunks/catchunks/%.o: ../tools/chunks/catchunks/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__cplusplus=201103L -I/usr/local/include -I/usr/include -I/usr/include/c++ -I/usr/include/c++/5 -I/usr/include/c++/5/bits -I/usr/include/x86_64-linux-gnu -I/usr/include/x86_64-linux-gnu/bits -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


