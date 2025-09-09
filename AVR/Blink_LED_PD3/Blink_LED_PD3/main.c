/*
 * Blink_LED_PD3.c
 *
 * Created: 08-09-2025 21:57:32
 * Author : Minnu
 
 1. Write a program to blink LED Connected to PD3 pin of an ATMEGA 328. Simulate in Siumul ide

 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    DDRD=0b00001000 ;                 //PD3 as OUTPUT
	
    while (1) 
    {
		PORTD=0b00001000;
		_delay_ms(1000);
		PORTD=0b00000000;
		_delay_ms(1000);
    }
}

