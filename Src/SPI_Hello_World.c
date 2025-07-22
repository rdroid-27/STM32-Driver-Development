/*
 * SPI_Hello_World.c
 *
 *  Created on: Jul 22, 2025
 *      Author: GANDALF
 */

#include <string.h>
#include "stm32f103xx.h"

/*
 *       SPI1
 *   PA7 -> MOSI
 *   PA6 -> MISO
 *   PA5 -> SCK
 *   PA4 -> NSS
 *   SPI1_REMAP = 0
 */

void SPI1_GPIOInits(void)
{
    AFIO_CLK_EN();
    AFIO->MAPR &= ~(1 << 0);

    GPIO_Handle_t SPIPins;
    SPIPins.pGPIOX = GPIOA;
    SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OP_10MHZ;
    SPIPins.GPIO_PinConfig.GPIO_PinCNF = GPIO_CNF_AF_PUSH_PULL;

    // SCK
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_5;
    GPIO_Init(&SPIPins);

    // MOSI
    SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_7;
    GPIO_Init(&SPIPins);

    // // MISO
    // SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_6;
    // SPIPins.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IP;
    // SPIPins.GPIO_PinConfig.GPIO_PinCNF = GPIO_CNF_FLOATING;
    // GPIO_Init(&SPIPins);

    // // NSS
    // SPIPins.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_4;
    // GPIO_Init(&SPIPins);
}

void SPI1_Inits(void)
{
    SPI_Handle_t SPI1Handle;

    SPI1Handle.pSPIX = SPI1;
    SPI1Handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
    SPI1Handle.SPIConfig.SPI_DeviceMode = SPI_MODE_MASTER;
    SPI1Handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV2;
    SPI1Handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
    SPI1Handle.SPIConfig.SPI_DFF = SPI_DFF_8;
    SPI1Handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
    SPI1Handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
    SPI1Handle.SPIConfig.SPI_SSM = SPI_SSM_EN;

    SPI_Init(&SPI1Handle);
}

int main()
{
    char user_data[] = "Hello World";

    SPI1_GPIOInits();
    SPI1_Inits();

    // Make NSS high internally
    SPI_SSIConfig(SPI1, SET);

    // Enable the SPI
    SPI_PeripheralControl(SPI1, ENABLE);

    // Send data
    SPI_SendData(SPI1, (uint8_t *)user_data, strlen(user_data));

    // Disbale the SPI
    SPI_PeripheralControl(SPI1, DISABLE);

    while (1)
        ;

    return 0;
}