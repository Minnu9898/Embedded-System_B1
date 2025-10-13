/*
 * LCD_Parallel_port.c
 *
 * Created: 08-10-2025 20:09:24
 * Author : MinnuDiary
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

int main(void)
{
	lcd_init();
	
	lcd_set_cursor(0, 0);
	lcd_print("Hello LCD");

	lcd_set_cursor(1, 0);
	lcd_print("It works! ");

	//small demo: print a number
	 lcd_print_uint16(1234);

	while (1)
	{
		lcd_print_uint16(1234);
		_delay_ms(1000);
		lcd_clear();
		_delay_ms(1000);

	}
	
	//small demo: print a floating number

	while (1)
	{
		lcd_clear();
		lcd_set_cursor(0, 0);
		lcd_print_float(45.678);
		_delay_ms(1000);
	}
}
