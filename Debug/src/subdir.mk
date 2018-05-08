################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/BMP180.c \
../src/I2C1.c \
../src/Timer.c \
../src/UART1.c \
../src/hal_entry.c 

OBJS += \
./src/BMP180.o \
./src/I2C1.o \
./src/Timer.o \
./src/UART1.o \
./src/hal_entry.o 

C_DEPS += \
./src/BMP180.d \
./src/I2C1.d \
./src/Timer.d \
./src/UART1.d \
./src/hal_entry.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	C:\Renesas\e2_studio\eclipse\../Utilities/isdebuild arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g3 -D_RENESAS_SYNERGY_ -I"C:\Renesas\workspace\SK_S7G2_I2C\synergy_cfg\ssp_cfg\bsp" -I"C:\Renesas\workspace\SK_S7G2_I2C\synergy_cfg\ssp_cfg\driver" -I"C:\Renesas\workspace\SK_S7G2_I2C\synergy\ssp\inc" -I"C:\Renesas\workspace\SK_S7G2_I2C\synergy\ssp\inc\bsp" -I"C:\Renesas\workspace\SK_S7G2_I2C\synergy\ssp\inc\bsp\cmsis\Include" -I"C:\Renesas\workspace\SK_S7G2_I2C\synergy\ssp\inc\driver\api" -I"C:\Renesas\workspace\SK_S7G2_I2C\synergy\ssp\inc\driver\instances" -I"C:\Renesas\workspace\SK_S7G2_I2C\src" -I"C:\Renesas\workspace\SK_S7G2_I2C\src\synergy_gen" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" -x c "$<"
	@echo 'Finished building: $<'
	@echo ' '


