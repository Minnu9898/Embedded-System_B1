/*
 * INTERUPT_TIMER0_CTC_METHOD.c
 *
 * Created: 01-10-2025 12:50:04
 * Author : MinnuDiary
 */ 


#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>


volatile uint16_t  count=0; 
ISR(TIMER0_OVF_vect)
{
	count ++;
	if(count>=996)
	{
		PORTB ^=(1<<PORTB5);
		count=0;
	}
	
}
int main(void)
{
    DDRB|=(1<<DDB5);
	TCCR0A|=(1<<WGM01); //CTC MODE
	OCR0A=249;
	TCCR0B|=(1<<CS00)|(1<<CS01); //PRESCALAR=64
	TIMSK0|=(1<<TOIE0); // ENABLE TIMER INTERRUPT
	sei();
    while (1) 
    {
    }
}

