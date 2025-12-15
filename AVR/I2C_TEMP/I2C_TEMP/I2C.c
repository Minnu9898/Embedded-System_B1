/*
 * I2C.c
 *
 * Created: 11-12-2025 21:00:53
 *  Author: MinnuDiary
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>

#define SCL_CLOCK 100000UL
#define TWBR_VALUE (((F_CPU / SCL_CLOCK) - 16) / 2)

void I2C_Init(void)
{
	TWBR = (uint8_t)TWBR_VALUE;  // Set I2C speed
	TWSR = 0x00;                 // Prescaler = 1
}

void I2C_Start(void)
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
}

void I2C_Stop(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}

void I2C_Write(uint8_t data)
{
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
}

uint8_t I2C_Read_ACK(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while(!(TWCR & (1<<TWINT)));
	return TWDR;
}

uint8_t I2C_Read_NACK(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	return TWDR;
}