/*
 * stm32f103xx.h
 *
 *  Created on: Jul 6, 2025
 *      Author: GANDALF
 */

#ifndef INC_STM32F103XX_H_
#define INC_STM32F103XX_H_

#include <stdint.h>

// Generic Macros
#define ENABLE 1
#define DISABLE 0
#define SET 1
#define RESET 0

/*******************************************************************************************
 *                            NVIC Register Macros (Cortex-M3)                             *
 *                                                                                         *
 * These macros define the memory-mapped addresses of NVIC registers used to control       *
 * external interrupts in ARM Cortex-M4 based STM32F4xx devices. Use them to enable,       *
 * disable, or manage IRQs via direct register access.                                     *
 *                                                                                         *
 * ➤ Interrupt Set-Enable Registers (ISERx)                                               *
 *     Used to enable external interrupts. Writing 1 to a bit enables the corresponding    *
 *     IRQ number. Each register controls 32 IRQs:                                         *
 *       - ISER0: IRQ  0–31                                                                *
 *       - ISER1: IRQ 32–63                                                                *
 *       - ISER2: IRQ 64–95                                                                *
 *                                                                                         *
 * ➤ Interrupt Clear-Enable Registers (ICERx)                                             *
 *     Used to disable external interrupts. Writing 1 clears (disables) the corresponding  *
 *     IRQ. Same IRQ ranges as ISERx apply.                                                *
 *******************************************************************************************/

#define NVIC_ISER0 ((volatile uint32_t *)0xE000E100)
#define NVIC_ISER1 ((volatile uint32_t *)0xE000E104)
#define NVIC_ISER2 ((volatile uint32_t *)0xE000E108)

#define NVIC_ICER0 ((volatile uint32_t *)0xE000E180)
#define NVIC_ICER1 ((volatile uint32_t *)0xE000E184)
#define NVIC_ICER2 ((volatile uint32_t *)0xE000E188)

#define NVIC_ISPR0 ((volatile uint32_t *)0xE000E200)
#define NVIC_ISPR1 ((volatile uint32_t *)0xE000E204)
#define NVIC_ISPR2 ((volatile uint32_t *)0xE000E208)

#define NVIC_ICPR0 ((volatile uint32_t *)0xE000E280)
#define NVIC_ICPR1 ((volatile uint32_t *)0xE000E284)
#define NVIC_ICPR2 ((volatile uint32_t *)0xE000E288)

#define NVIC_IPR_BASEADDR ((volatile uint32_t *)0xE000E400)

/*******************************************************************************************
 *                                STM32F103x MCU Base Addresses                            *
 *                                                                                         *
 * This section defines base addresses for all memory-mapped peripherals in STM32F103x     *
 * series, grouped by their corresponding bus (APB1, APB2, AHB). These macros allow        *
 * register-level access to peripheral control and data registers in bare-metal programs.  *
 *                                                                                         *
 * ➤ APB1 Peripherals (Advanced Peripheral Bus 1)                                         *
 *    Lower-speed peripherals like timers, USART2-5, I2C1/2, SPI2/3, etc.                  *
 *                                                                                         *
 * ➤ APB2 Peripherals (Advanced Peripheral Bus 2)                                         *
 *    Higher-speed peripherals like GPIOs, USART1, SPI1, ADCs, and advanced timers.        *
 *                                                                                         *
 * ➤ AHB Peripherals (Advanced High-Performance Bus)                                      *
 *    High-speed memory and DMA access, RCC, Flash, CRC, FSMC, and USB OTG.                *
 *                                                                                         *
 * Address Ranges:                                                                         *
 * - APB1: 0x4000 0000 - 0x4000 FFFF                                                       *
 * - APB2: 0x4001 0000 - 0x4001 FFFF                                                       *
 * - AHB:  0x4002 0000 - 0x5003 FFFF and 0xA000 0000 (FSMC)                                *
 *******************************************************************************************/

/*<! Memory Addresses >*/
#define SRAM_BASEADDR 0x20000000U
#define FLASH_BASEADDR 0x08000000U

/*<! Bus Addresses >*/
#define AHB_BASEADDR 0x40018000U
#define APB2_BASEADDR 0x40010000U
#define APB1_BASEADDR 0x40000000U

