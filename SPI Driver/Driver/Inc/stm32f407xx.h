/*
 * stm32f407xx.h
 *
 *  Created on: Apr 23, 2025
 *      Author: GANDALF
 */
#ifndef INC_STM32F407XX_H_
 #define INC_STM32F407XX_H_
 
 #include <stdint.h>
 
// <------------------------------------------------------------------------------> 
//                      BASE ADDRESSES

/*  -This sections defines the base address of all the Memories, Peripheral Buses and Peripherals lying on that bus.
*/
 //==========================================================
 // Base Address of MEMORIES
 #define FLASH_BASEADDR						         0x08000000U
 #define SRAM1_BASEADDR						         0x20000000U
 #define SRAM2_BASEADDR						         0x2001C000U
 #define ROM								            0x1FFF0000U
 #define SRAM								            SRAM1_BASEADDR
 //==========================================================
 
 
 //==========================================================
 // Base Address of PERIPHERALS BUSES
 #define PERIPH_BASE							         0x40000000U
 #define APB1_PERIPHBASE						      PERIPH_BASE
 #define APB2_PERIPHBASE						      0x40010000U
 #define AHB1_PERIPHBASE						      0x40020000U
 #define AHB2_PERIPHBASE						      0x50000000U
 #define AHB3_PERIPHBASE						      0xA0000000U
 //==========================================================
 
 //==========================================================
 // Base Address of APB1 PERIPHERALS 
 #define TIM2_BASEADDR                          0x40000000U
 #define TIM3_BASEADDR                          0x40000400U
 #define TIM4_BASEADDR                          0x40000800U
 #define TIM5_BASEADDR                          0x40000C00U
 #define TIM6_BASEADDR                          0x40001000U
 #define TIM7_BASEADDR                          0x40001400U
 #define TIM12_BASEADDR                         0x40001800U
 #define TIM13_BASEADDR                         0x40001C00U
 #define TIM14_BASEADDR                         0x40002000U
 #define RTC_BKP_BASEADDR                       0x40002800U
 #define WWDG_BASEADDR                          0x40002C00U
 #define IWDG_BASEADDR                          0x40003000U
 #define I2S2EXT_BASEADDR                       0x40003400U
 #define SPI2_I2S2_BASEADDR                     0x40003800U
 #define SPI3_I2S3_BASEADDR                     0x40003C00U
 #define I2S3EXT_BASEADDR                       0x40004000U
 #define USART2_BASEADDR                        0x40004400U
 #define USART3_BASEADDR                        0x40004800U
 #define UART4_BASEADDR                         0x40004C00U
 #define UART5_BASEADDR                         0x40005000U
 #define I2C1_BASEADDR                          0x40005400U
 #define I2C2_BASEADDR                          0x40005800U
 #define I2C3_BASEADDR                          0x40005C00U
 #define CAN1_BASEADDR                          0x40006400U
 #define CAN2_BASEADDR                          0x40006800U
 #define PWR_BASEADDR                           0x40007000U
 #define DAC_BASEADDR                           0x40007400U
 #define UART7_BASEADDR                         0x40007800U
 #define UART8_BASEADDR                         0x40007C00U
 //==========================================================
 
 //==========================================================
 // Base Address of APB2 PERIPHERALS
 #define TIM1_BASEADDR                          0x40010000U
 #define USART1_BASEADDR                        0x40011000U
 #define USART6_BASEADDR                        0x40011400U
 #define ADC1_2_3_BASEADDR                      0x40012000U                     // Shared base address for ADC1, ADC2, ADC3
 #define SDIO_BASEADDR                          0x40012C00U
 #define SPI1_BASEADDR                          0x40013000U
 #define SPI4_BASEADDR                          0x40013400U
 #define SYSCFG_BASEADDR                        0x40013800U
 #define EXTI_BASEADDR                          0x40013C00U
 #define TIM9_BASEADDR                          0x40014000U
 #define TIM10_BASEADDR                         0x40014400U
 #define TIM11_BASEADDR                         0x40014800U
 #define SPI5_BASEADDR                          0x40015000U
 #define SPI6_BASEADDR                          0x40015400U
 #define SAI1_BASEADDR                          0x40015800U
 #define LCD_TFT_BASEADDR                       0x40016800U
 //==========================================================

 //==========================================================
 // Base Address of AHB1 PERIPHERALS
 #define GPIOA_BASEADDR                         0x40020000U
 #define GPIOB_BASEADDR                         0x40020400U
 #define GPIOC_BASEADDR                         0x40020800U
 #define GPIOD_BASEADDR                         0x40020C00U
 #define GPIOE_BASEADDR                         0x40021000U
 #define GPIOF_BASEADDR                         0x40021400U
 #define GPIOG_BASEADDR                         0x40021800U
 #define GPIOH_BASEADDR                         0x40021C00U
 #define GPIOI_BASEADDR                         0x40022000U
 #define GPIOJ_BASEADDR                         0x40022400U
 #define GPIOK_BASEADDR                         0x40022800U
 #define CRC_BASEADDR                           0x40023000U
 #define RCC_BASEADDR                           0x40023800U
 #define FLASH_INTERFACE_BASEADDR               0x40023C00U
 #define BKPSRAM_BASEADDR                       0x40024000U
 #define DMA1_BASEADDR                          0x40026000U
 #define DMA2_BASEADDR                          0x40026400U
 #define ETHERNET_BASEADDR                      0x40028000U
 #define DMA2D_BASEADDR                         0x4002B000U
 #define USB_OTG_HS_BASEADDR                    0x40040000U
 //==========================================================
 
 //==========================================================
 // Base Address of AHB2 PERIPHERALS
 #define USB_OTG_FS_BASEADDR                    0x50000000U
 #define DCMI_BASEADDR                          0x50050000U
 #define CRYP_BASEADDR                          0x50060000U
 #define HASH_BASEADDR                          0x50060400U
 #define RNG_BASEADDR                           0x50060800U 
 //==========================================================

 //==========================================================
 // Base Address of AHB3 PERIPHERALS
 #define FSMC_BASEADDR                          0xA0000000U                     // FSMC (Flexible Static Memory Controller)
 //==========================================================

 //==========================================================
 // Generic Macros
  #define ENABLE                                1
  #define DISABLE                               0
  #define SET                                   1
  #define RESET                                 0
  #define GPIO_PIN_SET                          1
  #define GPIO_PIN_RESET                        0
 //==========================================================

