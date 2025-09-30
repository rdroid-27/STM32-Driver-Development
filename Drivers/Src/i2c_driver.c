#include "i2c_driver.h"

uint16_t AHB_PRESCALAR[8] = {2, 4, 8, 16, 64, 128, 256, 512};
uint16_t APB1_PRESCALAR[4] = {2, 4, 8, 16};

uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName)
{
    if (pI2Cx->SR1 & FlagName)
    {
        return FLAG_SET;
    }
    else
        return FLAG_RESET;
}

uint32_t RCC_GetPCLK1Value(void)
{
    uint32_t pclk1, sysclk;
    uint8_t clk_src = ((RCC->CFGR >> 2) & 0x3);
    uint8_t temp, ahbp, apb1p;
    if (clk_src == 0)
        sysclk = 16000000;
    else if (clk_src == 1)
        sysclk = 8000000;
    else if (clk_src == 2)
        ;
    // PLL based clock source
    else
        // Clock not allowed
        return 0;

    // For AHB
    temp = ((RCC->CFGR >> 4) & 0xF);
    if (temp < 8)
        ahbp = 1;
    else
        ahbp = AHB_PRESCALAR[temp - 8];

    // For APB
    temp = ((RCC->CFGR >> 10) & 0x7);
    if (temp < 8)
        apb1p = 1;
    else
        apb1p = APB1_PRESCALAR[temp - 4];

    pclk1 = (sysclk / ahbp) / apb1p;

    return pclk1;
}

/**
 * @brief Enables or disables the peripheral clock for the given I2C port
 * @param[in] pI2Cx   Pointer to the I2C peripheral base address (I2C1, I2C2, etc.)
 * @param[in] ENorDI  ENABLE or DISABLE macro to turn clock on or off
 */
void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t ENorDI)
{
    if (ENorDI == ENABLE)
    {
        if (pI2Cx == I2C1)
            I2C1_CLK_EN();
        else if (pI2Cx == I2C1)
            I2C1_CLK_EN();
    }
    else
    {
        if (pI2Cx == I2C1)
            I2C1_CLK_DI();
        else if (pI2Cx == I2C1)
            I2C1_CLK_DI();
    }
}

void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t ENorDI)
{
    if (ENorDI == ENABLE)
    {
        pI2Cx->CR1 |= (1 << 0);
    }
    else
    {
        pI2Cx->CR1 &= ~(1 << 0);
    }
}

void I2C_Init(I2C_Handle_t *pI2CHandle)
{
    uint32_t temp_reg = 0;

    // Enable the acknoledgement
    temp_reg |= (pI2CHandle->I2CConfig.I2C_ACKControl << 10);
    pI2CHandle->pI2Cx->CR1 = temp_reg;

    // Configure the clock frequency
    temp_reg = 0;
    temp_reg = RCC_GetPCLK1Value() / 1000000U;
    pI2CHandle->pI2Cx->CR2 = (temp_reg & 0x3F);

    // Program the Device Own Address
    temp_reg = 0;
    temp_reg = pI2CHandle->I2CConfig.I2C_DeviceAddress << 1;
    temp_reg |= 1 << 14;
    pI2CHandle->pI2Cx->OAR1 = temp_reg;

    // CCR Calculations
    temp_reg = 0;
    uint16_t ccr_value = 0;
    if (pI2CHandle->I2CConfig.I2C_SCLSpeed <= I2C_SCL_SPEED_SM)
    {
        // Configure the SM Mode
        ccr_value = RCC_GetPCLK1Value() / (2 * pI2CHandle->I2CConfig.I2C_SCLSpeed);
        temp_reg |= ccr_value & 0x0FFF;
    }
    else
    {
        // Configure the FM Mode
        temp_reg |= 1 << 15;
        ccr_value = RCC_GetPCLK1Value() / (2 * pI2CHandle->I2CConfig.I2C_SCLSpeed);
        if (pI2CHandle->I2CConfig.I2C_FmDutyCycle == I2C_DUTY_2)
        {
            ccr_value = RCC_GetPCLK1Value() / (3 * pI2CHandle->I2CConfig.I2C_SCLSpeed);
        }
        else if (pI2CHandle->I2CConfig.I2C_FmDutyCycle == I2C_DUTY_16_9)
        {
            ccr_value = RCC_GetPCLK1Value() / (25 * pI2CHandle->I2CConfig.I2C_SCLSpeed);
        }
        temp_reg |= ccr_value & 0x0FFF;
    }
    pI2CHandle->pI2Cx->CCR = temp_reg;

    // TRISE Calculations
    if (pI2CHandle->I2CConfig.I2C_SCLSpeed <= I2C_SCL_SPEED_SM)
    {
        // SM Mode

        temp_reg = (RCC_GetPCLK1Value() / 1000000U) + 1;
    }
    else
    {
        // FM Mode
        temp_reg = ((RCC_GetPCLK1Value() * 300) / 1000000000U) + 1;
    }
    pI2CHandle->pI2Cx->TRISE = (temp_reg & 0x3F);
}

void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddr)
{
    // 1. Generate Start Condition
    pI2CHandle->pI2Cx->CR1 |= (1 << I2C_CR1_START);

    // 2. Confirm the generation is complete by checking the SB flag in SR1. Until SB is cleared SCL will be stretched (pulled to low).
    while (!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_SB))
        ;

    // 3. Send the Addrerss of the slave with the R/nW bit set to 0 (total 8 Bits)
    pI2CHandle->pI2Cx->DR = (SlaveAddr << 1) & ~(1 << 0);

    // 4. Confirm that address phase is completed by checking the ADDR flag in the SR1
    while (!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_ADDR))
        ;

    // 5. Clear the ADDR flag according to its software sequence. Until ADDR is cleared SCL will be stretched (Pulled to LOW)
    uint32_t dummyRead = pI2CHandle->pI2Cx->SR1;
    dummyRead = pI2CHandle->pI2Cx->SR2;
    (void)dummyRead;

    // 6. Send data until Len becomes 0.
    while (Len > 0)
    {
        // Check if TXE is set
        while (!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_TxE))
            ;
        pI2CHandle->pI2Cx->DR = *pTxBuffer;
        pTxBuffer++;
        Len--;
    }

    // 7. When Len becomes 0, wait for TXE=1 and BTF=1 before generating the STOP condition, TXE=1 and BTF=1 means that both SR and DR are empty and next transmission should begin. When BTF=1 SCL will be stretched (pulled to LOW)
    while (!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_TxE))
        ;
    while (!I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_BTF))
        ;

    // 8. Genarate the STOP condition
    pI2CHandle->pI2Cx->CR1 |= (1 << I2C_CR1_STOP);
}
