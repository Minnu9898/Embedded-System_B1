/*
 * LED_Bright_Dim_Using_PWM.c
 *
 * Created: 24-09-2025 21:39:54
 * Author : MinnuDiary
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include<util/delay.h>


int main(void)
{
	DDRD|=(1<<DDD6);
	TCCR0A |= (1<<WGM00) | (1<<WGM01);    //Generate wave
	TCCR0A |= (1<<COM0A1) | (1<<COM0A0); // Inverting
	TCCR0B |= (1<<CS00) | (1<<CS01);
	TCCR0B&=~(1<<CS02);                 //select prescalar=64
	
	while (1)
	{
		for (uint8_t i = 0; i < 255; i++)
		{
			OCR0A = i;       // Increase duty cycle to Increase brightness
			_delay_ms(10);   
		}
		
		for (uint8_t i = 255; i > 0; i--)
		{
			OCR0A = i;       // Decrease duty cycle to decrease brightness
			_delay_ms(10);
		}
		
	}
}



