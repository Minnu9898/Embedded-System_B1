/*
 * CTM_COMPARE_TIMER.c
 *
 * Created: 19-09-2025 20:37:42
 * Author : MinnuDiary
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>


int main(void)
{
    DDRB |=(1<<DDB5); // OUTPUT
	
	TCCR0A|=(1<<WGM01); //BRING TO CTC MODE
	OCR0A=200;//SET POINT (COMPARISON VALUE)
	TCNT0=0;
	TCCR0B|=(1<<CS00);//NO PRESCALING
	TIFR0|=(1<<OCF0A); // RESET COMPARISON FLAG INITIALLY TO 0 (WIERD METHOD)
	
    while (1) 
    {
		PORTB^=(1<<PORTB5);
		
		for(int i=0;i<160000;i++) //FOR 2 SECOND DELAY
		{
			while(!(TIFR0 &(1<<OCF0A)))
			{
				
			}
			TIFR0|=(1<<OCF0A); // RESET COMPARISON FLAG INITIALLY TO 0 (WIERD METHOD)
			
		}
			
    }
}

