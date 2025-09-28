/*
 * i_created_directory.c
 *
 * Created: 26-09-2025 20:33:27
 *  Author: MinnuDiary
 */ 

// what all function defined in .h should be defined here
#include<avr/io.h>

void timer0_init(void)
{
	TCCR0A|=(1<<WGM01); //BRING TO CTC MODE
	OCR0A=249;//SET POINT (COMPARISON VALUE) - count=250
	TCNT0=0;
	TCCR0B|=(1<<CS00)|(1<<CS01);// PRESCALING=64
	TIFR0|=(1<<OCF0A); // RESET COMPARISON FLAG INITIALLY TO 0 (WIERD METHOD)
	
	// will create 1 ms delay
	
}

void delay_created(uint16_t ms)
{
	timer0_init(); 
	while(ms--)
	{
		
		while (!(TIFR0 & (1<<OCF0A)))// 1 means zero and zero means full
		{
			//BLANK - just to reduce delay one by one using a loop
		}
		TIFR0|=(1<<OCF0A);	 
		
	}
	
}