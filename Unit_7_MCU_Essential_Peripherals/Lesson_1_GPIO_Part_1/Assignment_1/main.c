/*******************************************************************************
 * @file main.c
 *
 * @author Abanoub Salah
 *
 * @date September 25, 2022
 ******************************************************************************/

typedef volatile unsigned char vuint8;
typedef unsigned int uint32;
typedef volatile unsigned int vuint32;

/* Atmega32 registers */
#define GPIO_BASE   		0x20
#define DDRC        		(*(vuint8 *)(GPIO_BASE + 0x14))
#define PORTC       		(*(vuint8 *)(GPIO_BASE + 0x15))

#define PC0     			0
#define PC1     			1
#define PC2     			2
#define PC3     			3

/* Application used pins defs */
#define LED1     			PC0
#define LED2     			PC1
#define LED3     			PC2
#define BUZZER     			PC3

/* Local functions definition */
static void delay(uint32 count);

int main(void)
{
	/* Set pins direction as output */
    DDRC |= (1 << LED1) | (1 << LED2) | (1 << LED3) | (1 << BUZZER);
    
    while (1)
    {
		/* Turn LED 1 on */
		PORTC &= ~(1 << BUZZER);
		PORTC |= (1 << LED1);
        delay(250);
		/* Turn LED 2 on */
		PORTC &= ~(1 << LED1);
		PORTC |= (1 << LED2);
		delay(250);
		/* Turn LED 3 on */
		PORTC &= ~(1 << LED2);
		PORTC |= (1 << LED3);
		delay(250);
		/* Turn buzzer on */
		PORTC &= ~(1 << LED3);
		PORTC |= (1 << BUZZER);
		delay(250);
    }
    return 0;
}


static void delay(uint32 count)
{
    vuint32 i, j;
    
    for(i = 0; i < count; ++i)
    {
        for(j = 0; j < count; ++j);
    }
}
