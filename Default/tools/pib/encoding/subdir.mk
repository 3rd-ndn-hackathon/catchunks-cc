################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../tools/pib/encoding/default-param.cpp \
../tools/pib/encoding/delete-param.cpp \
../tools/pib/encoding/get-param.cpp \
../tools/pib/encoding/list-param.cpp \
../tools/pib/encoding/pib-encoding.cpp \
../tools/pib/encoding/update-param.cpp 

OBJS += \
./tools/pib/encoding/default-param.o \
./tools/pib/encoding/delete-param.o \
./tools/pib/encoding/get-param.o \
./tools/pib/encoding/list-param.o \
./tools/pib/encoding/pib-encoding.o \
./tools/pib/encoding/update-param.o 

CPP_DEPS += \
./tools/pib/encoding/default-param.d \
./tools/pib/encoding/delete-param.d \
./tools/pib/encoding/get-param.d \
./tools/pib/encoding/list-param.d \
./tools/pib/encoding/pib-encoding.d \
./tools/pib/encoding/update-param.d 


# Each subdirectory must supply rules for building sources it contributes
tools/pib/encoding/%.o: ../tools/pib/encoding/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -D__cplusplus=201103L -I/usr/local/include -I/usr/include -I/usr/include/c++ -I/usr/include/c++/5 -I/usr/include/c++/5/bits -I/usr/include/x86_64-linux-gnu -I/usr/include/x86_64-linux-gnu/bits -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