/*<! APB1 Preipherals Addresses >*/
#define TIM2_BASEADDR 0x40000000U
#define TIM3_BASEADDR 0x40000400U
#define TIM4_BASEADDR 0x40000800U
#define TIM5_BASEADDR 0x40000C00U
#define TIM6_BASEADDR 0x40001000U
#define TIM7_BASEADDR 0x40001400U
#define TIM12_BASEADDR 0x40001800U
#define TIM13_BASEADDR 0x40001C00U
#define TIM14_BASEADDR 0x40002000U
#define RTC_BASEADDR 0x40002800U
#define WWDG_BASEADDR 0x40002C00U
#define IWDG_BASEADDR 0x40003000U
#define SPI2_BASEADDR 0x40003800U
#define SPI3_BASEADDR 0x40003C00U
#define USART2_BASEADDR 0x40004400U
#define USART3_BASEADDR 0x40004800U
#define UART4_BASEADDR 0x40004C00U
#define UART5_BASEADDR 0x40005000U
#define I2C1_BASEADDR 0x40005400U
#define I2C2_BASEADDR 0x40005800U
#define USB_DEVICE_FS_BASEADDR 0x40005C00U
#define USB_CAN_SRAM_BASEADDR 0x40006000U
#define CAN2_BASEADDR 0x40006800U
#define CAN1_BASEADDR 0x40006400U
#define BKP_BASEADDR 0x40006C00U
#define PWR_BASEADDR 0x40007000U
#define DAC_BASEADDR 0x40007400U

#define APB1_RESERVED1_BASE 0x40007800U // Reserved up to 0x4000FFFFU

/*<! APB2 Preipherals Addresses >*/
#define AFIO_BASEADDR 0x40010000U
#define EXTI_BASEADDR 0x40010400U
#define GPIOA_BASEADDR 0x40010800U
#define GPIOB_BASEADDR 0x40010C00U
#define GPIOC_BASEADDR 0x40011000U
#define GPIOD_BASEADDR 0x40011400U
#define GPIOE_BASEADDR 0x40011800U
#define GPIOF_BASEADDR 0x40011C00U
#define GPIOG_BASEADDR 0x40012000U
#define ADC1_BASEADDR 0x40012400U
#define ADC2_BASEADDR 0x40012800U
#define TIM1_BASEADDR 0x40012C00U
#define SPI1_BASEADDR 0x40013000U
#define TIM8_BASEADDR 0x40013400U
#define USART1_BASEADDR 0x40013800U
#define ADC3_BASEADDR 0x40013C00U
#define TIM9_BASEADDR 0x40014C00U
#define TIM10_BASEADDR 0x40015000U
#define TIM11_BASEADDR 0x40015400U

#define APB2_RESERVED1_BASE 0x40014000U // Reserved (0x40014000 - 0x40014BFF)
#define APB2_RESERVED2_BASE 0x40015800U // Reserved (0x40015800 - 0x40017FFF)

/*<! APB2 Preipherals Addresses >*/
#define DMA1_BASEADDR 0x40020000U
#define DMA2_BASEADDR 0x40020400U
#define RCC_BASEADDR 0x40021000U
#define FLASH_INTF_BASEADDR 0x40022000U
#define CRC_BASEADDR 0x40023000U
#define ETHERNET_BASEADDR 0x40028000U
#define SDIO_BASEADDR 0x40018000U
#define USB_OTG_FS_BASEADDR 0x50000000U
#define FSMC_BASEADDR 0xA0000000U

#define AHB_RESERVED1_BASE 0x40020800U // Reserved (0x40020800 - 0x40020FFF)
#define AHB_RESERVED2_BASE 0x40021400U // Reserved (0x40021400 - 0x40021FFF)
#define AHB_RESERVED3_BASE 0x40023400U // Reserved (0x40023400 - 0x40027FFF)
#define AHB_RESERVED4_BASE 0x40030000U // Reserved (0x40030000 - 0x4FFFFFFF)
#define AHB_RESERVED5_BASE 0x40018400U // Reserved (0x40018400 - 0x4001FFFF)
// ==============================================================================

/*******************************************************************************************
 *                          STM32F103x Peripheral Register Definitions                     *
 *                                                                                         *
 * This section defines register offsets and register structures for each peripheral       *
 * (e.g., RCC, GPIO, TIM, USART, etc.) based on the STM32F103x reference manual. These     *
 * definitions allow direct register-level access to peripheral functionality.             *
 *                                                                                         *
 * ➤ Purpose:                                                                             *
 *    - Map each peripheral's register layout using `typedef struct`                       *
 *    - Create peripheral access macros (e.g., #define RCC ((RCC_RegDef_t*) RCC_BASEADDR))*
 *                                                                                         *
 * ➤ Usage:                                                                               *
 *    After defining base addresses, we bind them to C structs representing the register   *
 *    map of each peripheral. These enable safe and readable register access in code.      *
 *******************************************************************************************/

// ==========================================================================================