// <------------------------------------------------------------------------------> 

//                      PERIPHERAL REGISTERS DEFINITION STRUCTURES

/*  -In different projects, you might need to use different registers of a peripheral.
    -So, creating a macro for every single register would be difficult and messy. A better way is to use a structure.
    -When we create a structure and set its base address to the peripheral's base address, all the members of the structure will point to the correct registers.
    -This makes it easy to access and work with the registers.
*/

 //==========================================================
 // Structure for GPIO Registers
 typedef struct
 {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];
 } GPIO_RegDef_t;
 //==========================================================

 //==========================================================
 // Structure for RCC Registers
 typedef struct
 {
    volatile uint32_t CR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t AHB1RSTR;
    volatile uint32_t AHB2RSTR;
    volatile uint32_t AHB3RSTR;
    volatile uint32_t RESERVED1;
    volatile uint32_t APB1RSTR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t RESERVED2[2];
    volatile uint32_t AHB1ENR;
    volatile uint32_t AHB2ENR;
    volatile uint32_t AHB3ENR;
    volatile uint32_t RESERVED3;
    volatile uint32_t APB1ENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t RESERVED4[2];
    volatile uint32_t AHB1LPENR;
    volatile uint32_t AHB2LPENR;
    volatile uint32_t AHB3LPENR;
    volatile uint32_t RESERVED5;
    volatile uint32_t APB1LPENR;
    volatile uint32_t APB2LPENR;
    volatile uint32_t RESERVED6[2];
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
    volatile uint32_t RESERVED7[2];
    volatile uint32_t SSCGR;
    volatile uint32_t PLLI2SCFGR;
 } RCC_RegDef_t;
 //==========================================================

 //==========================================================
 // Structure for GPIO Registers
 typedef struct
 {
    volatile uint32_t IMR;
    volatile uint32_t EMR;
    volatile uint32_t RTSR;
    volatile uint32_t FTSR;
    volatile uint32_t SWIER;
    volatile uint32_t PR;
 } EXTI_RegDef_t;
 //==========================================================

 //==========================================================
 // Structure for SYSCFG Registers
 typedef struct
 {
    volatile uint32_t MEMRMP;
    volatile uint32_t PMC;
    volatile uint32_t EXTICR[4];
             uint32_t RESERVED1[2];
    volatile uint32_t CMPCR;
             uint32_t RESERVED2[2];
 } SYSCFG_RegDef_t;
 //==========================================================

