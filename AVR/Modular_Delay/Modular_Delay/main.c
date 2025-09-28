/*
 * Modular_Delay.c
 *
 * Created: 26-09-2025 20:20:31
 * Author : MinnuDiary
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include "i_created_directory.h"
#include <stdint.h>


int main(void)
{
   DDRB|=(1<<DDB5);
   timer0_init(); 
    while (1) 
    {
		PORTB^=(1<<PORTB5);
		delay_created(5000);
    }
}

