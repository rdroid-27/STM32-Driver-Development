#ifndef INC_USART_H_
#define INC_USART_H_

#include "stm32f103xx.h"

/*USART SR Macros*/
#define ORE (1 << 3)
#define RXNE (1 << 5)
#define TXE (1 << 7)
#define TC (1 << 6)

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

#endif // INC_USART_H_