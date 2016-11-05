################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../tools/pib/cert-publisher.cpp \
../tools/pib/default-query-processor.cpp \
../tools/pib/delete-query-processor.cpp \
../tools/pib/get-query-processor.cpp \
../tools/pib/key-cache.cpp \
../tools/pib/list-query-processor.cpp \
../tools/pib/ndn-pib.cpp \
../tools/pib/pib-db.cpp \
../tools/pib/pib-validator.cpp \
../tools/pib/pib.cpp \
../tools/pib/response-cache.cpp \
../tools/pib/update-query-processor.cpp 

OBJS += \
./tools/pib/cert-publisher.o \
./tools/pib/default-query-processor.o \
./tools/pib/delete-query-processor.o \
./tools/pib/get-query-processor.o \
./tools/pib/key-cache.o \
./tools/pib/list-query-processor.o \
./tools/pib/ndn-pib.o \
./tools/pib/pib-db.o \
./tools/pib/pib-validator.o \
./tools/pib/pib.o \
./tools/pib/response-cache.o \
./tools/pib/update-query-processor.o 

CPP_DEPS += \
./tools/pib/cert-publisher.d \
./tools/pib/default-query-processor.d \
./tools/pib/delete-query-processor.d \
./tools/pib/get-query-processor.d \
./tools/pib/key-cache.d \
./tools/pib/list-query-processor.d \
./tools/pib/ndn-pib.d \
./tools/pib/pib-db.d \
./tools/pib/pib-validator.d \
./tools/pib/pib.d \
./tools/pib/response-cache.d \
./tools/pib/update-query-processor.d 


# Each subdirectory must supply rules for building sources it contributes
tools/pib/%.o: ../tools/pib/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__cplusplus=201103L -I/usr/local/include -I/usr/include -I/usr/include/c++ -I/usr/include/c++/5 -I/usr/include/c++/5/bits -I/usr/include/x86_64-linux-gnu -I/usr/include/x86_64-linux-gnu/bits -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


