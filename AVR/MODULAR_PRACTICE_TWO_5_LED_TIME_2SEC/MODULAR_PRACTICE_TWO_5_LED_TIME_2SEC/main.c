/*
 * MODULAR_PRACTICE_TWO_5_LED_TIME_2SEC.c
 *
 * Created: 28-09-2025 20:39:59
 * Author : MinnuDiary
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdint.h>
#include "Two_sec_delay.h"


int main(void)
{	
	timer0_init();
	DDRB|=(1<<DDB5)|(1<<DDB4)|(1<<DDB3)|(1<<DDB2)|(1<<DDB1); // set B5,B4,B3,B2 as output
    while (1) 
    {
		PORTB ^=(1<<PORTB5)|(1<<PORTB4)|(1<<PORTB3)|(1<<PORTB2)|(1<<PORTB1);
		Two_sec_delay(2000);
		
    }
	
}

