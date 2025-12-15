/*
 * UART.h
 *
 * Created: 11-12-2025 21:11:17
 *  Author: MinnuDiary
 */ 


#ifndef UART_H_
#define UART_H_

#include <avr/io.h>

void UART_Init(void);
void UART_TxChar(char c);
void UART_TxString(const char *str);
void UART_TxNumber(int num);



#endif /* UART_H_ */