###############################################################################
# Makefile for the project wiz-web
###############################################################################

## General Flags
PROJECT = wiz-web
MCU = atmega128
TARGET = simple_tcp.elf
CC = avr-gcc.exe

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99 -Os -funsigned-char
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=simple_tcp.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Include Directories
INCLUDES = -I"D:\work\project\2008\WIZ_EmbeddedWebserver\FW\firm_rev04\main\ex02_simple_tcp\..\..\mcu" 

## Objects that must be built in order to link
OBJECTS = evb.o socket.o w5300.o main.o delay.o serial.o wiz_util.o lcd.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) simple_tcp.hex simple_tcp.eep simple_tcp.lss size

## Compile
evb.o: ../../../evb/evb.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

socket.o: ../../../iinchip/socket.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

w5300.o: ../../../iinchip/w5300.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

main.o: ../main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

delay.o: ../../../mcu/delay.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

serial.o: ../../../mcu/serial.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

wiz_util.o: ../../../util/wiz_util.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

lcd.o: ../../../evb/lcd.c
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
	-rm -rf $(OBJECTS) simple_tcp.elf dep/* simple_tcp.hex simple_tcp.eep simple_tcp.lss simple_tcp.map


## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

