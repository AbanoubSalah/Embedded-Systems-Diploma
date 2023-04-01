/*******************************************************************************
 * @file startup.c
 * @brief This file is the implementation of the startup code for ARM Cortex 
 *
 * @author Abanoub Salah
 * @date July 27, 2022
 ******************************************************************************/

#include "platform_types.h"

extern uint32 __data_start__;
extern uint32 __data_end__;
extern uint32 __bss_start__;
extern uint32 __bss_end__;
extern uint32 __text_end__;
extern uint32 __stack_top__;

extern sint32 main(void);

void Reset_Handler(void);

void Default_Handler()
{
	Reset_Handler();
}

void NMI_Handler(void) __attribute__ ((weak, alias ("Default_Handler")));
void H_fault_Handler(void) __attribute__ ((weak, alias ("Default_Handler")));

void (* vectorTable[])() __attribute__((section(".vectors"))) = 
{
	(void (*)())((uint32) &(__stack_top__)),
	(void (*)())((uint32) &(Reset_Handler)),
	(void (*)())((uint32) &(NMI_Handler)),
	(void (*)())((uint32) &(H_fault_Handler)),
};

void Reset_Handler (void)
{
	/* copy data from ROM to RAM */
	uint32 DATA_size = (uint32 *) &(__data_end__) - (uint32 *) &(__data_start__);
	uint8 *P_src = (uint8 *) &(__text_end__);
	uint8 *P_dst = (uint8 *) &(__data_start__);

	for( uint32 i = 0; i < DATA_size; ++i)
	{
		*((uint8 *) P_dst++) = *((uint8*) P_src++);
	}

	/* initiate the .bss section with zeros */
	uint32 bss_size = (uint32 *) &(__bss_end__) - (uint32 *) &(__bss_start__);
	
	P_dst = (uint8 *) &(__bss_start__);
	
	for(uint32 i = 0; i < bss_size; ++i)
	{
		*((uint8 *) P_dst++) = (uint8) 0;
	}
	
	/* jump to main */
	main();
}

/*******************************************************************************
 * END OF FILE: startup.c
 ******************************************************************************/
