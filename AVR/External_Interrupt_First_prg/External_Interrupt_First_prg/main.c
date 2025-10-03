/*
 * External_Interrupt_First_prg.c
 *
 * Created: 03-10-2025 20:11:25
 * Author : MinnuDiary
 
 Q: I have to enable interrupt 0 in atmega 328. 
    connect a push button to corresponding interrupt pin.
    I need to toggle an LED connected to PB5 each time i press the push button.
    Falling Edge
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include<stdio.h>
#include <util/delay.h>

ISR(INT0_vect)
{	
PORTB ^=(1<<PORTB5);
_delay_ms(6000);	//after 10 second we need our PB4 to continue
}
int main(void)
{
   DDRD&=~ (1<<DDD2); //set as input =0 - push button
   DDRB|=(1<<DDB5); // set as output = 1
   DDRB|=(1<<DDB4); // second LED
   PORTD|=(1<<PORTD2); //internal pull up on -to make it always 1 so that to make the interrupt in falling edge
   
   //Registers for External Interrupt
   EIMSK|=(1<<INT0); //Enable Interruppt 1
   EICRA |= (1<<ISC01) ; //Falling edge  1 0 
   sei();
  
    while (1) 
    {
		PORTB ^=(1<<PORTB4);
		_delay_ms(2000);
    }
}

