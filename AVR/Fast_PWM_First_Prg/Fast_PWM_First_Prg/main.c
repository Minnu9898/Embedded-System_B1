/*
 * Fast_PWM_First_Prg.c
 *
 * Created: 24-09-2025 20:59:56
 * Author : MinnuDiary
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include<util/delay.h>


int main(void)
{
   DDRD|=(1<<DDD6);
   
    while (1) 
    {
		TCCR0A |= (1<<WGM00) | (1<<WGM01);    //Generate wave
		TCCR0A |= (1<<COM0A1) | (1<<COM0A0); // Inverting
		TCCR0B |= (1<<CS00) | (1<<CS01); 
		TCCR0B&=~(1<<CS02);                 //select prescalar=64
		
		OCR0A=100;//duty cycle = OCROA/256 =78 %
    }
}

