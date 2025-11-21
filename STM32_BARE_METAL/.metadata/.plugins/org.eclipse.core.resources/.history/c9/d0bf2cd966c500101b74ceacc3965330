/*
 * stm32f446rxx.h
 *
 *  Created on: Nov 19, 2025
 *      Author: MinnuDiary
 */

#ifndef STM32F446RXX_H_
#define STM32F446RXX_H_
			/* Take  register boundary addresses (Reference Manual - page=58)
			 * Find to which Bus GPIO /SPI/I2C is connected
			 * Find Base address from that table- start defining
			 * Using structure declare registers in it using the register mapping page by clicking the link
			 * Define pointers to point into these registers
			 */
/*GPIO BASE ADDRESSES -(AHB1 BUS)*/
#define GPIOA_BASEADDR	0x40020000U
#define GPIOB_BASEADDR	0x40020400U
#define GPIOC_BASEADDR	0x40020800U
#define GPIOD_BASEADDR	0x40020C00U
#define GPIOE_BASEADDR	0x40021000U
#define GPIOF_BASEADDR	0x40021400U
#define GPIOG_BASEADDR	0x40021800U
#define GPIOH_BASEADDR	0x40021C00U

/*GPIO REGISTER STRUCTURE*/
typedef struct
{
	volatile uint32_t MODER;    // GPIO port mode register              (0x00)
	volatile uint32_t OTYPER;   // GPIO port output type register       (0x04)
	volatile uint32_t OSPEEDR;  // GPIO port output speed register      (0x08)
	volatile uint32_t PUPDR;    // GPIO port pull-up/pull-down register (0x0C)
	volatile uint32_t IDR;      // GPIO port input data register        (0x10)
	volatile uint32_t ODR;      // GPIO port output data register       (0x14)
	volatile uint32_t BSRR;     // GPIO port bit set/reset register     (0x18)
	volatile uint32_t LCKR;     // GPIO port configuration lock register(0x1C)
	volatile uint32_t AFRL;     // GPIO alternate function low register (0x20)
	volatile uint32_t AFRH;     // GPIO alternate function high register(0x24)

}GPIO_RegDef_t;

/*GPIO POINTERS (To point to all registers in the structure*/
#define GPIOA	((GPIO_RegDef_t*)GPIOA_BASEADDR)
#define GPIOB	((GPIO_RegDef_t*)GPIOB_BASEADDR)
#define GPIOC	((GPIO_RegDef_t*)GPIOC_BASEADDR)
#define GPIOD	((GPIO_RegDef_t*)GPIOD_BASEADDR)
#define GPIOE	((GPIO_RegDef_t*)GPIOE_BASEADDR)
#define GPIOF	((GPIO_RegDef_t*)GPIOF_BASEADDR)
#define GPIOG	((GPIO_RegDef_t*)GPIOG_BASEADDR)
#define GPIOH	((GPIO_RegDef_t*)GPIOH_BASEADDR)


/*I2C BASE ADDRESSES*/
#define I2C1_BASEADDRESS  0x40005400U
#define I2C2_BASEADDRESS  0x40005800U
#define I2C3_BASEADDRESS  0x40005C00U

/*I2C REGISTER STRUCTURE*/
typeDef struct
{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t OAR1;
	volatile uint32_t OAR2;
	volatile uint32_t DR;
	volatile uint32_t SR1;
	volatile uint32_t SR2;
	volatile uint32_t CCR;
	volatile uint32_t TRISE;
	volatile uint32_t FLTR;

}I2C_RegDef_t;

/*I2C POINTERS*/

#define I2C1  ((I2C_RegDef_t*)I2C1_BASEADDRESS)
#define I2C2  ((I2C_RegDef_t*)I2C2_BASEADDRESS)
#define I2C3  ((I2C_RegDef_t*)I2C3_BASEADDRESS)

/*SPI BASE ADDRESSES*/
#define SPI1_BASEADDR     0x40013000U   // On APB2
#define SPI2_BASEADDR     0x40003800U   // On APB1
#define SPI3_BASEADDR     0x40003C00U   // On APB1
#define SPI4_BASEADDR     0x40013400U   // On APB2


#endif /* STM32F446RXX_H_ */
