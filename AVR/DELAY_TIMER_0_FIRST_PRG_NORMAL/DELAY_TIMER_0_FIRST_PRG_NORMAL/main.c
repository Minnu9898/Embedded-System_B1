/*
 * DELAY_TIMER_0_FIRST_PRG_NORMAL.c
 *
 * Created: 17-09-2025 20:47:26
 * Author : MinnuDiary
 */ 

#define F_CPU 16000000
#include <avr/io.h>

void delay(void)
{	
	unsigned int i;
	unsigned int count=62500; //frequency =16MHz T=1/16MHz
	
	for(i=0;i<count;i++)
	{
		TCNT0=0;			 //INITIAL VALUE=0 FOR NORMAL MODE
		TCCR0A=0;			//CONTROLLER SET TO 0
		TCCR0B|=(1<<CS00); //NO PRESCALAR
		TIFR0|=(1<<TOV0); //RESET TO ZERO BY WRITING 1 TO TOV0
		while(!(TIFR0 & (1<<TOV0)));
	}
	
}

int main(void)
{
    DDRB|=(1<<DDB5); // output
    while (1) 
    {
		PORTB^=(1<<PORTB5); //On OFF
		delay();
		
    }
}

