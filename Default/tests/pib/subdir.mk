################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../tests/pib/cert-publisher.t.cpp \
../tests/pib/key-cache.t.cpp \
../tests/pib/pib-db.t.cpp \
../tests/pib/pib-validator.t.cpp \
../tests/pib/pib.t.cpp \
../tests/pib/response-cache.t.cpp 

OBJS += \
./tests/pib/cert-publisher.t.o \
./tests/pib/key-cache.t.o \
./tests/pib/pib-db.t.o \
./tests/pib/pib-validator.t.o \
./tests/pib/pib.t.o \
./tests/pib/response-cache.t.o 

CPP_DEPS += \
./tests/pib/cert-publisher.t.d \
./tests/pib/key-cache.t.d \
./tests/pib/pib-db.t.d \
./tests/pib/pib-validator.t.d \
./tests/pib/pib.t.d \
./tests/pib/response-cache.t.d 


# Each subdirectory must supply rules for building sources it contributes
tests/pib/%.o: ../tests/pib/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__cplusplus=201103L -I/usr/local/include -I/usr/include -I/usr/include/c++ -I/usr/include/c++/5 -I/usr/include/c++/5/bits -I/usr/include/x86_64-linux-gnu -I/usr/include/x86_64-linux-gnu/bits -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


