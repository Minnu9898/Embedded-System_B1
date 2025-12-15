/*
 * BMP280.h
 *
 * Created: 11-12-2025 21:01:48
 *  Author: MinnuDiary
 */ 


#ifndef BMP280_H_
#define BMP280_H_



#include <stdint.h>

void BMP280_Init(void);
uint8_t BMP280_ReadChipID(void);
float BMP280_ReadTemperature(void);




#endif /* BMP280_H_ */