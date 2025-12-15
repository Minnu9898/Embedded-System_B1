/*
 * I2C.h
 *
 * Created: 11-12-2025 21:00:15
 *  Author: MinnuDiary
 */ 


#ifndef I2C_H_
#define I2C_H_

#define SCL_CLOCK 100000UL   // 100kHz I2C

#define TWBR_VALUE (((F_CPU / SCL_CLOCK) - 16) / 2)
#include <avr/io.h>

void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Write(uint8_t data);
uint8_t I2C_Read_ACK(void);
uint8_t I2C_Read_NACK(void);



#endif /* I2C_H_ */