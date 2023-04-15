################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../lcd.c \
../main.c \
../MCP3008.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
lcd.o \
main.o \
MCP3008.o

OBJS_AS_ARGS +=  \
lcd.o \
main.o \
MCP3008.o

C_DEPS +=  \
lcd.d \
main.d \
MCP3008.d

C_DEPS_AS_ARGS +=  \
lcd.d \
main.d \
MCP3008.d

OUTPUT_FILE_PATH +=mcp_adc_demo.elf

OUTPUT_FILE_PATH_AS_ARGS +=mcp_adc_demo.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler
./lcd.o: .././lcd.c
	@echo Building file: $<
	@echo Invoking: XC8 C Compiler : 2.32
	$(QUOTE)D:\Program Files\Microchip\xc8\v2.32\bin\xc8-cc.exe$(QUOTE)  -mcpu=ATmega8515  -mdfp="D:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.6.364\xc8"  -c -x c -funsigned-char -funsigned-bitfields -mext=cci -D__ATmega8515__ -DDEBUG  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

./main.o: .././main.c
	@echo Building file: $<
	@echo Invoking: XC8 C Compiler : 2.32
	$(QUOTE)D:\Program Files\Microchip\xc8\v2.32\bin\xc8-cc.exe$(QUOTE)  -mcpu=ATmega8515  -mdfp="D:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.6.364\xc8"  -c -x c -funsigned-char -funsigned-bitfields -mext=cci -D__ATmega8515__ -DDEBUG  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	

./MCP3008.o: .././MCP3008.c
	@echo Building file: $<
	@echo Invoking: XC8 C Compiler : 2.32
	$(QUOTE)D:\Program Files\Microchip\xc8\v2.32\bin\xc8-cc.exe$(QUOTE)  -mcpu=ATmega8515  -mdfp="D:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.6.364\xc8"  -c -x c -funsigned-char -funsigned-bitfields -mext=cci -D__ATmega8515__ -DDEBUG  -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	




# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking:  XC8 C Linker : 2.32
	$(QUOTE)D:\Program Files\Microchip\xc8\v2.32\bin\xc8-cc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -mcpu=ATmega8515  -mdfp="D:\Program Files (x86)\Atmel\Studio\7.0\Packs\atmel\ATmega_DFP\1.6.364\xc8"  -Wl,-Map="mcp_adc_demo.map" -funsigned-char -funsigned-bitfields -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -Og -ffunction-sections -fdata-sections -fpack-struct -fshort-enums --memorysummary,memoryfile.xml  
	@echo Finished building target: $@
	"D:\Program Files\Microchip\xc8\v2.32\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "mcp_adc_demo.elf" "mcp_adc_demo.hex"
	"D:\Program Files\Microchip\xc8\v2.32\bin\avr-objcopy.exe" -j .eeprom --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0 --no-change-warnings -O ihex "mcp_adc_demo.elf" "mcp_adc_demo.eep" || exit 0
	"D:\Program Files\Microchip\xc8\v2.32\bin\avr-objdump.exe" -h -S "mcp_adc_demo.elf" > "mcp_adc_demo.lss"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "mcp_adc_demo.elf" "mcp_adc_demo.hex" "mcp_adc_demo.eep" "mcp_adc_demo.map" "mcp_adc_demo.usersignatures" "mcp_adc_demo.a"  "mcp_adc_demo.lss"
	