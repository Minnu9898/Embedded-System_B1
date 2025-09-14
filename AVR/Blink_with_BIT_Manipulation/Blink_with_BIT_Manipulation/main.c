/*
 * Blink_with_BIT_Manipulation.c
 *
 * Created: 10-09-2025 20:21:05
 * Author : MinnuDiary
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include<util/delay.h>


int main(void)
{
   DDRB= DDRB|(1<<DDB4); // bit made as output to connect LED
   
   
    while (1) 
    {
		PORTB=PORTB|(1<<PORTB4); // LED CONNECTED TO PB5
		_delay_ms(1000);
		PORTB=PORTB&~ (1<<PORTB4);  // CAN BE WRITTEN AS PORTB&=~(1<<PORT5)
		_delay_ms(1000);
    }
}