// <------------------------------------------------------------------------------>
//==========================================================
// Structure for SPI Registers
typedef struct
{
   volatile uint32_t CR[2];
   volatile uint32_t SR;
   volatile uint32_t DR;
   volatile uint32_t CRCPR;
   volatile uint32_t RXCRCR;
   volatile uint32_t TXCRCR;
   volatile uint32_t I2SCFGR;
   volatile uint32_t I2SPR;
} SPI_RegDef_t;
//==========================================================

// <------------------------------------------------------------------------------>

//                      PERIPHERALs DEFINITION

/*  -Once we define structures for different peripherals, we need to connect them to their base addresses so we can access their registers easily.
    -To do this, we typecast the base address of the peripheral to a pointer of the structure type (like xxx_RegDef_t).
    -This way, we can use the structure to work with the peripheral's registers in a simple and clear manner.
*/

//==========================================================
// GPIO peripherals
#define GPIOA ((GPIO_RegDef_t *)GPIOA_BASEADDR)
#define GPIOB ((GPIO_RegDef_t *)GPIOB_BASEADDR)
#define GPIOC ((GPIO_RegDef_t *)GPIOC_BASEADDR)
#define GPIOD ((GPIO_RegDef_t *)GPIOD_BASEADDR)
#define GPIOE ((GPIO_RegDef_t *)GPIOE_BASEADDR)
#define GPIOF ((GPIO_RegDef_t *)GPIOF_BASEADDR)
#define GPIOG ((GPIO_RegDef_t *)GPIOG_BASEADDR)
#define GPIOH ((GPIO_RegDef_t *)GPIOH_BASEADDR)
#define GPIOI ((GPIO_RegDef_t *)GPIOI_BASEADDR)
//==========================================================

//==========================================================
// SPI peripherals
#define SPI1 ((SPI_RegDef_t *)SPI1_BASEADDR)
#define SPI2 ((SPI_RegDef_t *)SPI2_I2S2_BASEADDR)
#define SPI3 ((SPI_RegDef_t *)SPI3_I2S3_BASEADDR)
#define SPI4 ((SPI_RegDef_t *)SPI4_BASEADDR)
#define SPI5 ((SPI_RegDef_t *)SPI5_BASEADDR)
#define SPI6 ((SPI_RegDef_t *)SPI6_BASEADDR)
//==========================================================

//==========================================================
// RCC
#define RCC ((RCC_RegDef_t *)RCC_BASEADDR)
// EXTI
#define EXTI ((EXTI_RegDef_t *)EXTI_BASEADDR)
// SYSCFG
#define SYSCFG ((SYSCFG_RegDef_t *)SYSCFG_BASEADDR)
//==========================================================

// <------------------------------------------------------------------------------>

//                      CLOCK ENABLE MACROS FOR PERIPHERALS

/* -In this section, macros are defined to enable different peripherals.
   -This is done by enabling the bus (like AHB1, APB1, etc.) to which the peripheral is connected.
*/
//==========================================================
// Clock enable for GPIO peripherals
#define GPIOA_PCLK_EN() (RCC->AHB1ENR |= (1 << 0))
#define GPIOB_PCLK_EN() (RCC->AHB1ENR |= (1 << 1))
#define GPIOC_PCLK_EN() (RCC->AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN() (RCC->AHB1ENR |= (1 << 3))
#define GPIOE_PCLK_EN() (RCC->AHB1ENR |= (1 << 4))
#define GPIOF_PCLK_EN() (RCC->AHB1ENR |= (1 << 5))
#define GPIOG_PCLK_EN() (RCC->AHB1ENR |= (1 << 6))
#define GPIOH_PCLK_EN() (RCC->AHB1ENR |= (1 << 7))
#define GPIOI_PCLK_EN() (RCC->AHB1ENR |= (1 << 8))
//==========================================================

//==========================================================
// Clock disable for GPIO peripherals
#define GPIOA_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 4))
#define GPIOF_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 5))
#define GPIOG_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 6))
#define GPIOH_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 7))
#define GPIOI_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 8))
//==========================================================

