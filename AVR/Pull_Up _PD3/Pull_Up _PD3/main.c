/*
 * LED_PD3_Switch_PC0.c
 *
 * Created: 08-09-2025 22:18:11
 * Author : Minnu
 2. 1. Write a program to Turn on an LED Connected to PD3 pin of an ATMEGA 328 when a switch connected to PC0 is pressed(show active high and low connections in the switch). Simulate in Siumul ide
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include<util/delay.h>


int main(void)
{	
	DDRC=0b00000000; // DC0 -input connected to switch
	DDRD=0b00001000; // DC3 - output connected to LED
	//PORTC = 0b00000001;
   
    while (1) 
    {
		if (PINC==0b00000000)
		{
			PORTD=0b00001000;
		}
		else
		{
			PORTD=0b00000000;
		}
    }
}



