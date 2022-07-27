#include "platform_types.h"

//Registers addresses
#define RCC_BASE       0x40021000
#define GPIOA_BASE     0x40010800
#define RCC_APB2ENR    *( vuint32_t * )( RCC_BASE    + 0x18 )
#define GPIOA_CRH      *( vuint32_t * )( GPIOA_BASE  + 0x04 )
#define GPIOA_ODR      *( vuint32_t * )( GPIOA_BASE  + 0x0C )

//Registers Bits Masks
#define RCC_MASK		0x00000004
#define CRH_RST_MASK 	0x00F00000
#define CRH_SET_MASK 	0x00200000

typedef union
{
	vuint32_t          Port_A;
	struct
	{
		vuint32_t     reversed:13;
		vuint32_t     pin_13:1;
	}Pin;
}R_ODR_t;

volatile R_ODR_t*  R_ODR =  ( volatile R_ODR_t* )( GPIOA_BASE + 0x0C );
uint8 g_variables[3] = {1, 2, 3};
uint8 const const_variables[3] = {1, 2, 3};

sint32 main(void)
{
	RCC_APB2ENR |=  (RCC_MASK);
	GPIOA_CRH   &= ~(CRH_RST_MASK);
	GPIOA_CRH   |=  (CRH_SET_MASK);

	while(1)
	{
		R_ODR->Pin.pin_13 = TRUE;
		for(vint32_t i = 0; i < 100000; ++i);

		R_ODR->Pin.pin_13 = FALSE;
		for(vint32_t i = 0; i < 100000; ++i);
	}
	
	return 0;
}
