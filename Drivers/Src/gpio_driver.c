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

