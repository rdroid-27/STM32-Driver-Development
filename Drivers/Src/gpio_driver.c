/*
 * gpio_driver.c
 *
 *  Created on: Jul 8, 2025
 *      Author: GANDALF
 */

#include "gpio_driver.h"

/**************************************************************
 * @function  GPIO_PeriClockControl
 * @brief     Enables or disables peripheral clock for a given GPIO port
 * @param[in] pGPIOx - Base address of the GPIO peripheral (GPIOA, GPIOB, etc.)
 * @param[in] ENorDI - Enable or Disable macro:
 *                     - ENALBE (1) to enable clock
 *                     - DISABLE (0) to disable clock
 * @retval    None
 *
 * @note      The RCC peripheral clock for the GPIO must be enabled
 *            before any read/write/config operations can be performed.
 **************************************************************/
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t ENorDI)
{
    if (ENorDI == ENALBE)
    {
        if (pGPIOx == GPIOA)
            GPIOA_CLK_EN();
        else if (pGPIOx == GPIOB)
            GPIOB_CLK_EN();
        else if (pGPIOx == GPIOC)
            GPIOC_CLK_EN();
        else if (pGPIOx == GPIOD)
            GPIOD_CLK_EN();
        else if (pGPIOx == GPIOE)
            GPIOE_CLK_EN();
    }
    else
    {
        if (pGPIOx == GPIOA)
            GPIOA_CLK_DI();
        else if (pGPIOx == GPIOB)
            GPIOB_CLK_DI();
        else if (pGPIOx == GPIOC)
            GPIOC_CLK_DI();
        else if (pGPIOx == GPIOD)
            GPIOD_CLK_DI();
        else if (pGPIOx == GPIOE)
            GPIOE_CLK_DI();
    }
}

void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{

    uint8_t pin_number = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber;

    // Select CRL or CRH based on pin number
    volatile uint32_t *config_reg;
    if (pin_number <= 7)
        config_reg = &pGPIOHandle->pGPIOX->CRL;
    else
        config_reg = &pGPIOHandle->pGPIOX->CRH;

    uint8_t shift = (pin_number % 8) * 4;

    // Clear previous mode + cnf bits
    *config_reg &= ~(0xF << shift);

    // Set mode and cnf
    uint32_t MODE = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode & 0x3);
    uint32_t CNF = (pGPIOHandle->GPIO_PinConfig.GPIO_PinCNF & 0x3);

    *config_reg |= ((MODE | (CNF << 2)) << shift);

    if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IP && pGPIOHandle->GPIO_PinConfig.GPIO_PinCNF == IP_PU_PD)
    {
        if (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl == GPIO_PIN_PU)
            pGPIOHandle->pGPIOX->ODR |= (1 << pin_number); // pull-up
        else
            pGPIOHandle->pGPIOX->ODR &= ~(1 << pin_number); // pull-down
    }
}