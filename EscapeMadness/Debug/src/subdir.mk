################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/EscapeMadness.cpp 

OBJS += \
./src/EscapeMadness.o 

CPP_DEPS += \
./src/EscapeMadness.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/ -I/usr/include/c++/4.7.1 -I/usr/include/c++/4.7 -O0 -g3 -Wall -c -fmessage-length=0 -lm -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