//==========================================================
// Clock Enable for SPI peripherals
#define SPI1_PCLK_EN() (RCC->APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN() (RCC->APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN() (RCC->APB1ENR |= (1 << 15))
#define SPI4_PCLK_EN() (RCC->APB2ENR |= (1 << 13))
#define SPI5_PCLK_EN() (RCC->APB2ENR |= (1 << 20))
#define SPI6_PCLK_EN() (RCC->APB2ENR |= (1 << 21))
//==========================================================

//==========================================================
// Clock disable for SPI peripherals
#define SPI1_PCLK_DI() (RCC->APB2ENR &= ~(1 << 12))
#define SPI2_PCLK_DI() (RCC->APB1ENR &= ~(1 << 14))
#define SPI3_PCLK_DI() (RCC->APB1ENR &= ~(1 << 15))
#define SPI4_PCLK_DI() (RCC->APB2ENR &= ~(1 << 13))
#define SPI5_PCLK_DI() (RCC->APB2ENR &= ~(1 << 20))
#define SPI6_PCLK_DI() (RCC->APB2ENR &= ~(1 << 21))
//==========================================================

//==========================================================
// Clock enable & disable for SYSCFG
#define SYSCFG_PCLK_EN() (RCC->APB2ENR |= (1 << 14))
#define SYSCFG_PCLK_DI() (RCC->APB2ENR &= ~(1 << 14))
//==========================================================

//==========================================================
// Macro for returning the GPIO port code corresponding to the GPIO port
#define GPIO_BASEADDR_TO_PORTCODE(x) ((x == GPIOA) ? 0 : (x == GPIOB) ? 1 \
                                                     : (x == GPIOC)   ? 2 \
                                                     : (x == GPIOD)   ? 3 \
                                                     : (x == GPIOE)   ? 4 \
                                                     : (x == GPIOF)   ? 5 \
                                                     : (x == GPIOG)   ? 6 \
                                                     : (x == GPIOH)   ? 7 \
                                                     : (x == GPIOI)   ? 8 \
                                                                      :)
//==========================================================

//==========================================================
// Register Reset for GPIO peripherals
#define GPIOA_REG_RESET()           \
   do                               \
   {                                \
      (RCC->AHB1RSTR |= (1 << 0));  \
      (RCC->AHB1RSTR &= ~(1 << 0)); \
   } while (0)
#define GPIOB_REG_RESET()           \
   do                               \
   {                                \
      (RCC->AHB1RSTR |= (1 << 1));  \
      (RCC->AHB1RSTR &= ~(1 << 1)); \
   } while (0)
#define GPIOC_REG_RESET()           \
   do                               \
   {                                \
      (RCC->AHB1RSTR |= (1 << 2));  \
      (RCC->AHB1RSTR &= ~(1 << 2)); \
   } while (0)
#define GPIOD_REG_RESET()           \
   do                               \
   {                                \
      (RCC->AHB1RSTR |= (1 << 3));  \
      (RCC->AHB1RSTR &= ~(1 << 3)); \
   } while (0)
#define GPIOE_REG_RESET()           \
   do                               \
   {                                \
      (RCC->AHB1RSTR |= (1 << 4));  \
      (RCC->AHB1RSTR &= ~(1 << 4)); \
   } while (0)
#define GPIOF_REG_RESET()           \
   do                               \
   {                                \
      (RCC->AHB1RSTR |= (1 << 5));  \
      (RCC->AHB1RSTR &= ~(1 << 5)); \
   } while (0)
#define GPIOG_REG_RESET()           \
   do                               \
   {                                \
      (RCC->AHB1RSTR |= (1 << 6));  \
      (RCC->AHB1RSTR &= ~(1 << 6)); \
   } while (0)
#define GPIOH_REG_RESET()           \
   do                               \
   {                                \
      (RCC->AHB1RSTR |= (1 << 7));  \
      (RCC->AHB1RSTR &= ~(1 << 7)); \
   } while (0)
#define GPIOI_REG_RESET()           \
   do                               \
   {                                \
      (RCC->AHB1RSTR |= (1 << 8));  \
      (RCC->AHB1RSTR &= ~(1 << 8)); \
   } while (0)

//==========================================================

#endif /* INC_STM32F407XX_H_ */
