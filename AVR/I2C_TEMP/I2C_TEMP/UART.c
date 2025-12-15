/*
 * UART.c
 *
 * Created: 11-12-2025 21:12:09
 *  Author: MinnuDiary
 */ 
#include "uart.h"

void UART_Init(void)
{
	uint16_t ubrr = 103;       // 9600 baud @ 16 MHz
	UBRR0H = (ubrr >> 8);
	UBRR0L = (uint8_t)ubrr;

	UCSR0B = (1 << TXEN0);             // Enable transmitter
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8-bit data, 1 stop bit
}

void UART_TxChar(char c)
{
	while (!(UCSR0A & (1 << UDRE0))); // Wait
	UDR0 = c;
}

void UART_TxString(const char *str)
{
	while (*str)
	{
		UART_TxChar(*str++);
	}
}

void UART_TxNumber(int num)
{
	char buffer[10];
	int i = 0;

	if (num == 0)
	{
		UART_TxChar('0');
		return;
	}

	if (num < 0)
	{
		UART_TxChar('-');
		num = -num;
	}

	while (num > 0)
	{
		buffer[i++] = (num % 10) + '0';
		num /= 10;
	}

	while (i > 0)
	{
		UART_TxChar(buffer[--i]);
	}
}