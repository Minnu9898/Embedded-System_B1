/*
 * I2C_TEMP.c
 *
 * Created: 11-12-2025 20:53:06
 * Author : MinnuDiary
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <avr/io.h>
#include <util/delay.h>

#include "uart.h"
#include "i2c.h"
#include "bmp280.h"

int main(void)
{
	UART_Init();
	I2C_Init();

	UART_TxString("BMP280 I2C MODE\r\n");
	
	// volatile uint8_t chip_id;
	//uint8_t chip_id = BMP280_ReadChipID();
	BMP280_Init();

	while (1)
	{
		float temp = BMP280_ReadTemperature();

		UART_TxString("TEMP = ");
		int t_int = temp;
		int t_dec = (temp - t_int) * 100;
		UART_TxNumber(t_int);
		UART_TxChar('.');
		UART_TxNumber(t_dec);
		UART_TxString(" C\r\n");

		_delay_ms(1000);
	}
}
