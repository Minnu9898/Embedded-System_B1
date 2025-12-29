#include "stm32f446xx_i2c_driver.h"

/* ============================================================
 * Helper functions (private)
 * ============================================================ */

static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx)
{
    pI2Cx->CR1 |= (1 << I2C_CR1_START);
}

static void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx)
{
    pI2Cx->CR1 |= (1 << I2C_CR1_STOP);
}

static void I2C_ExecuteAddressPhaseWrite(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr)
{
    SlaveAddr = SlaveAddr << 1;
    SlaveAddr &= ~(1);              // Write
    pI2Cx->DR = SlaveAddr;
}

static void I2C_ExecuteAddressPhaseRead(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr)
{
    SlaveAddr = SlaveAddr << 1;
    SlaveAddr |= 1;                 // Read
    pI2Cx->DR = SlaveAddr;
}

static void I2C_ClearADDRFlag(I2C_Handle_t *pI2CHandle)
{
    uint32_t dummy;

    dummy = pI2CHandle->pI2Cx->SR1;
    dummy = pI2CHandle->pI2Cx->SR2;
    (void)dummy;
}

/* ============================================================
 * Peripheral Clock Control
 * ============================================================ */

void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi)
{
    if(EnorDi == ENABLE)
    {
        if(pI2Cx == I2C1)      I2C1_PCLK_EN();
        else if(pI2Cx == I2C2) I2C2_PCLK_EN();
        else if(pI2Cx == I2C3) I2C3_PCLK_EN();
    }
    else
    {
        if(pI2Cx == I2C1)      I2C1_PCLK_DI();
        else if(pI2Cx == I2C2) I2C2_PCLK_DI();
        else if(pI2Cx == I2C3) I2C3_PCLK_DI();
    }
}

/* ============================================================
 * Init and DeInit
 * ============================================================ */

void I2C_Init(I2C_Handle_t *pI2CHandle)
{
    uint32_t tempreg = 0;

    /* Enable clock */
    I2C_PeriClockControl(pI2CHandle->pI2Cx, ENABLE);

    /* ACK control */
    tempreg |= pI2CHandle->I2CConfig.I2C_ACKControl << I2C_CR1_ACK;
    pI2CHandle->pI2Cx->CR1 = tempreg;

    /* Configure FREQ (APB1 frequency) */
    tempreg = 0;
    tempreg |= RCC_GetPCLK1Value() / 1000000U;
    pI2CHandle->pI2Cx->CR2 = (tempreg & 0x3F);

    /* Configure device own address */
    tempreg = 0;
    tempreg |= pI2CHandle->I2CConfig.I2C_DeviceAddress << 1;
    tempreg |= (1 << 14); // Bit 14 must be kept 1
    pI2CHandle->pI2Cx->OAR1 = tempreg;

    /* Configure CCR */
    uint16_t ccr_value = 0;
    tempreg = 0;

    if(pI2CHandle->I2CConfig.I2C_SCLSpeed <= I2C_SCL_SPEED_SM)
    {
        ccr_value = (RCC_GetPCLK1Value()) / (2 * pI2CHandle->I2CConfig.I2C_SCLSpeed);
        tempreg |= (ccr_value & 0xFFF);
    }
    else
    {
        tempreg |= (1 << I2C_CCR_FS);

        if(pI2CHandle->I2CConfig.I2C_FMDutyCycle == I2C_FM_DUTY_2)
        {
            ccr_value = RCC_GetPCLK1Value() / (3 * pI2CHandle->I2CConfig.I2C_SCLSpeed);
        }
        else
        {
            tempreg |= (1 << I2C_CCR_DUTY);
            ccr_value = RCC_GetPCLK1Value() / (25 * pI2CHandle->I2CConfig.I2C_SCLSpeed);
        }

        tempreg |= (ccr_value & 0xFFF);
    }

    pI2CHandle->pI2Cx->CCR = tempreg;

    /* TRISE configuration */
    if(pI2CHandle->I2CConfig.I2C_SCLSpeed <= I2C_SCL_SPEED_SM)
    {
        pI2CHandle->pI2Cx->TRISE = (RCC_GetPCLK1Value()/1000000U) + 1;
    }
    else
    {
        pI2CHandle->pI2Cx->TRISE = ((RCC_GetPCLK1Value()*300)/1000000000U) + 1;
    }
}

void I2C_DeInit(I2C_RegDef_t *pI2Cx)
{
    if(pI2Cx == I2C1)      I2C1_REG_RESET();
    else if(pI2Cx == I2C2) I2C2_REG_RESET();
    else if(pI2Cx == I2C3) I2C3_REG_RESET();
}

/* ============================================================
 * Peripheral Control
 * ============================================================ */

void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi)
{
    if(EnOrDi == ENABLE)
        pI2Cx->CR1 |= (1 << I2C_CR1_PE);
    else
        pI2Cx->CR1 &= ~(1 << I2C_CR1_PE);
}

void I2C_ManageAcking(I2C_RegDef_t *pI2Cx, uint8_t EnorDi)
{
    if(EnorDi == I2C_ACK_ENABLE)
        pI2Cx->CR1 |= (1 << I2C_CR1_ACK);
    else
        pI2Cx->CR1 &= ~(1 << I2C_CR1_ACK);
}

/* ============================================================
 * Master Send Data (Polling)
 * ============================================================ */

void I2C_MasterSendData(I2C_Handle_t *pI2CHandle,
                        uint8_t *pTxBuffer,
                        uint32_t Len,
                        uint8_t SlaveAddr,
                        uint8_t Sr)
{
    /* Generate START */
    I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

    /* Wait for SB */
    while(! (pI2CHandle->pI2Cx->SR1 & I2C_FLAG_SB));

    /* Send address */
    I2C_ExecuteAddressPhaseWrite(pI2CHandle->pI2Cx, SlaveAddr);

    /* Wait for ADDR */
    while(! (pI2CHandle->pI2Cx->SR1 & I2C_FLAG_ADDR));

    I2C_ClearADDRFlag(pI2CHandle);

    /* Send data */
    while(Len > 0)
    {
        while(! (pI2CHandle->pI2Cx->SR1 & I2C_FLAG_TXE));
        pI2CHandle->pI2Cx->DR = *pTxBuffer;
        pTxBuffer++;
        Len--;
    }

    /* Wait for TXE & BTF */
    while(! (pI2CHandle->pI2Cx->SR1 & I2C_FLAG_TXE));
    while(! (pI2CHandle->pI2Cx->SR1 & I2C_FLAG_BTF));

    /* STOP */
    if(Sr == I2C_DISABLE_SR)
        I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
}
