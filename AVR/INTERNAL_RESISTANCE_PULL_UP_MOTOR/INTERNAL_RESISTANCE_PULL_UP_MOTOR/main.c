/*
 * INTERNAL_RESISTANCE_PULL_UP_MOTOR.c
 *
 * Created: 17-09-2025 12:21:53
 * Author : MinnuDiary
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>



int main(void)
{
	DDRD&=~(1<<DDD2);
	PORTD|=(1<<PORTD2);
	DDRB|=(1<<5);
	DDRB|=(1<<4);
	while (1)
	{
		if (!(PIND&(1<<PIND2)))
		{
			PORTB|=(1<<PORTB5);
			PORTB&=~(1<<PORTB4);
			_delay_ms(1000); // Clock wise
			
			PORTB&=~(1<<PORTB5);
			PORTB&=~(1<<PORTB4);
			_delay_ms(1000); // Stop
			
			PORTB&=~(1<<PORTB5);
			PORTB|=(1<<PORTB4);
			_delay_ms(1000); // Counter clock wise
			
			PORTB&=~(1<<PORTB5);
			PORTB&=~(1<<PORTB4);
			_delay_ms(1000); // Stop
		}
		else
		{
			PORTB&=~(1<<PORTB5);
			PORTB&=~(1<<PORTB4);
			_delay_ms(1000); // Stop
			
		}
		
		
		
	}
}

