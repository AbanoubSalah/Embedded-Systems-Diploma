CC = arm-none-eabi-
CFLAGS = -mcpu=cortex-m3 -gdwarf-2
INCS =-I.
LIBS =
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
AS = $(wildcard *.s)
AsOBJ = $(As:.s=.o)

all: learn_in_depth_cortexM3.hex

%.o: %.s
	$(CC)as.exe $(CFLAGS) $< -o $@
	
%.o: %.c
	$(CC)gcc.exe $(CFLAGS) $(INCS) -c $< -o $@

learn_in_depth.elf: $(OBJ) $(AsOBJ)
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) $(AsOBJ) -o $@ -Map=map_file.map

learn_in_depth_cortexM3.hex: learn_in_depth.elf
	$(CC)objcopy.exe -O binary $< $@

clean:
	rm -rf *.o *~ *.elf *.hex
	@echo "Everything clean"