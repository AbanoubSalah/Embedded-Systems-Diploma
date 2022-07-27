#include "platform_types.h"

//Registers addresses
#define SYSCTL_RCGC2_R			(*((vuint32_t *) 0x400FE108))
#define GPIO_PORTF_DATA_R 		(*((vuint32_t *) 0x400253FC))
#define GPIO_PORTF_DIR_R 		(*((vuint32_t *) 0x40025400))
#define GPIO_PORTF_DEN_R 		(*((vuint32_t *) 0x4002551C))

//Registers Bits Masks
#define SYSCTL_GPIOF_MASK		0x00000020
#define LED_MASK 				0x00000008

uint32 main(void)
{
	vuint32_t delay_count;
	SYSCTL_RCGC2_R = SYSCTL_GPIOF_MASK;
	for(delay_count = 0; delay_count < 200; ++delay_count);
	GPIO_PORTF_DIR_R |= LED_MASK;
	GPIO_PORTF_DEN_R |= LED_MASK;

	while(1)
	{
		GPIO_PORTF_DATA_R |= LED_MASK;
		for(delay_count = 0; delay_count < 200000; ++delay_count);

		GPIO_PORTF_DATA_R &= ~(LED_MASK);
		for(delay_count = 0; delay_count < 200000; ++delay_count);
	}
	
	return 0;
}
