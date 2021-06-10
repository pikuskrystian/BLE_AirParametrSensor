################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../startup/startup_QN908XC.S 

OBJS += \
./startup/startup_QN908XC.o 


# Each subdirectory must supply rules for building sources it contributes
startup/%.o: ../startup/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: MCU Assembler'
	arm-none-eabi-gcc -c -x assembler-with-cpp -D__REDLIB__ -I"/Users/ki_09/Desktop/IoT_Lab13/board" -I"/Users/ki_09/Desktop/IoT_Lab13/source" -I"/Users/ki_09/Desktop/IoT_Lab13" -I"/Users/ki_09/Desktop/IoT_Lab13/CMSIS" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/OSAbstraction/Interface" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/Flash/Internal" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/GPIO" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/Keyboard/Interface" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/LED/Interface" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/common" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/MemManager/Interface" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/Messaging/Interface" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/Panic/Interface" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/RNG/Interface" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/NVM/Interface" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/NVM/Source" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/SerialManager/Interface" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/SerialManager/Source/UART_Adapter" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/SerialManager/Source/SPI_Adapter" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/SerialManager/Source/I2C_Adapter" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/TimersManager/Interface" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/TimersManager/Source" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/ModuleInfo" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/FunctionLib" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/Lists" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/SecLib" -I"/Users/ki_09/Desktop/IoT_Lab13/bluetooth/host/interface" -I"/Users/ki_09/Desktop/IoT_Lab13/source/common" -I"/Users/ki_09/Desktop/IoT_Lab13/bluetooth/host/config" -I"/Users/ki_09/Desktop/IoT_Lab13/bluetooth/controller/interface" -I"/Users/ki_09/Desktop/IoT_Lab13/bluetooth/hci_transport/interface" -I"/Users/ki_09/Desktop/IoT_Lab13/source/common/gatt_db/macros" -I"/Users/ki_09/Desktop/IoT_Lab13/source/common/gatt_db" -I"/Users/ki_09/Desktop/IoT_Lab13/bluetooth/profiles/battery" -I"/Users/ki_09/Desktop/IoT_Lab13/bluetooth/profiles/device_info" -I"/Users/ki_09/Desktop/IoT_Lab13/bluetooth/profiles/private_profile" -I"/Users/ki_09/Desktop/IoT_Lab13/framework/MWSCoexistence/Interface" -I"/Users/ki_09/Desktop/IoT_Lab13/drivers" -I"/Users/ki_09/Desktop/IoT_Lab13/utilities" -g3 -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -D__REDLIB__ -specs=redlib.specs -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


