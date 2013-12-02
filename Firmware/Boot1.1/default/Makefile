###############################################################################
# Makefile for the project Boot
###############################################################################

## General Flags
PROJECT = Boot
MCU = atmega128
TARGET = Boot.elf
CC = avr-gcc.exe

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2  -Os -funsigned-char
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Ttext=0x1e000  -Wl,-Map=Boot.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Objects that must be built in order to link
OBJECTS = delay.o flash.o main.o netloading.o socket.o serial.o w5300.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) Boot.hex Boot.eep Boot.lss size

## Compile
flash.o: ../flash.s
	$(CC) $(INCLUDES) $(ASMFLAGS) -c  $<

delay.o: ../delay.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

main.o: ../main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

netloading.o: ../netloading.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

socket.o: ../socket.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

serial.o: ../serial.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

w5300.o: ../w5300.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) Boot.elf dep/* Boot.hex Boot.eep Boot.lss Boot.map


## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

