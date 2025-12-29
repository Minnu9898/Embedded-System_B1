/*
 * stm32f446xx_gpio_driver.c
 * GPIO Driver Implementation
 */

#include "stm32f446xx_gpio_driver.h"

/*********************************************************************
 * @fn          GPIO_PeriClockControl
 *
 * @brief       Enables or disables peripheral clock for GPIO port
 *
 * @param[in]   pGPIOx: GPIO port base address (GPIOA, GPIOB, etc.)
 * @param[in]   EnorDi: ENABLE or DISABLE
 *
 * @return      None
 *
 * @note        This must be called before using any GPIO functions
 *********************************************************************/
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
    if (EnorDi == ENABLE)
    {
        // Enable clock for the appropriate port
        if (pGPIOx == GPIOA)
        {
            GPIOA_PCLK_EN();
        }
        else if (pGPIOx == GPIOB)
        {
            GPIOB_PCLK_EN();
        }
        else if (pGPIOx == GPIOC)
        {
            GPIOC_PCLK_EN();
        }
        else if (pGPIOx == GPIOD)
        {
            GPIOD_PCLK_EN();
        }
        else if (pGPIOx == GPIOE)
        {
            GPIOE_PCLK_EN();
        }
        else if (pGPIOx == GPIOF)
        {
            GPIOF_PCLK_EN();
        }
        else if (pGPIOx == GPIOG)
        {
            GPIOG_PCLK_EN();
        }
        else if (pGPIOx == GPIOH)
        {
            GPIOH_PCLK_EN();
        }
    }
    else
    {
        // Disable clock for the appropriate port
        if (pGPIOx == GPIOA)
        {
            GPIOA_PCLK_DI();
        }
        else if (pGPIOx == GPIOB)
        {
            GPIOB_PCLK_DI();
        }
        // ... similar for other ports
    }
}

/*********************************************************************
 * @fn          GPIO_Init
 *
 * @brief       Initializes a GPIO pin according to the configuration
 *
 * @param[in]   pGPIOHandle: Pointer to GPIO handle structure
 *
 * @return      None
 *********************************************************************/
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
    uint32_t temp = 0;

    // 0. Enable the peripheral clock (so we don't forget!)
    GPIO_PeriClockControl(pGPIOHandle->pGPIOx, ENABLE);

    // 1. Configure the mode of GPIO pin
    if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
    {
        /*
         * Non-interrupt mode
         * MODER register: 2 bits per pin
         * Pin 0: bits [1:0], Pin 1: bits [3:2], ..., Pin 15: bits [31:30]
         */

        // Calculate the bit position: pin_number * 2
        temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode
                << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));

        // Clear the 2 bits first (important!)
        pGPIOHandle->pGPIOx->MODER &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));

        // Set the new value
        pGPIOHandle->pGPIOx->MODER |= temp;
    }
    else
    {
        /*
         * Interrupt mode
         * Need to configure: EXTI, SYSCFG, and NVIC
         */

        if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
        {
            // Configure for Falling edge trigger
            EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            // Make sure rising trigger is disabled
            EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        }
        else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
        {
            // Configure for Rising edge trigger
            EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            // Make sure falling trigger is disabled
            EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        }
        else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
        {
            // Configure for both Rising and Falling edge trigger
            EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
            EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
        }

        /*
         * Configure GPIO port selection in SYSCFG_EXTICR
         *
         * EXTICR[0] controls pins 0-3
         * EXTICR[1] controls pins 4-7
         * EXTICR[2] controls pins 8-11
         * EXTICR[3] controls pins 12-15
         *
         * Each pin uses 4 bits in the register
         */
        uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;
        uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;
        uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);

        SYSCFG_PCLK_EN();  // Enable SYSCFG clock
        SYSCFG->EXTICR[temp1] = portcode << (temp2 * 4);

        // Enable the EXTI interrupt delivery using IMR (Interrupt Mask Register)
        EXTI->IMR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    }

    // 2. Configure the speed
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed
            << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->OSPEEDR |= temp;

    // 3. Configure the pull-up/pull-down settings
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl
            << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
    pGPIOHandle->pGPIOx->PUPDR |= temp;

    // 4. Configure the output type
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType
            << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
    pGPIOHandle->pGPIOx->OTYPER |= temp;

    // 5. Configure the alternate functionality (if applicable)
    if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
    {
        /*
         * AFR[0] (AFRL) controls pins 0-7
         * AFR[1] (AFRH) controls pins 8-15
         * Each pin uses 4 bits
         */
        uint8_t temp1, temp2;

        temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;  // Which AFR register
        temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;  // Position within register

        pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << (4 * temp2));  // Clear 4 bits
        pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * temp2));
    }
}

/*********************************************************************
 * @fn          GPIO_DeInit
 *
 * @brief       Resets GPIO port to default state
 *
 * @param[in]   pGPIOx: GPIO port base address
 *
 * @return      None
 *********************************************************************/
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
{
    if (pGPIOx == GPIOA)
    {
        GPIOA_REG_RESET();
    }
    else if (pGPIOx == GPIOB)
    {
        GPIOB_REG_RESET();
    }
    else if (pGPIOx == GPIOC)
    {
        GPIOC_REG_RESET();
    }
    // ... continue for all ports
}

