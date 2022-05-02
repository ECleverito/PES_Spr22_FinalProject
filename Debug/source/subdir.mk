################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/IR_pin.c \
../source/LEDs.c \
../source/PES_Spr22_FinalProject.c \
../source/TPM.c \
../source/UART.c \
../source/cbfifo.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/sysclock.c 

OBJS += \
./source/IR_pin.o \
./source/LEDs.o \
./source/PES_Spr22_FinalProject.o \
./source/TPM.o \
./source/UART.o \
./source/cbfifo.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/sysclock.o 

C_DEPS += \
./source/IR_pin.d \
./source/LEDs.d \
./source/PES_Spr22_FinalProject.d \
./source/TPM.d \
./source/UART.d \
./source/cbfifo.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/sysclock.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\erich\Documents\MCUXpressoIDE_11.2.0_4120\workspace\PES_Spr22_FinalProject\board" -I"C:\Users\erich\Documents\MCUXpressoIDE_11.2.0_4120\workspace\PES_Spr22_FinalProject\source" -I"C:\Users\erich\Documents\MCUXpressoIDE_11.2.0_4120\workspace\PES_Spr22_FinalProject" -I"C:\Users\erich\Documents\MCUXpressoIDE_11.2.0_4120\workspace\PES_Spr22_FinalProject\drivers" -I"C:\Users\erich\Documents\MCUXpressoIDE_11.2.0_4120\workspace\PES_Spr22_FinalProject\CMSIS" -I"C:\Users\erich\Documents\MCUXpressoIDE_11.2.0_4120\workspace\PES_Spr22_FinalProject\utilities" -I"C:\Users\erich\Documents\MCUXpressoIDE_11.2.0_4120\workspace\PES_Spr22_FinalProject\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


