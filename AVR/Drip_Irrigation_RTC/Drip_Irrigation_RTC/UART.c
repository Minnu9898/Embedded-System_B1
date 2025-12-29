#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdio.h>
#include "uart.h"

void UART_Init(uint32_t baud)
{
	uint16_t ubrr = (F_CPU / (16UL * baud)) - 1;

	UBRR0H = (ubrr >> 8);
	UBRR0L = ubrr;

	UCSR0B = (1 << TXEN0);                     // Enable TX
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);    // 8-bit data
}

void UART_TransmitChar(char data)
{
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

/* Required by printf */
int UART_PutChar(char c, FILE *stream)
{
	if (c == '\n')
	UART_TransmitChar('\r');

	UART_TransmitChar(c);
	return 0;
}