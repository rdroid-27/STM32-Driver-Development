#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include "stm32f103xx.h"

/*<! GPIO Register Structure >*/
typedef struct
{
    volatile uint32_t CRL;  // 0x00: Port configuration register low (pins 0–7)
    volatile uint32_t CRH;  // 0x04: Port configuration register high (pins 8–15)
    volatile uint32_t IDR;  // 0x08: Input data register
    volatile uint32_t ODR;  // 0x0C: Output data register
    volatile uint32_t BSRR; // 0x10: Bit set/reset register
    volatile uint32_t BRR;  // 0x14: Bit reset register
    volatile uint32_t LCKR; // 0x18: Port configuration lock register
} GPIO_RegDef_t;

// Map GPIOs to GPIO Register Structure
#define GPIOA ((GPIO_RegDef_t *)GPIOA_BASEADDR)
#define GPIOB ((GPIO_RegDef_t *)GPIOB_BASEADDR)
#define GPIOC ((GPIO_RegDef_t *)GPIOC_BASEADDR)
#define GPIOD ((GPIO_RegDef_t *)GPIOD_BASEADDR)
#define GPIOE ((GPIO_RegDef_t *)GPIOE_BASEADDR)
#define GPIOF ((GPIO_RegDef_t *)GPIOF_BASEADDR)
#define GPIOG ((GPIO_RegDef_t *)GPIOG_BASEADDR)

/*<! AFIO Register Structure >*/
typedef struct
{
    volatile uint32_t EVCR;      // 0x00: Event Control Register
    volatile uint32_t MAPR;      // 0x04: AF Remap and Debug I/O Configuration Register
    volatile uint32_t EXTICR[4]; // 0x08–0x14: External Interrupt Configuration Registers(EXTICR1–EXTICR4)
    volatile uint32_t MAPR2;     // 0x18: AF Remap and Debug I/O Configuration Register 2
} AFIO_RegDef_t;

// Map AFIO to AFIO Register Structure
#define AFIO ((AFIO_RegDef_t *)AFIO_BASEADDR)

// Enable Clock for GPIOs
#define GPIOA_CLK_EN() (RCC->APB2ENR |= (1 << 2))
#define GPIOB_CLK_EN() (RCC->APB2ENR |= (1 << 3))
#define GPIOC_CLK_EN() (RCC->APB2ENR |= (1 << 4))
#define GPIOD_CLK_EN() (RCC->APB2ENR |= (1 << 5))
#define GPIOE_CLK_EN() (RCC->APB2ENR |= (1 << 6))

// Disable Clock for GPIOs
#define GPIOA_CLK_DI() (RCC->APB2ENR &= ~(1 << 2))
#define GPIOB_CLK_DI() (RCC->APB2ENR &= ~(1 << 3))
#define GPIOC_CLK_DI() (RCC->APB2ENR &= ~(1 << 4))
#define GPIOD_CLK_DI() (RCC->APB2ENR &= ~(1 << 5))
#define GPIOE_CLK_DI() (RCC->APB2ENR &= ~(1 << 6))

// Enable Clock for AFIO
#define AFIO_CLK_EN() (RCC->APB2ENR |= (1 << 0))

// Disable Clock for AFIO
#define AFIO_CLK_DI() (RCC->APB2ENR &= ~(1 << 0))

#endif