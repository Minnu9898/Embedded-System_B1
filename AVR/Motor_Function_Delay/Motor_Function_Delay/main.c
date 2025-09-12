/*
 * Motor_Function_Delay.c
 *
 * Created: 11-09-2025 17:31:53
 * Author : MinnuDiary
 */ 


#define F_CPU 16000000UL
#include <avr/io.h>
#include<util/delay.h>
    //#define DELAY1 2000
    //#define DELAY2 5000

void variable_delay_ms(uint16_t ms)
{
	while(ms--) {
		_delay_ms(1);   // 1ms delay repeated
	}
}	
	

void clock_wise(uint16_t delay_ms)
{
	PORTB|=(1<<PORTB5); // 1  0
	PORTB&=~ (1<<PORTB4);
	variable_delay_ms(delay_ms);
	
}

void stop(uint16_t delay_ms)
{
	PORTB&= ~(1<<PORTB5);   // OFF
	PORTB&= ~(1<<PORTB4);
	variable_delay_ms(delay_ms);
	
}
void Anti_clock_wise(uint16_t delay_ms)
{
	PORTB|=(1<<PORTB4); //0 1
	PORTB&= ~(1<<PORTB5);
	variable_delay_ms(delay_ms);
	
}

int main(void)
{
	
	
	DDRB|= (1<<DDB5); // bit made as output to connect LED
	DDRB|=(1<<DDB4);
	
	while (1)
	{
		
		
		clock_wise(2000);
		stop(3000);
		Anti_clock_wise(2000);
		
	}
}





