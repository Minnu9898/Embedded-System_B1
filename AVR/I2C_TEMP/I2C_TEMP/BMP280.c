/*
 * BMP280.c
 *
 * Created: 11-12-2025 21:01:30
 *  Author: MinnuDiary
 */ 

#include "bmp280.h"
#include "i2c.h"
#include <util/delay.h>

#define BMP280_ADDR 0x76   // I2C Address

uint16_t dig_T1;
int16_t dig_T2, dig_T3;

uint8_t bmp280_read8(uint8_t reg)
{
	uint8_t data;

	I2C_Start();
	I2C_Write((BMP280_ADDR << 1) | 0);     // Write mode
	I2C_Write(reg);

	I2C_Start();
	I2C_Write((BMP280_ADDR << 1) | 1);     // Read mode
	data = I2C_Read_NACK();
	I2C_Stop();

	return data;
}

void bmp280_write8(uint8_t reg, uint8_t value)
{
	I2C_Start();
	I2C_Write((BMP280_ADDR << 1) | 0);
	I2C_Write(reg);
	I2C_Write(value);
	I2C_Stop();
}

void BMP280_ReadCalibration(void)
{
	uint8_t msb, lsb;

	lsb = bmp280_read8(0x88);
	msb = bmp280_read8(0x89);
	dig_T1 = (msb << 8) | lsb;

	lsb = bmp280_read8(0x8A);
	msb = bmp280_read8(0x8B);
	dig_T2 = (msb << 8) | lsb;

	lsb = bmp280_read8(0x8C);
	msb = bmp280_read8(0x8D);
	dig_T3 = (msb << 8) | lsb;
}

uint8_t BMP280_ReadChipID(void)
{
	return bmp280_read8(0xD0);
}

void BMP280_Init(void)
{
	bmp280_write8(0xF4, 0x27);   // Normal mode, temp oversample x1
	_delay_ms(100);

	BMP280_ReadCalibration();
}

float BMP280_ReadTemperature(void)
{
	uint32_t msb = bmp280_read8(0xFA);
	uint32_t lsb = bmp280_read8(0xFB);
	uint32_t xlsb = bmp280_read8(0xFC);

	uint32_t raw = (msb << 12) | (lsb << 4) | (xlsb >> 4);

	float var1 = (((raw / 16384.0) - (dig_T1 / 1024.0)) * dig_T2);
	float var2 = (((raw / 131072.0) - (dig_T1 / 8192.0)) * dig_T3);
	float t_fine = var1 + var2;

	return t_fine / 5120.0;
}