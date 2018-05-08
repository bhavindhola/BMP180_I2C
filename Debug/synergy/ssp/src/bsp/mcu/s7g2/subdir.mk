################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../synergy/ssp/src/bsp/mcu/s7g2/bsp_clocks.c \
../synergy/ssp/src/bsp/mcu/s7g2/bsp_group_irq.c \
../synergy/ssp/src/bsp/mcu/s7g2/bsp_irq.c \
../synergy/ssp/src/bsp/mcu/s7g2/bsp_locking.c \
../synergy/ssp/src/bsp/mcu/s7g2/bsp_register_protection.c \
../synergy/ssp/src/bsp/mcu/s7g2/bsp_rom_registers.c \
../synergy/ssp/src/bsp/mcu/s7g2/bsp_vbatt.c 

OBJS += \
./synergy/ssp/src/bsp/mcu/s7g2/bsp_clocks.o \
./synergy/ssp/src/bsp/mcu/s7g2/bsp_group_irq.o \
./synergy/ssp/src/bsp/mcu/s7g2/bsp_irq.o \
./synergy/ssp/src/bsp/mcu/s7g2/bsp_locking.o \
./synergy/ssp/src/bsp/mcu/s7g2/bsp_register_protection.o \
./synergy/ssp/src/bsp/mcu/s7g2/bsp_rom_registers.o \
./synergy/ssp/src/bsp/mcu/s7g2/bsp_vbatt.o 

C_DEPS += \
./synergy/ssp/src/bsp/mcu/s7g2/bsp_clocks.d \
./synergy/ssp/src/bsp/mcu/s7g2/bsp_group_irq.d \
./synergy/ssp/src/bsp/mcu/s7g2/bsp_irq.d \
./synergy/ssp/src/bsp/mcu/s7g2/bsp_locking.d \
./synergy/ssp/src/bsp/mcu/s7g2/bsp_register_protection.d \
./synergy/ssp/src/bsp/mcu/s7g2/bsp_rom_registers.d \
./synergy/ssp/src/bsp/mcu/s7g2/bsp_vbatt.d 


# Each subdirectory must supply rules for building sources it contributes
synergy/ssp/src/bsp/mcu/s7g2/%.o: ../synergy/ssp/src/bsp/mcu/s7g2/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	C:\Renesas\e2_studio\eclipse\../Utilities/isdebuild arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O2 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal  -g3 -D_RENESAS_SYNERGY_ -I"C:\Renesas\workspace\SK_S7G2_I2C\synergy_cfg\ssp_cfg\bsp" -I"C:\Renesas\workspace\SK_S7G2_I2C\synergy_cfg\ssp_cfg\driver" -I"C:\Renesas\workspace\SK_S7G2_I2C\synergy\ssp\inc" -I"C:\Renesas\workspace\SK_S7G2_I2C\synergy\ssp\inc\bsp" -I"C:\Renesas\workspace\SK_S7G2_I2C\synergy\ssp\inc\bsp\cmsis\Include" -I"C:\Renesas\workspace\SK_S7G2_I2C\synergy\ssp\inc\driver\api" -I"C:\Renesas\workspace\SK_S7G2_I2C\synergy\ssp\inc\driver\instances" -I"C:\Renesas\workspace\SK_S7G2_I2C\src" -I"C:\Renesas\workspace\SK_S7G2_I2C\src\synergy_gen" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" -x c "$<"
	@echo 'Finished building: $<'
	@echo ' '


