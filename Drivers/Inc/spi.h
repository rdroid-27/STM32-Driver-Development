/**
 * @file spi.h
 * @brief Definitions for the STM32F103xx SPI Peripherals.
 *
 * This module provides definitions and macros for SPI peripherals.
 *
 * @author rdroid-27
 * @date July 2026
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_

#include "stm32f103xx.h"

/*<! SPI Register Structure >*/
typedef struct
{
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t CRCPR;
    volatile uint32_t RXCRCR;
    volatile uint32_t TXCRCR;
    volatile uint32_t I2SCFGR;
    volatile uint32_t I2SPR;
} SPI_RegDef_t;

// Map SPIx to SPI Register Structure
#define SPI1 ((SPI_RegDef_t *)SPI1_BASEADDR)
#define SPI2 ((SPI_RegDef_t *)SPI2_BASEADDR)
#define SPI3 ((SPI_RegDef_t *)SPI3_BASEADDR)

// Enable Clock for SPIx
#define SPI1_CLK_EN() (RCC->APB2ENR |= (1 << 12))
#define SPI2_CLK_EN() (RCC->APB1ENR |= (1 << 14))
#define SPI3_CLK_EN() (RCC->APB1ENR |= (1 << 15))

// Disable Clock for SPIx
#define SPI1_CLK_DI() (RCC->APB2ENR &= ~(1 << 12))
#define SPI2_CLK_DI() (RCC->APB1ENR &= ~(1 << 14))
#define SPI3_CLK_DI() (RCC->APB1ENR &= ~(1 << 15))

// SPI interrupts in NVIC
#define IRQ_NO_SPI1 35
#define IRQ_NO_SPI2 36
#define IRQ_NO_SPI3 51

#endif // INC_SPI_H_