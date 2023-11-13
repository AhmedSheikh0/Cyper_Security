################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/UART/subdir.mk
-include MCAL/Port/subdir.mk
-include MCAL/GIE/subdir.mk
-include MCAL/DIO/subdir.mk
-include HAL/LCD2/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
NTI_USART_C.lss \

FLASH_IMAGE += \
NTI_USART_C.hex \

EEPROM_IMAGE += \
NTI_USART_C.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: NTI_USART_C.elf secondary-outputs

# Tool invocations
NTI_USART_C.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,NTI_USART_C.map -mmcu=atmega32 -o "NTI_USART_C.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

NTI_USART_C.lss: NTI_USART_C.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S NTI_USART_C.elf  >"NTI_USART_C.lss"
	@echo 'Finished building: $@'
	@echo ' '

NTI_USART_C.hex: NTI_USART_C.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex NTI_USART_C.elf  "NTI_USART_C.hex"
	@echo 'Finished building: $@'
	@echo ' '

NTI_USART_C.eep: NTI_USART_C.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex NTI_USART_C.elf  "NTI_USART_C.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: NTI_USART_C.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 NTI_USART_C.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) NTI_USART_C.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
