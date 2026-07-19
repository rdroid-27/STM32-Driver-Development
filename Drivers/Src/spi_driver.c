#include "spi_driver.h"

/**************************************************************
 * @function  SPI_PeriClockControl
 * @brief     Enables or disables peripheral clock for a given GPIO port
 * @param[in] pGPIOx - Base address of the GPIO peripheral (GPIOA, GPIOB, etc.)
 * @param[in] ENorDI - Enable or Disable macro:
 *                     - ENABLE (1) to enable clock
 *                     - DISABLE (0) to disable clock
 * @retval    None
 * @note      The RCC peripheral clock for the SPI must be enabled
 *            before any operations can be performed.
 **************************************************************/
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t ENorDI)
{
    if (ENorDI == ENABLE)
    {
        if (pSPIx == SPI1)
            SPI1_CLK_EN();
        if (pSPIx == SPI2)
            SPI2_CLK_EN();
        if (pSPIx == SPI3)
            SPI3_CLK_EN();
    }
    else
    {
        if (pSPIx == SPI1)
            SPI1_CLK_DI();
        if (pSPIx == SPI2)
            SPI2_CLK_DI();
        if (pSPIx == SPI3)
            SPI3_CLK_DI();
    }
}

/**************************************************************
 * @function  SPI_Init
 * @brief Initializes the SPI peripheral with the specified configuration
 * @param[in] pSPIHandle  Pointer to the SPI handle structure with config settings
 * @retval    None
 * @note      The RCC peripheral clock for the SPI must be enabled
 *            before any operations can be performed.
 **************************************************************/
void SPI_Init(SPI_Handle_t *pSPIHandle)
{
    // Enable clock for peripheral
    SPI_PeriClockControl(pSPIHandle->pSPIX, ENABLE);

    // 1. Configure SPI Device Mode
    pSPIHandle->pSPIX->CR1 |= (pSPIHandle->SPIConfig.SPI_DeviceMode << 2);

    // 2. Configure Bus
    if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
        pSPIHandle->pSPIX->CR1 |= (1 << 15);
    else if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
        pSPIHandle->pSPIX->CR1 &= ~(1 << 15);
    else if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SX_RX)
    {
        pSPIHandle->pSPIX->CR1 &= ~(1 << 15);
        pSPIHandle->pSPIX->CR1 |= (1 << 10);
    }

    // 3. Configure Serial Clock Speed (Baud Rate)
    pSPIHandle->pSPIX->CR1 &= ~(7 << 3);
    pSPIHandle->pSPIX->CR1 |= (pSPIHandle->SPIConfig.SPI_SclkSpeed << 3);

    // 4. Configure the DFF
    pSPIHandle->pSPIX->CR1 &= ~(1 << 11);
    pSPIHandle->pSPIX->CR1 |= (pSPIHandle->SPIConfig.SPI_DFF << 11);

    // 5. Configure the CPOL
    pSPIHandle->pSPIX->CR1 &= ~(1 << 1);
    pSPIHandle->pSPIX->CR1 |= (pSPIHandle->SPIConfig.SPI_CPOL << 1);

    // 6. Configure the CPHA
    pSPIHandle->pSPIX->CR1 &= ~(1 << 0);
    pSPIHandle->pSPIX->CR1 |= (pSPIHandle->SPIConfig.SPI_CPHA << 0);
}

/**************************************************************
 * @function  SPI_PeripheralControl
 * @brief Initializes the SPI peripheral with the specified configuration
 * @param[in] pSPIx   Pointer to the SPI peripheral base address (SPI1, SPI2, etc.)
 * @param[in] ENorDI  ENABLE or DISABLE macro to turn peripheral on or off
 * @retval    None
 **************************************************************/
void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
    if (EnorDi == ENABLE)
    {
        pSPIx->CR1 |= (1 << 6);
    }
    else
    {
        pSPIx->CR1 &= ~(1 << 6);
    }
}

/**************************************************************
 * @function  SPI_SSIConfig
 * @brief Enables or Disables the SSI for multimaster/MODEF situation
 * @param[in] pSPIx   Pointer to the SPI peripheral base address (SPI1, SPI2, etc.)
 * @param[in] ENorDI  ENABLE or DISABLE macro to turn clock on or off
 **************************************************************/
