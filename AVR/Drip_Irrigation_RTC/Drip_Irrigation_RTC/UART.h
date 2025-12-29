

#ifndef UART_H
#define UART_H

#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>     // ? REQUIRED for FILE

void UART_Init(uint32_t baud);
void UART_TransmitChar(char data);

/* printf stream function */
int UART_PutChar(char c, FILE *stream);

#endif