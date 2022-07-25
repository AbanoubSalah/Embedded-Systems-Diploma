#include "platform_types.h"

#define STACK_START_SP 0x2000100

extern uint32 _stack_top;
extern uint32 _S_DATA;
extern uint32 _E_DATA;
extern uint32 _S_bss;
extern uint32 _E_bss;
extern uint32 _E_text;

extern sint32 main(void);
void Rest_Handler(void);

void Default_Handler()
{
	Rest_Handler();
}

void NMI_Handler(void) __attribute__ ((weak, alias ("Default_Handler")));
void H_fault_Handler(void) __attribute__ ((weak, alias ("Default_Handler")));
void MM_Fault_Handler(void) __attribute__ ((weak, alias ("Default_Handler")));
void Bus_Fault(void) __attribute__ ((weak, alias ("Default_Handler")));
void Usage_Fault_Handler(void) __attribute__ ((weak, alias ("Default_Handler")));

uint32 vectors[] __attribute__((section(".vectors"))) = {
(uint32) &_stack_top,
(uint32) &Rest_Handler,
(uint32) &NMI_Handler,
(uint32) &H_fault_Handler,
(uint32) &MM_Fault_Handler,
(uint32) &Bus_Fault,
(uint32) &Usage_Fault_Handler,
};

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
