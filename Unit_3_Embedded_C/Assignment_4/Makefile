CC = arm-none-eabi-
CFLAGS = -mcpu=cortex-m4 -gdwarf-2 -g
INCS =-I.
LIBS =
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
AS = $(wildcard *.s)
AsOBJ = $(As:.s=.o)
Project_name = unit3_lab4_cortexM4

all: $(Project_name).bin
	@echo "========Build is Done========="
	
%.o: %.c
	$(CC)gcc.exe $(CFLAGS) $(INCS) -c $< -o $@

$(Project_name).elf: $(OBJ)
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) $(AsOBJ) -o $@ -Map=map_file.map
	cp $(Project_name).elf $(Project_name).axf

$(Project_name).bin: $(Project_name).elf
	$(CC)objcopy.exe -O binary $< $@

clean_all:
	rm *.o *.elf *.bin

clean:
	rm *.elf *.bin