################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../board/board.c \
../board/clock_config.c \
../board/gpio_pins.c \
../board/pin_mux.c \
../board/rco32k_calibration.c 

OBJS += \
./board/board.o \
./board/clock_config.o \
./board/gpio_pins.o \
./board/pin_mux.o \
./board/rco32k_calibration.o 

C_DEPS += \
./board/board.d \
./board/clock_config.d \
./board/gpio_pins.d \
./board/pin_mux.d \
./board/rco32k_calibration.d 


# Each subdirectory must supply rules for building sources it contributes
board/%.o: ../board/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_QN9080C_cm4 -DCPU_QN9080C -DDEBUG -DCPU_QN908X=1 -DCFG_BLE_PRJ=1 -DSDK_DEBUGCONSOLE=1 -DPRINTF_FLOAT_ENABLE=1 -D__MCUXPRESSO -D__USE_CMSIS -I"/Users/ki_09/Desktop/IoT_Lab13/board" -I"/Users/ki_09/Desktop/IoT_Lab13/source" -I"/Users/ki_09/Desktop/IoT_Lab13" -I"/Users/ki_09/Desktop/IoT_Lab13/CMSIS" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/OSAbstraction/Interface" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/Flash/Internal" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/GPIO" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/Keyboard/Interface" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/LED/Interface" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/common" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/MemManager/Interface" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/Messaging/Interface" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/Panic/Interface" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/RNG/Interface" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/NVM/Interface" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/NVM/Source" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/SerialManager/Interface" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/SerialManager/Source/UART_Adapter" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/SerialManager/Source/SPI_Adapter" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/SerialManager/Source/I2C_Adapter" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/TimersManager/Interface" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/TimersManager/Source" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/ModuleInfo" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/FunctionLib" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/Lists" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/SecLib" -I"/Users/ki_09/Desktop/IoT_Lab13/bluetooth/host/interface" -I"/Users/ki_09/Desktop/IoT_Lab13/source/common" -I"/Users/ki_09/Desktop/IoT_Lab13/bluetooth/host/config" -I"/Users/ki_09/Desktop/IoT_Lab13/bluetooth/controller/interface" -I"/Users/ki_09/Desktop/IoT_Lab13/bluetooth/hci_transport/interface" -I"/Users/ki_09/Desktop/IoT_Lab13/source/common/gatt_db/macros" -I"/Users/ki_09/Desktop/IoT_Lab13/source/common/gatt_db" -I"/Users/ki_09/Desktop/IoT_Lab13/bluetooth/profiles/battery" -I"/Users/ki_09/Desktop/IoT_Lab13/bluetooth/profiles/device_info" -I"/Users/ki_09/Desktop/IoT_Lab13/bluetooth/profiles/private_profile" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/MWSCoexistence/Interface" -I"/Users/ki_09/Desktop/IoT_Lab13/drivers" -I"/Users/ki_09/Desktop/IoT_Lab13/utilities" -O0 -fno-common -g -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -imacros "/Users/ki_09/Desktop/IoT_Lab13/source/app_preinclude.h" -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


