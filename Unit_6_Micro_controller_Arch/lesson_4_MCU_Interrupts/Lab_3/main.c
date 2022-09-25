/**
 * @file main.c
 * @brief This file is the main entry point to unit 6 lab 3
 *
 * @author Abanoub Salah
 * @date September 25, 2022
 *
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>

void GPIO_init(void);
void EXTI_init(void);

int main(void)
{
	/* Initialize external interrupt */
    EXTI_init();
	
    /* Initialize GPIO */
    GPIO_init();
    
    for( ; ; )
    {
        /* Turn off all LEDs */
        PORTD &= ~((1 << PD5) | (1 << PD6) | (1 << PD7));
    }
	
    return 0;
}

void GPIO_init(void)
{
    /* Port D set direction to output */
    DDRD |= (1 << PD5) | (1 << PD6) | (1 << PD7);
}

void EXTI_init(void)
{        
    /* Configuration of interrupt sense as INT0, any logical change
     * & INT1, rising edge and INT2, falling edge
	 */
    MCUCR |= (1 << ISC11) | (1 << ISC10) | (1 << ISC00);
    
    /* Enable General interrupt control */
    GICR |= (1 << INT1) | (1 << INT0) | (1 << INT2);
	
	/* Global interrupt enable */
    sei();
}

ISR(INT0_vect)
{
    /* Pin5 LED on */
    PORTD |= (1 << PD5);
    
    /* 1000 ms delay */
    _delay_ms(1000);
    
    /* Pin5 LED off */
    PORTD &= ~(1 << PD5);
}

ISR(INT1_vect)
{
    /* Pin6 LED on */
    PORTD |= (1 << PD6);
    
    /* 1000 ms delay */
    _delay_ms(1000);
    
    /* Pin6 LED off */
    PORTD &= ~(1 << PD6);
}

ISR(INT2_vect)
{
    /* Pin7 LED on */
    PORTD |= (1 << PD7);
    
    /* 1000 ms delay */
    _delay_ms(1000);
    
    /* Pin7 LED off */
    PORTD &= ~(1 << PD7);
}
