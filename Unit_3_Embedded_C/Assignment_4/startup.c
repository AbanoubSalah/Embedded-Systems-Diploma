#include "platform_types.h"

void Rest_Handler(void);
extern sint32 main(void);

void Default_Handler()
{
	Rest_Handler();
}

void NMI_Handler(void) __attribute__ ((weak, alias ("Default_Handler")));
void H_fault_Handler(void) __attribute__ ((weak, alias ("Default_Handler")));

// reserve stack size
static uint32 Stack_top[256]; //256*4 *1024 B

void (* const g_p_fn_Vectors[])() __attribute__((section(".vectors"))) = 
{
	(void (*)())((uint32)Stack_top + sizeof(Stack_top)),
	&Rest_Handler,
	&NMI_Handler,
	&H_fault_Handler,
};

extern uint32 _S_DATA;
extern uint32 _E_DATA;
extern uint32 _S_bss;
extern uint32 _E_bss;
extern uint32 _E_text;

void Rest_Handler (void)
{
	//copy data from ROM to RAM
	uint32 DATA_size = (uint8 *)&_E_DATA - (uint8 *)&_S_DATA;
	uint8 *P_src = (uint8 *)&_E_text;
	uint8 *P_dst = (uint8 *)&_S_DATA;
	for( uint32 i = 0; i < DATA_size; ++i)
	{
		*((uint8 *)P_dst++) = *((uint8*)P_src++);
	}

	//init the .bss with zero
	uint32 bss_size = (uint8 *)&_E_bss - (uint8 *)&_S_bss;
	
	P_dst = (uint8 *)&_S_bss;
	
	for(uint32 i = 0; i < bss_size; ++i)
	{
		*((uint8 *)P_dst++) = (uint8)0;
	}
	
	//jump to main (learn-in-depth)
	main();
}
