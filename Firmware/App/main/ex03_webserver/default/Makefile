###############################################################################
# Makefile for the project wiz-web
###############################################################################

## General Flags
PROJECT = wiz-web
MCU = atmega128
TARGET = wiz-web.elf
CC = avr-gcc

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
LDFLAGS +=  -Wl,-Map=wiz-web.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Include Directories
INCLUDES = -I"C:\Users\jbkim\Dropbox\Team OH\Github\WIZ200WEB\Firmware\App\main\ex03_webserver\..\..\mcu" 

## Objects that must be built in order to link
OBJECTS = evb.o dataflash.o romfile.o socket.o w5300.o httpd.o main.o task_config.o delay.o serial.o wiz_util.o lcd.o tc77.o timer.o dhcp.o dhcp_task.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) wiz-web.hex wiz-web.eep wiz-web.lss size

## Compile
evb.o: ../../../evb/evb.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

dataflash.o: ../../../evb/dataflash.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

romfile.o: ../../../evb/romfile.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

socket.o: ../../../iinchip/socket.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

w5300.o: ../../../iinchip/w5300.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

httpd.o: ../../../inet/httpd.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

main.o: ../main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

task_config.o: ../task_config.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

delay.o: ../../../mcu/delay.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

serial.o: ../../../mcu/serial.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

wiz_util.o: ../../../util/wiz_util.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

lcd.o: ../../../evb/lcd.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

tc77.o: ../../../evb/tc77.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

timer.o: ../../../mcu/timer.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

dhcp.o: ../../../inet/dhcp.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

dhcp_task.o: ../dhcp_task.c
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
	-rm -rf $(OBJECTS) wiz-web.elf dep/* wiz-web.hex wiz-web.eep wiz-web.lss wiz-web.map


## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

