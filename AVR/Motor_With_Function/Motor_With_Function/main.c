/*
 * Motor_With_Function.c
 *
 * Created: 10-09-2025 21:53:39
 * Author : MinnuDiary
 */ 


#define F_CPU 16000000UL
#include <avr/io.h>
#include<util/delay.h>


void clock_wise()
{
	PORTB=PORTB|(1<<PORTB5); // 1  0
	PORTB=PORTB&~ (1<<PORTB4);
	_delay_ms(5000);
	
}

void stop()
{
	PORTB=PORTB&~ (1<<PORTB5);   // OFF
	PORTB=PORTB&~ (1<<PORTB4);
	_delay_ms(1000);
	
}
void Anti_clock_wise()
{
	PORTB=PORTB|(1<<PORTB4); //0 1
	PORTB=PORTB&~ (1<<PORTB5);
	_delay_ms(5000);
	
}

int main(void)
{
   DDRB= DDRB|(1<<DDB5); // bit made as output to connect LED
   DDRB= DDRB|(1<<DDB4);
   
    while (1) 
    {
		clock_wise();
		stop();
		Anti_clock_wise();
		
    }
}



