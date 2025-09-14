/*
 * Motor_Driving.c
 *
 * Created: 10-09-2025 21:10:33
 * Author : MinnuDiary
 */ 


#define F_CPU 16000000UL
#include <avr/io.h>
#include<util/delay.h>


int main(void)
{
   DDRB= DDRB|(1<<DDB5); // bit made as output to connect LED
   DDRB= DDRB|(1<<DDB4);
   
    while (1) 
    {
		PORTB=PORTB|(1<<PORTB5); // 1  0 
		PORTB=PORTB&~ (1<<PORTB4); 
		_delay_ms(3000);
		PORTB=PORTB&~ (1<<PORTB5);   // OFF
		PORTB=PORTB&~ (1<<PORTB4);
		_delay_ms(1000);	
		PORTB=PORTB|(1<<PORTB4); //0 1
		PORTB=PORTB&~ (1<<PORTB5); 
		_delay_ms(3000);
		PORTB=PORTB&~ (1<<PORTB5);   // OFF
		PORTB=PORTB&~ (1<<PORTB4);
		_delay_ms(1000);
		
		
    }
}


