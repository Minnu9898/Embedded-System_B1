#define F_CPU 16000000UL  // Define CPU frequency for delay functions (16 MHz)

#include <avr/io.h>       // AVR IO definitions (ports, registers, etc.)
#include <util/delay.h>   // Delay functions like _delay_ms()
#include "rtc.h"          // RTC header file with structure and function prototypes

#define RTC_ADDRESS 0x68  // I2C 7-bit address of DS1307 / DS3231 RTC

/* ---------- BCD Conversion Functions ---------- */

// Convert Decimal value (0-99) to BCD format for RTC registers
uint8_t DecimalToBCD(uint8_t val)
{
	return ((val / 10) << 4) | (val % 10);
}

// Convert BCD value from RTC to Decimal for MCU calculations
uint8_t BCDToDecimal(uint8_t val)
{
	return ((val >> 4) * 10) + (val & 0x0F);
}

/* ---------- TWI (I2C) Low Level Functions ---------- */

// Initialize TWI (I2C) peripheral on ATmega
static void TWI_Init(void)
{
	TWSR = 0x00;                 // Prescaler = 1
	TWBR = 72;                   // Set bit rate for 100kHz @ 16MHz CPU
	TWCR = (1 << TWEN);          // Enable TWI module
}

// Generate I2C start condition
static void TWI_Start(void)
{
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN); // Send START
	while (!(TWCR & (1 << TWINT)));                  // Wait for START to complete
}

// Generate I2C stop condition
static void TWI_Stop(void)
{
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN); // Send STOP
}

// Write a byte of data to I2C bus
static void TWI_Write(uint8_t data)
{
	TWDR = data;                                     // Load data into TWI Data Register
	TWCR = (1 << TWINT) | (1 << TWEN);              // Start transmission
	while (!(TWCR & (1 << TWINT)));                 // Wait until transmission completes
}

// Read a byte from I2C bus and send ACK (for reading multiple bytes)
static uint8_t TWI_ReadACK(void)
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA); // Enable TWI and ACK
	while (!(TWCR & (1 << TWINT)));                 // Wait for data
	return TWDR;                                     // Return received data
}

// Read last byte from I2C bus and send NACK (for ending read sequence)
static uint8_t TWI_ReadNACK(void)
{
	TWCR = (1 << TWINT) | (1 << TWEN);             // Enable TWI without ACK
	while (!(TWCR & (1 << TWINT)));                 // Wait for data
	return TWDR;                                    // Return received data
}

/* ---------- RTC Functions ---------- */

// Initialize RTC by initializing I2C peripheral
void RTC_Init(void)
{
	TWI_Init(); // Set up I2C communication
}

// Set time and date in RTC registers
void RTC_SetTime(RTC_TimeDate *time)
{
	TWI_Start();                        // Start I2C communication
	TWI_Write((RTC_ADDRESS << 1) | 0);  // Send RTC address + write bit
	TWI_Write(0x00);                    // Start writing from seconds register

	// Write seconds, minutes, hours, day, date, month, year in BCD format
	TWI_Write(DecimalToBCD(time->seconds));
	TWI_Write(DecimalToBCD(time->minutes));
	TWI_Write(DecimalToBCD(time->hours));
	TWI_Write(DecimalToBCD(time->day));
	TWI_Write(DecimalToBCD(time->date));
	TWI_Write(DecimalToBCD(time->month));
	TWI_Write(DecimalToBCD(time->year));

	TWI_Stop();                         // Stop I2C communication
}

// Read time and date from RTC registers
void RTC_GetTime(RTC_TimeDate *time)
{
	TWI_Start();                        // Start I2C communication
	TWI_Write((RTC_ADDRESS << 1) | 0);  // Send RTC address + write bit
	TWI_Write(0x00);                    // Point to seconds register

	TWI_Start();                        // Repeated start for reading
	TWI_Write((RTC_ADDRESS << 1) | 1);  // Send RTC address + read bit

	// Read each byte from RTC and convert BCD to decimal
	time->seconds = BCDToDecimal(TWI_ReadACK() & 0x7F); // Mask CH bit
	time->minutes = BCDToDecimal(TWI_ReadACK());
	time->hours   = BCDToDecimal(TWI_ReadACK());
	time->day     = BCDToDecimal(TWI_ReadACK());
	time->date    = BCDToDecimal(TWI_ReadACK());
	time->month   = BCDToDecimal(TWI_ReadACK());
	time->year    = BCDToDecimal(TWI_ReadNACK());       // Last byte, send NACK

	TWI_Stop();                         // Stop I2C communication
}