/*<! RCC Register Structure >*/
typedef struct
{
    volatile uint32_t CR;       // 0x00: Clock Control Register
    volatile uint32_t CFGR;     // 0x04: Clock Configuration Register
    volatile uint32_t CIR;      // 0x08: Clock Interrupt Register
    volatile uint32_t APB2RSTR; // 0x0C: APB2 Peripheral Reset Register
    volatile uint32_t APB1RSTR; // 0x10: APB1 Peripheral Reset Register
    volatile uint32_t AHBENR;   // 0x14: AHB Peripheral Clock Enable Register
    volatile uint32_t APB2ENR;  // 0x18: APB2 Peripheral Clock Enable Register
    volatile uint32_t APB1ENR;  // 0x1C: APB1 Peripheral Clock Enable Register
    volatile uint32_t BDCR;     // 0x20: Backup Domain Control Register
    volatile uint32_t CSR;      // 0x24: Control/Status Register
    volatile uint32_t AHBSTR;   // 0x28: AHB Peripheral Reset Register (connectivity line only)
    volatile uint32_t CFGR2;    // 0x2C: Clock Configuration Register 2 (connectivity line only)
} RCC_RegDef_t;

// Map RCC to RCC Register Structure
#define RCC ((RCC_RegDef_t *)RCC_BASEADDR)

// ==========================================================================================

/*<! EXTI Register Structure >*/
typedef struct
{
    volatile uint32_t IMR;   // 0x00: Interrupt Mask Register
    volatile uint32_t EMR;   // 0x04: Event Mask Register
    volatile uint32_t RTSR;  // 0x08: Rising Trigger Selection Register
    volatile uint32_t FTSR;  // 0x0C: Falling Trigger Selection Register
    volatile uint32_t SWIER; // 0x10: Software Interrupt Event Register
    volatile uint32_t PR;    // 0x14: Pending Register
} EXTI_RegDef_t;

// Map EXTI to EXTI Register Structure
#define EXTI ((EXTI_RegDef_t *)EXTI_BASEADDR)

// IRQ (Interrupt Request) Numbers
#define IRQ_NO_EXTI0 6
#define IRQ_NO_EXTI1 7
#define IRQ_NO_EXTI2 8
#define IRQ_NO_EXTI3 9
#define IRQ_NO_EXTI4 10
#define IRQ_NO_EXTI9_5 23
#define IRQ_NO_EXTI15_10 40

// ==========================================================================================

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

// ==========================================================================================

/*<! I2C Register Structure >*/
typedef struct
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
} I2C_RegDef_t;

// Map I2Cx to I2C Register Structure
#define I2C1 ((I2C_RegDef_t *)I2C1_BASEADDR)
#define I2C3 ((I2C_RegDef_t *)I2C2_BASEADDR)

// Enable Clock for I2Cx
#define I2C1_CLK_EN() (RCC->APB1ENR |= (1 << 21))
#define I2C2_CLK_EN() (RCC->APB1ENR |= (1 << 22))

// Disable Clock for I2Cx
#define I2C1_CLK_DI() (RCC->APB1ENR &= ~(1 << 21))
#define I2C2_CLK_DI() (RCC->APB1ENR &= ~(1 << 22))

// ==========================================================================================
/*<! USART Register Structure >*/
typedef struct
{
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;
} USART_RegDef_t;

// Map USARTx to USART Register Structure
#define USART1 ((USART_RegDef_t *)USART1_BASEADDR)
#define USART2 ((USART_RegDef_t *)USART2_BASEADDR)
#define USART3 ((USART_RegDef_t *)USART3_BASEADDR)
#define UART4 ((USART_RegDef_t *)UART4_BASEADDR)
#define UART5 ((USART_RegDef_t *)UART5_BASEADDR)

// Enable Clock for USARTx
#define USART1_CLK_EN() (RCC->APB2ENR |= (1 << 14))
#define USART2_CLK_EN() (RCC->APB1ENR |= (1 << 17))
#define USART3_CLK_EN() (RCC->APB1ENR |= (1 << 18))
#define UART4_CLK_EN() (RCC->APB1ENR |= (1 << 19))
#define UART5_CLK_EN() (RCC->APB1ENR |= (1 << 20))

// Disable Clock for USARTx
#define USART1_CLK_DI() (RCC->APB2ENR &= ~(1 << 14))
#define USART2_CLK_DI() (RCC->APB1ENR &= ~(1 << 17))
#define USART3_CLK_DI() (RCC->APB1ENR &= ~(1 << 18))
#define UART4_CLK_DI() (RCC->APB1ENR &= ~(1 << 19))
#define UART5_CLK_DI() (RCC->APB1ENR &= ~(1 << 20))

// ==========================================================================================

#include "gpio.h"
#include "gpio_driver.h"
#include "spi_driver.h"
#include "usart_driver.h"
#include "rcc_driver.h"

#endif /* INC_STM32F103XX_H_ */
