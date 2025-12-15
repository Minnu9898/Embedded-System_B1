
/*
 * LEARNINGS
 * TO MAKE A BIT ZERO  ------> &= ~(0x3 << (5*2));
 *
 */


#include "stm32f446rxx.h"
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>




uint32_t ADC1_Read(void)
{
    ADC1->CR2 |= (1 << 30);        // SWSTART (start conversion)

    while(!(ADC1->SR & (1 << 1))); // Wait for EOC

    return ADC1->DR;               // return ADC result
}

float LM35_ReadTemp(void)
{
    uint32_t adc = ADC1_Read();

    float voltage_mv = (adc * 3300.0f) / 4095.0f;  // mV
    float temp = voltage_mv / 10.0f;               // LM35 → 10mV = 1°C

    return temp;
}



void ADC1_Init(void)
{
    ADC1->CR2 = 0;                 // reset control register

    ADC1->SQR3 = 1;                // Channel 1 (PA1)
    ADC1->SMPR2 |= (7 << 3);       // 480 cycle sample time

    ADC1->CR2 |= (1 << 0);         // ADON = 1 (Power ON)

    // IMPORTANT: ADC needs delay after ADON
    for(volatile int i=0; i<10000; i++);

    ADC1->CR2 |= (1 << 1);         // CONT = 1 → continuous mode
    ADC1->CR2 |= (1 << 10);        // EOCS = 1 → EOC after each conversion
    ADC1->CR2 |= (1 << 8);         // EXTSEL = SWSTART
}


int main(void)
{
    GPIOA_CLK_EN();     // Enable GPIOA clock
    ADC1_CLK_EN();      // Enable ADC1 clock
    // PA1 → Analog Mode
        GPIOA->MODER &= ~(0x3 << (1*2));
        GPIOA->MODER |=  (0x3 << (1*2));     // 11 = analog mode

        ADC1_Init();

        while(1)
        {
            float temp = LM35_ReadTemp();
            printf("Temperature : %.2f C\n", temp);

            for(volatile int i=0; i<500000; i++); // small delay (~100ms)
        }

}


