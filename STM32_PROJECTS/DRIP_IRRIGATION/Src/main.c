#include <stdint.h>
#include "stm32f446rxx.h"

#define DS3231_ADDR  0x68

/* NVIC register */
#define NVIC_ISER0   (*(volatile uint32_t*)0xE000E100)

/* PWR register */
#define PWR_CR       (*(volatile uint32_t*)0x40007000)

/* ===================== RELAY ===================== */
void Relay_Init(void)
{
    GPIOA_CLK_EN();

    GPIOA->MODER &= ~(3 << 10);
    GPIOA->MODER |=  (1 << 10);   // PA5 output

    GPIOA->ODR &= ~(1 << 5);      // Relay OFF
}

/* ===================== I2C ===================== */
void I2C1_Init(void)
{
    GPIOB_CLK_EN();
    I2C1_CLK_EN();

    /* PB6, PB7 -> AF4 */
    GPIOB->MODER &= ~(0xF << 12);
    GPIOB->MODER |=  (0xA << 12);

    /* Open-drain */
    GPIOB->OTYPER |= (1 << 6) | (1 << 7);

    /* High speed */
    GPIOB->OSPEEDR |= (0xF << 12);

    /* Pull-up */
    GPIOB->PUPDR &= ~(0xF << 12);
    GPIOB->PUPDR |=  (0x5 << 12);

    /* AF4 selection */
    GPIOB->AFRL |= (4 << 24) | (4 << 28);

    /* I2C timing (APB1 = 16 MHz, 100 kHz) */
    I2C1->CR1 &= ~(1 << 0);
    I2C1->CR2 = 16;
    I2C1->CCR = 80;
    I2C1->TRISE = 17;
    I2C1->CR1 |= (1 << 0);
}

void I2C_Write(uint8_t devAddr, uint8_t reg, uint8_t data)
{
    I2C1->CR1 |= (1 << 8);                    // START
    while(!(I2C1->SR1 & (1 << 0)));

    I2C1->DR = devAddr << 1;
    while(!(I2C1->SR1 & (1 << 1)));
    (void)I2C1->SR2;

    I2C1->DR = reg;
    while(!(I2C1->SR1 & (1 << 7)));

    I2C1->DR = data;
    while(!(I2C1->SR1 & (1 << 7)));

    I2C1->CR1 |= (1 << 9);                    // STOP
}

/* ===================== DS3231 ===================== */
void DS3231_SetTime(void)
{
    /* Time: 16:59:00 (BCD) */
    I2C_Write(DS3231_ADDR, 0x00, 0x00);   // Seconds
    I2C_Write(DS3231_ADDR, 0x01, 0x59);   // Minutes
    I2C_Write(DS3231_ADDR, 0x02, 0x16);   // Hours (4 PM)
}

void DS3231_SetAlarm_5PM(void)
{
    I2C_Write(DS3231_ADDR, 0x07, 0x00);   // A1 Seconds
    I2C_Write(DS3231_ADDR, 0x08, 0x00);   // A1 Minutes
    I2C_Write(DS3231_ADDR, 0x09, 0x17);   // A1 Hours (5 PM)
    I2C_Write(DS3231_ADDR, 0x0A, 0x80);   // Ignore date

    I2C_Write(DS3231_ADDR, 0x0E, 0x05);   // INTCN + A1IE
    I2C_Write(DS3231_ADDR, 0x0F, 0x00);   // Clear alarm flags
}

/* ===================== EXTI ===================== */
void EXTI0_Init(void)
{
    RCC->APB2ENR |= (1 << 14);            // SYSCFG

    GPIOA_CLK_EN();
    GPIOA->MODER &= ~(3 << 0);            // PA0 input

    /* PA0 -> EXTI0 */
    *((volatile uint32_t*)0x40013808) &= ~(0xF << 0);

    /* EXTI */
    *((volatile uint32_t*)0x40013C00) |= (1 << 0); // IMR
    *((volatile uint32_t*)0x40013C08) |= (1 << 0); // Falling edge

    /* NVIC enable */
    NVIC_ISER0 |= (1 << 6);               // EXTI0 IRQ
}

/* ===================== LOW POWER ===================== */
void Enter_StopMode(void)
{
    PWR_CR &= ~(1 << 1);                  // STOP mode
    *((volatile uint32_t*)0xE000ED10) |= (1 << 2); // SLEEPDEEP
    __WFI();
}

/* ===================== ISR ===================== */
void EXTI0_IRQHandler(void)
{
    *((volatile uint32_t*)0x40013C14) |= (1 << 0); // Clear pending

    GPIOA->ODR |= (1 << 5);               // Relay ON
}

/* ===================== MAIN ===================== */
int main(void)
{
    Relay_Init();
    I2C1_Init();

    DS3231_SetTime();
    DS3231_SetAlarm_5PM();

    EXTI0_Init();

    while(1)
    {
        Enter_StopMode();
    }
}
