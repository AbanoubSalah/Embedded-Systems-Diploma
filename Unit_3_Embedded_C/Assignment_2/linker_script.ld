/* entry point */
ENTRY(reset)

/* list of memory sections */
MEMORY
{
	Mem (rwx) : ORIGIN = 0x00000000, LENGTH = 64M
}

/* list of output sections */
SECTIONS
{
	. = 0x10000;
	.startup . :
	{
		startup.o(.text)
	}> Mem
	.text :
	{
		*(.text) *(.rodata)
	}> Mem
	.data :
	{
		*(.data)
	}> Mem
	.bss :
	{
		*(.bss) *(COMMON)
	}> Mem
	/* 4KB of Stack Memory */
	. = . + 0x1000;
	stack_top = .;
}