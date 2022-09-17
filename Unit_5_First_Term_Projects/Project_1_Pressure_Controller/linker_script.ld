/* list of memory sections */

MEMORY
{
	flash (RX) : ORIGIN = 0x08000000, LENGTH = 32K
	sram (RWX) : ORIGIN = 0x20000000, LENGTH = 10K
}

/* Entry Point */
ENTRY(Reset_Handler)

/* list of output sections */
SECTIONS
{
	.text : {
		*(.vectors*)
		*(.text*)
		KEEP(*(.init))
        KEEP(*(.fini))
		__text_end__ = . ;
	} > flash

	.rodata : {
	. = ALIGN(4);
	*(.rodata)
	*(.rodata*)
	. = ALIGN(4);
	} > flash

	.data :
	{
		__data_start__ = . ;		
        *(vtable)
        *(.data*)

        . = ALIGN(4);
        /* preinit data */
        KEEP(*(.preinit_array))

        . = ALIGN(4);
        /* init data */
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))

        . = ALIGN(4);
        /* finit data */
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
		
		. = ALIGN(4) ;
		__data_end__ = . ;
	}> sram AT> flash

	.bss :
	{
		__bss_start__ = . ;
		*(.bss*)
		*(COMMON)
		. = ALIGN(4) ;
		__bss_end__ = . ;
		. = ALIGN(4) ;
		. = . + 0x1000 ;
		__stack_top__ = . ;
	} > sram
}