/*********************************************************************
 * @fn          GPIO_ReadFromInputPin
 *
 * @brief       Reads the value of a specific GPIO pin
 *
 * @param[in]   pGPIOx: GPIO port base address
 * @param[in]   PinNumber: Pin number (0-15)
 *
 * @return      0 or 1
 *********************************************************************/
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
    uint8_t value;

    /*
     * Read from IDR (Input Data Register)
     * Shift right to move the target bit to position 0
     * Mask with 0x01 to extract only that bit
     */
    value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001);

    return value;
}

/*********************************************************************
 * @fn          GPIO_ReadFromInputPort
 *
 * @brief       Reads the entire GPIO port
 *
 * @param[in]   pGPIOx: GPIO port base address
 *
 * @return      16-bit value representing all pins
 *********************************************************************/
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
    uint16_t value;

    value = (uint16_t)pGPIOx->IDR;

    return value;
}

/*********************************************************************
 * @fn          GPIO_WriteToOutputPin
 *
 * @brief       Writes to a specific GPIO pin
 *
 * @param[in]   pGPIOx: GPIO port base address
 * @param[in]   PinNumber: Pin number (0-15)
 * @param[in]   Value: GPIO_PIN_SET or GPIO_PIN_RESET
 *
 * @return      None
 *********************************************************************/
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
    if (Value == GPIO_PIN_SET)
    {
        // Set the bit (write 1)
        pGPIOx->ODR |= (1 << PinNumber);
    }
    else
    {
        // Clear the bit (write 0)
        pGPIOx->ODR &= ~(1 << PinNumber);
    }
}

/*********************************************************************
 * @fn          GPIO_WriteToOutputPort
 *
 * @brief       Writes to entire GPIO port
 *
 * @param[in]   pGPIOx: GPIO port base address
 * @param[in]   Value: 16-bit value to write
 *
 * @return      None
 *********************************************************************/
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value)
{
    pGPIOx->ODR = Value;
}

/*********************************************************************
 * @fn          GPIO_ToggleOutputPin
 *
 * @brief       Toggles a specific GPIO pin
 *
 * @param[in]   pGPIOx: GPIO port base address
 * @param[in]   PinNumber: Pin number (0-15)
 *
 * @return      None
 *********************************************************************/
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
    /*
     * XOR operation: toggles the bit
     * If bit is 0, XOR with 1 makes it 1
     * If bit is 1, XOR with 1 makes it 0
     */
    pGPIOx->ODR ^= (1 << PinNumber);
}

/*********************************************************************
 * @fn          GPIO_IRQInterruptConfig
 *
 * @brief       Enables or disables interrupt in NVIC
 *
 * @param[in]   IRQNumber: Interrupt number
 * @param[in]   EnorDi: ENABLE or DISABLE
 *
 * @return      None
 *********************************************************************/
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
    if (EnorDi == ENABLE)
    {
        /*
         * NVIC has multiple ISER (Interrupt Set Enable) registers
         * ISER0: IRQ 0-31
         * ISER1: IRQ 32-63
         * ISER2: IRQ 64-95
         */
        if (IRQNumber <= 31)
        {
            *NVIC_ISER0 |= (1 << IRQNumber);
        }
        else if (IRQNumber > 31 && IRQNumber < 64)
        {
            *NVIC_ISER1 |= (1 << (IRQNumber % 32));
        }
        else if (IRQNumber >= 64 && IRQNumber < 96)
        {
            *NVIC_ISER2 |= (1 << (IRQNumber % 64));
        }
    }
    else
    {
        // Use ICER (Interrupt Clear Enable) registers to disable
        if (IRQNumber <= 31)
        {
            *NVIC_ICER0 |= (1 << IRQNumber);
        }
        else if (IRQNumber > 31 && IRQNumber < 64)
        {
            *NVIC_ICER1 |= (1 << (IRQNumber % 32));
        }
        else if (IRQNumber >= 64 && IRQNumber < 96)
        {
            *NVIC_ICER2 |= (1 << (IRQNumber % 64));
        }
    }
}

/*********************************************************************
 * @fn          GPIO_IRQPriorityConfig
 *
 * @brief       Sets the priority of an interrupt
 *
 * @param[in]   IRQNumber: Interrupt number
 * @param[in]   IRQPriority: Priority value (0-15 for 4-bit priority)
 *
 * @return      None
 *********************************************************************/
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
    /*
     * NVIC Priority Registers (IPR0-IPR59)
     * Each register contains 4 priority fields (8 bits each)
     * Only upper 4 bits are implemented (in STM32)
     */

    // Find which IPR register
    uint8_t iprx = IRQNumber / 4;

    // Find which section within the register (0, 1, 2, or 3)
    uint8_t iprx_section = IRQNumber % 4;

    // Calculate shift amount
    // Priority is in upper 4 bits of each 8-bit field
    uint8_t shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED);

    *(NVIC_PR_BASE_ADDR + iprx) |= (IRQPriority << shift_amount);
}

/*********************************************************************
 * @fn          GPIO_IRQHandling
 *
 * @brief       Clears the pending interrupt flag
 *
 * @param[in]   PinNumber: Pin number that triggered the interrupt
 *
 * @return      None
 *
 * @note        Must be called in the ISR to clear the interrupt
 *********************************************************************/
void GPIO_IRQHandling(uint8_t PinNumber)
{
    /*
     * Clear the EXTI Pending Register (PR)
     * Writing 1 clears the pending bit
     */
    if (EXTI->PR & (1 << PinNumber))
    {
        EXTI->PR |= (1 << PinNumber);  // Clear by writing 1
    }
}
