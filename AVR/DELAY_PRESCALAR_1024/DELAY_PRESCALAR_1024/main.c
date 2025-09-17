/*
 * DELAY_PRESCALAR_1024.c
 *
 * Created: 17-09-2025 22:05:25
 * Author : MinnuDiary
 */ 


#define F_CPU 16000000
#include <avr/io.h>

void delay(void)
{	
	/*16 MHZ/1024=15625 
	T=1/15625 =64 microsecond
	In 64 microsecond 1 count occurs
	Total delay for 256 count =64 x 256 =16384
	So 1 second=1/16384=610
	*/
	unsigned int i;
	unsigned int count=610; //frequency =16MHz T=1/(16/1024)MHz
	
	for(i=0;i<count;i++)
	{
		TCNT0=0;			 //INITIAL VALUE=0 FOR NORMAL MODE
		TCCR0A=0;			//CONTROLLER SET TO 0
		TCCR0B |= (1<<CS02) | (1<<CS00);   // Set CS02=1, CS01=0, CS00=1  // prescalar =1024
		TCCR0B &= ~(1<<CS01); 
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

