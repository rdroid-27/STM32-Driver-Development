/*
 * stm32f407xx_spi_driver.h
 *
 *  Created on: Apr 28, 2025
 *      Author: GANDALF
 */

#ifndef INC_STM32F407XX_SPI_DRIVER_H_
#define INC_STM32F407XX_SPI_DRIVER_H_

#include "stm32f407xx.h"

// <------------------------------------------------------------------------------>

// Pin Configuration Structure for SPI
/* This structure is used to hold all the settings needed to configure SPI. Instead of setting each value separately, we put all the configurations into one structure for easy management and cleaner code.
 */
typedef struct
{
    uint8_t SPI_DeviceMode;
    uint8_t SPI_BusConfig;
    uint8_t SPI_SclkSpeed;
    uint8_t SPI_DFF;
    uint8_t SPI_CPOL;
    uint8_t SPI_CPHA;
    uint8_t SPI_SSM;
} SPI_Config_t;

// <------------------------------------------------------------------------------>

// Handle Structure for a SPI
/* This structure is used to group everything needed to initialize and use SPI.
 */
typedef struct
{
    SPI_RegDef_t *pSPIx;
    SPI_Config_t *SPI_Config;
} SPI_Handle_t;

// <------------------------------------------------------------------------------>

// Driver APIs

void SPI_Init(SPI_Handle_t *pSPI_Handle);
void SPI_Deinit(SPI_RegDef_t *pSPIx);

void SPI_PeriClkControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi);

void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);
void SPI_RecieveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer);

void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t *pHandle);

#endif /* INC_STM32F407XX_SPI_DRIVER_H_ */
