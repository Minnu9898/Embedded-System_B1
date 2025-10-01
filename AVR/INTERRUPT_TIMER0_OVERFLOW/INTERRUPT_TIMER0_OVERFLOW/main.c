/*
 * INTERRUPT_TIMER0_OVERFLOW.c
 *
 * Created: 29-09-2025 20:47:43
 * Author : MinnuDiary
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include<stdio.h>

volatile uint16_t  count=0; // volatile keyword used to say this variable value can be changed outside main
ISR(TIMER0_OVF_vect) // Interrupt service routine - TIMER0_OVF_vect=interrupt vector table/address for timer overflow Interrupt
{
	//TIMER0_OVF_vect - its location is present in header file
	count++;
	if (count>=977)
	{
		PORTB^=(1<<PORTB5); //blink led
		count=0;
	}
	
	
}

int main(void)
{
    DDRB|=(1<<DDB5);
	//TCNT0=0;			 //INITIAL VALUE=0 FOR NORMAL MODE
	TCCR0A=0;			//CONTROLLER SET TO 0-NORMAL MODE
	TCCR0B|=(1<<CS00)|(1<<CS01); // PRESCALAR=64
	TIMSK0|=(1<<TOIE0);//Enable timer overflow Interrupt for timer 0
	sei();//Enable global interrupt
	 // when overflow happens it check interrupt table for the interrupt addresss- all interrupts has corresponding table or location
	
    while (1) 
    {
    }
}

