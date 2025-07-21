/*
 * spi_driver.h
 *
 *  Created on: Jul 21, 2025
 *      Author: GANDALF
 */

#ifndef INC_SPI_DRIVER_H_
#define INC_SPI_DRIVER_H_

#include "stm32f103xx.h"

// SPI Macros
#define SPI_MODE_MASTER             1
#define SPI_MODE_SLAVE              0

#define SPI_BUS_CONFIG_HD           1
#define SPI_BUS_CONFIG_FD           2
#define SPI_BUS_CONFIG_SX_RX        3

#define SPI_SCLK_SPEED_DIV2         0
#define SPI_SCLK_SPEED_DIV4         1
#define SPI_SCLK_SPEED_DIV8         2
#define SPI_SCLK_SPEED_DIV16        3
#define SPI_SCLK_SPEED_DIV32        4
#define SPI_SCLK_SPEED_DIV64        5
#define SPI_SCLK_SPEED_DIV128       6
#define SPI_SCLK_SPEED_DIV256       7

#define SPI_DFF_8                   0
#define SPI_DFF_16                  1

#define SPI_CPOL_HIGH               1
#define SPI_CPOL_LOW                0

#define SPI_CPHA_HIGH               1
#define SPI_CPHA_LOW                0

#define SPI_SSM_EN                  1
#define SPI_SSM_DI                  0


// SPI Configuration Structure
typedef struct
{
    volatile uint8_t SPI_DeviceMode; // Device mode: Master (1) or Slave (0)
    volatile uint8_t SPI_BusConfig;  // Bus configuration: Full-duplex, Half-duplex, or Simplex RX-only
    volatile uint8_t SPI_SclkSpeed;  // Serial clock speed (baud rate control)
    volatile uint8_t SPI_DFF;        // Data frame format: 8-bit or 16-bit
    volatile uint8_t SPI_CPOL;       // Clock polarity: Low (0) or High (1) when idle
    volatile uint8_t SPI_CPHA;       // Clock phase: Data sampling edge (1st or 2nd)
    volatile uint8_t SPI_SSM;        // Software slave management: Enabled or Disabled
} SPI_Config_t;

typedef struct
{
    SPI_RegDef_t *pSPIX;
    SPI_Config_t SPIConfig;
} SPI_Handle_t;

/**************************************************************
 *                     SPI Driver API Prototypes             *
 **************************************************************/

// Enables or disables the peripheral clock for the given SPI port
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t ENorDI);

// Initializes the SPI peripheral with the specified configuration
void SPI_Init(SPI_Handle_t *pSPIHandle);

// Resets the SPI peripheral registers to their default state
void SPI_DeInit(SPI_RegDef_t *pSPIx);

// Sends data using the SPI peripheral in blocking mode
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t len);

// Receives data using the SPI peripheral in blocking mode
void SPI_RecieveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t len);

// Enables or disables the interrupt for the given SPI IRQ number
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t ENorDI);

// Sets the priority of the given SPI interrupt number
void SPI_IRQPriorityConfig(uint32_t IRQPriority, uint8_t IRQNumber);

// Handles the SPI interrupt and clears the flags
void SPI_IRQHandling(SPI_Handle_t *pSPIHandle);

#endif /* INC_SPI_DRIVER_H_ */
