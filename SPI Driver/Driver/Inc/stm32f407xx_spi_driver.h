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
} GPIO_Handle_t;

// <------------------------------------------------------------------------------>
 
 #endif /* INC_STM32F407XX_SPI_DRIVER_H_ */
 