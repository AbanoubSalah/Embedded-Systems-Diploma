/*******************************************************************************
 * @file main.c
 * @brief This file is the main entry point
 *
 * @author Abanoub Salah
 * @date September 26, 2022
 ******************************************************************************/

typedef volatile unsigned char vuint8;
typedef unsigned int uint32;
typedef volatile unsigned int vuint32;

/* Atmega32 registers */
#define GPIO_BASE   		0x20
#define DDRC        		*(vuint8 *)(GPIO_BASE + 0x14)
#define PORTC       		*(vuint8 *)(GPIO_BASE + 0x15)

#define PC2     			2
#define PC3     			3
#define PC4     			4
#define PC5     			5
#define PC6     			6
#define PC7     			7

/* Local functions definition */
static void delay(uint32 count);

int main(void)
{
    /* Set pins direction as output */
    DDRC |= (1 << PC2) | (1 << PC3) | (1 << PC4) | (1 << PC5) | (1 << PC6) | (1 << PC7);
	
    while (1) 
    {
		vuint32 i, j;
		for(i = 0; i < 10; ++i)
		{
			for(j = 0; j < 10; ++j)
			{
				PORTC = ((i << 4) | 0xB);
				delay(360);
				PORTC = ((j << 4) | 0x7);
				delay(620);
			}
		}
    }
}

static void delay(uint32 count)
{
    vuint32 i, j;
    
    for(i = 0; i < count; ++i)
    {
        for(j = 0; j < count; ++j);
    }
}
