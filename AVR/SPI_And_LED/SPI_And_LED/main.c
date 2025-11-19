#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

/*
? Full Summary (Easy to Remember)
CS Low ? start SPI
Send 0xD0 ? request chip ID
Wait
Ignore dummy read
Send 0x00 ? allow chip to output ID
Wait
Read chip ID
CS High ? end SPI
Delay

*/
int main(void)
{
	uint8_t chip_id;

	DDRB |= (1 << PB3) | (1 << PB5) | (1 << PB2); // MOSI, SCK, SS as outputs
	DDRB &= ~(1 << PB4);                           // MISO as input
	PORTB |= (1 << PB2);                           // SS high initially
	DDRD|=(1<<PD3);
	// ===== SPI SETUP =====
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0); // Enable SPI Master

	_delay_ms(100); // allow BMP280 to power up

	// ===== READ CHIP ID =====
	PORTB &= ~(1 << PB2); // CSB low
	SPDR = 0xD0;    // command to read chip id from slave =0xD0
	while (!(SPSR & (1 << SPIF)));
	(void)SPDR;     // command for dummy reading and ignore value
	
	SPDR = 0x00;    //send a dummy byte
	//In SPI, to receive data from the slave, you must send something.
	//Sending 0x00 provides the clock pulses so the slave can output the CHIP ID byte.
	
	while (!(SPSR & (1 << SPIF))); // when flag sets after transfer of data 
	chip_id = SPDR;
	PORTB |= (1 << PB2); // CSB high
	_delay_ms(100);

/*
Sensor detection
Debugging
Hardware verification

*/
	while (1)
	{
		if(chip_id==0x58)     //checks if the connected device is the correct sensor.
		{
			PORTD|=(1<<PD3); //turning ON something connected to PD3
		}
		else
		{
			PORTD &=~(1<<PD3); //turning off something connected to PD3
		}
	}
}