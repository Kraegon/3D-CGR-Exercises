################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Camera.cpp \
../src/Keyboard.cpp \
../src/Level.cpp \
../src/ObjModel.cpp \
../src/main.cpp \
../src/texture_loader.cpp 

OBJS += \
./src/Camera.o \
./src/Keyboard.o \
./src/Level.o \
./src/ObjModel.o \
./src/main.o \
./src/texture_loader.o 

CPP_DEPS += \
./src/Camera.d \
./src/Keyboard.d \
./src/Level.d \
./src/ObjModel.d \
./src/main.d \
./src/texture_loader.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