void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
    if (EnorDi == ENABLE)
    {
        pSPIx->CR1 |= (1 << 8);
    }
    else
    {
        pSPIx->CR1 &= ~(1 << 8);
    }
}

/**************************************************************
 * @function  SPI_DeInit
 * @brief Resets the SPI peripheral registers to their default state
 * @param[in] pSPIx  Pointer to the SPI peripheral base address
 **************************************************************/
void SPI_DeInit(SPI_RegDef_t *pSPIx)
{
    if (pSPIx == SPI1)
    {
        RCC->APB2RSTR |= (1 << 12);
        RCC->APB2RSTR &= ~(1 << 12);
    }
    else if (pSPIx == SPI2)
    {
        RCC->APB1RSTR |= (1 << 14);
        RCC->APB1RSTR &= ~(1 << 14);
    }
    else if (pSPIx == SPI3)
    {
        RCC->APB1RSTR |= (1 << 15);
        RCC->APB1RSTR &= ~(1 << 15);
    }
}

/**************************************************************
 * @function  SPI_SendData
 * @brief Sends data using SPI in blocking (polling) mode
 * @param[in] pSPIx      Pointer to the SPI peripheral base address
 * @param[in] pTxBuffer  Pointer to the data buffer to transmit
 * @param[in] len        Number of bytes to send
 * @retval    None
 * @note This is a blocking call
 **************************************************************/
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t len)
{
    // All the bits are sent
    while (len > 0)
    {
        // 1. Wait for Tx buffer to be empty
        while (!(pSPIx->SR & (1 << 1)))
            ;

        if ((uint8_t)(pSPIx->CR1 & (1 << 11)) == SPI_DFF_16)
        {
            // DFF is 16 bits
            pSPIx->DR = *((uint16_t *)pTxBuffer);
            len--;
            len--;
            pTxBuffer += 2;
        }
        else
        {
            // DFF is 8 bits
            pSPIx->DR = *(pTxBuffer);
            len--;
            pTxBuffer++;
        }
    }
    return;
}

/**************************************************************
 * @function  SPI_SendData
 * @brief Receives data using SPI in blocking (polling) mode
 * @param[in] pSPIx      Pointer to the SPI peripheral base address
 * @param[in] len        Number of bytes to receive
 * @param[out] pRxBuffer Pointer to the buffer where received data will be stored
 * @retval    None
 **************************************************************/
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t len)
{
    // All the bits are Recieved
    while (len > 0)
    {
        // 1. Wait for Rx buffer to be empty
        while ((pSPIx->SR & (1 << 0)))
            ;

        if ((uint8_t)(pSPIx->CR1 & (1 << 11)) == SPI_DFF_16)
        {
            // DFF is 16 bits
            *((uint16_t *)pRxBuffer) = pSPIx->DR;
            len--;
            len--;
            pRxBuffer += 2;
        }
        else
        {
            // DFF is 8 bits
            *pRxBuffer = pSPIx->DR;
            len--;
            pRxBuffer++;
        }
    }
    return;
}

/**************************************************************
 * @function  SPI_IRQInterruptConfig
 * @brief Enables or disables the SPI interrupt for a given IRQ number
 * @param[in] IRQNumber  IRQ number of the SPI peripheral
 * @param[in] ENorDI     ENABLE or DISABLE macro
 * @retval    None
 **************************************************************/
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t ENorDI);

/**************************************************************
 * @function  SPI_IRQPriorityConfig
 * @brief Configures the priority of the given SPI interrupt
 * @param[in] IRQPriority  Interrupt priority (lower value = higher priority)
 * @param[in] IRQNumber    IRQ number of the SPI peripheral
 * @retval    None
 **************************************************************/
void SPI_IRQPriorityConfig(uint32_t IRQPriority, uint8_t IRQNumber);

/**************************************************************
 * @function  SPI_IRQHandling
 * @brief Handles the SPI interrupt and clears interrupt flags
 * @param[in] pSPIHandle  Pointer to the SPI handle structure
 * @retval    None
 **************************************************************/
void SPI_IRQHandling(SPI_Handle_t *pSPIHandle);
