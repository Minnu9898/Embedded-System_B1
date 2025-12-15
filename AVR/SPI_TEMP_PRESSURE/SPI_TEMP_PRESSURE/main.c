#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	uint8_t chip_id,MSB,LSB,Middle_MSB;

	DDRB |= (1 << PB3) | (1 << PB5) | (1 << PB2); // MOSI, SCK, SS as outputs
	DDRB &= ~(1 << PB4);                           // MISO as input
	PORTB |= (1 << PB2);                           // SS high initially
	DDRD|=(1<<PD3);
	// ===== SPI SETUP =====
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0); // Enable SPI Master

	_delay_ms(100); // allow BMP280 to power up

	// ===== READ CHIP ID =====
	PORTB &= ~(1 << PB2); // CSB low
	SPDR = 0xD0|0X80;
	while (!(SPSR & (1 << SPIF)));
	(void)SPDR;
	SPDR = 0x00;
	while (!(SPSR & (1 << SPIF)));
	chip_id = SPDR;
	PORTB |= (1 << PB2); // CSB high
	_delay_ms(100);
	
	//============MEASURE TEMPERATURE============

		PORTB &= ~(1 << PB2); // CSB low
		SPDR = 0xFA|0X80;
		while (!(SPSR & (1 << SPIF)));
		(void)SPDR;
		SPDR = 0x00;
		while (!(SPSR & (1 << SPIF)));
		MSB = SPDR;
		PORTB |= (1 << PB2); // CSB high
		_delay_ms(100);
		
			PORTB &= ~(1 << PB2); // CSB low
			SPDR = 0xFB|0X80;
			while (!(SPSR & (1 << SPIF)));
			(void)SPDR;
			SPDR = 0x00;
			while (!(SPSR & (1 << SPIF)));
			Middle_MSB = SPDR;
			PORTB |= (1 << PB2); // CSB high
			_delay_ms(100);
			
				PORTB &= ~(1 << PB2); // CSB low
				SPDR = 0xFC|0X80;
				while (!(SPSR & (1 << SPIF)));
				(void)SPDR;
				SPDR = 0x00;
				while (!(SPSR & (1 << SPIF)));
				LSB = SPDR;
				PORTB |= (1 << PB2); // CSB high
				_delay_ms(100);
	while (1)
	{
		if(chip_id==0x58)
		{
			PORTD|=(1<<PD3);
		}
		else
		{
			PORTD &=~(1<<PD3);
		}
	}
}