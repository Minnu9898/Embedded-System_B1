/*
 * UART_TX.c
 *
 * Created: 17-10-2025 20:53:26
 * Author : MinnuDiary
 Write a program to send letter 'A' in each 1 second using UART.
 */ 

#define F_CPU 16000000UL     // 16 MHz clock
#include <avr/io.h>
#include <util/delay.h>

void UART_Transmit(unsigned char data);
void UART_SendString(const char *str);

void UART_SendString(const char *str)
{
	while (*str)
	{
		UART_Transmit(*str++);
	}
}
// Function to transmit any one  character
void UART_Transmit(unsigned char data)
{
	// Wait until buffer is empty ( If UDREn is one, the buffer is empty,and therefore ready to be written)
	while (!(UCSR0A & (1 << UDRE0)));   //if its 1 on doing and with 1 -will get the value present in the bit
	UDR0 = data;                        // Send data
}

int main(void)
{
    
	/*
	
				16000000
	UBRR  =	   __________   - 1 = 103
				(16 x 9600)
	*/
	//UART_Init();   // Initialize UART
	
	unsigned int ubrr_value = 103;  // For 16MHz and 9600 baud
	UBRR0H = (unsigned char)(ubrr_value >> 8);  // Set baud rate high byte
	UBRR0L = (unsigned char)ubrr_value;         // Set baud rate low byte
	UCSR0B = (1 << TXEN0);	// Enable transmitter
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);     // 8-bit data, no parity, 1 stop bit
	//asynchronus mode UCSZ00=0
/*
    while (1) 
    {
		UART_Transmit('A');  // Send character 'A'
		_delay_ms(1000);     // Wait 1 second
    }
	*/
	while (1)
	{
		UART_SendString("HELLO WORLD\r\n");  // Send the message
		_delay_ms(1000);                     // Wait 1 second
	}
	
}

