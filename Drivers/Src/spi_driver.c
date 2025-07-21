/*
 * spi_driver.c
 *
 *  Created on: Jul 21, 2025
 *      Author: GANDALF
 */

#include "spi_driver.h"

/**
 * @brief Enables or disables the peripheral clock for the given SPI port
 * @param[in] pSPIx   Pointer to the SPI peripheral base address (SPI1, SPI2, etc.)
 * @param[in] ENorDI  ENABLE or DISABLE macro to turn clock on or off
 */
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

/**
 * @brief Initializes the SPI peripheral with the specified configuration
 * @param[in] pSPIHandle  Pointer to the SPI handle structure with config settings
 * @note Call SPI_PeriClockControl() before this to enable the clock.
 */
void SPI_Init(SPI_Handle_t *pSPIHandle)
{
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

/**
 * @brief Resets the SPI peripheral registers to their default state
 * @param[in] pSPIx  Pointer to the SPI peripheral base address
 */
void SPI_DeInit(SPI_RegDef_t *pSPIx);

/**
 * @brief Sends data using SPI in blocking (polling) mode
 * @param[in] pSPIx      Pointer to the SPI peripheral base address
 * @param[in] pTxBuffer  Pointer to the data buffer to transmit
 * @param[in] len        Number of bytes to send
 */
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t len);

/**
 * @brief Receives data using SPI in blocking (polling) mode
 * @param[in] pSPIx      Pointer to the SPI peripheral base address
 * @param[out] pRxBuffer Pointer to the buffer where received data will be stored
 * @param[in] len        Number of bytes to receive
 */
void SPI_RecieveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t len);

/**
 * @brief Enables or disables the SPI interrupt for a given IRQ number
 * @param[in] IRQNumber  IRQ number of the SPI peripheral
 * @param[in] ENorDI     ENABLE or DISABLE macro
 */
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t ENorDI);

/**
 * @brief Configures the priority of the given SPI interrupt
 * @param[in] IRQPriority  Interrupt priority (lower value = higher priority)
 * @param[in] IRQNumber    IRQ number of the SPI peripheral
 */
void SPI_IRQPriorityConfig(uint32_t IRQPriority, uint8_t IRQNumber);

/**
 * @brief Handles the SPI interrupt and clears interrupt flags
 * @param[in] pSPIHandle  Pointer to the SPI handle structure
 */
void SPI_IRQHandling(SPI_Handle_t *pSPIHandle);
