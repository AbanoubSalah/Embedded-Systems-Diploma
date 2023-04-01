#------------------------------------------------------------------------------
# Make file for bulding section 2
#
# Use: make [TARGET]
#
# Build Targets:
#	   build: Build the whole project
#	   clean: Removes all make generated files
#
#------------------------------------------------------------------------------

BUILDDIR = build
TARGET = Section_2
SOURCES = main.c		  \
		  LCD/lcd.c		  \
		  Keypad/keypad.c \

INCLUDES = -I.			  \
		   -IKeypad/	  \
		   -ILCD/		  \

CC = avr-gcc
LD = avr-ld
SIZE = avr-size
OBJDUMP = avr-objdump
OBJCOPY = avr-objcopy
MCU = atmega32
OBJS := $(SOURCES:.c=.o)
CFLAGS = -O3 $(INCLUDES) -std=c99 -mmcu=$(MCU)

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
LDFLAGS += -Xlinker -Map=$(TARGET).map
endif

.PHONY: build clean
build : $(OBJS)
	$(CC) $(LDFLAGS) $(CFLAGS) $(SOURCES) -o $(TARGET).elf
	$(OBJCOPY) -I elf32-avr -O ihex $(TARGET).elf $(TARGET).hex
	$(SIZE) -Btd $(TARGET).elf $(OBJS)

%.i : %.c
	$(CC) -E $(CPPFLAGs) $(CFLAGS) -MF $@ $<
%.asm : %.c %.o
	$(CC) -S $(CFLAGS) $<
	$(OBJDUMP) -D -S $(word 2,$^) > $@
%.o : %.c
	$(CC) -c $< $(CFLAGS) -o $@

clean :
	rm -f $(OBJS) $(TARGET).elf $(TARGET).hex $(TARGET).map
