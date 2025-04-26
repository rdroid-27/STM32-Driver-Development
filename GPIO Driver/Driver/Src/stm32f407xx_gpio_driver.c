#include "stm32f407xx_gpio_driver.h"

// Enable The GPIO port by enable the corresponding peripheral clock associated with it and vice versa for disabling the GPIO port.
void GPIO_PeriClkControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
    if (EnorDi == ENABLE)
    {
        if (pGPIOx == GPIOA)
        {
            GPIOA_PCLK_EN();
        }
        else if (pGPIOx == GPIOB)
        {
            GPIOB_PCLK_EN();
        }
        else if (pGPIOx == GPIOC)
        {
            GPIOC_PCLK_EN();
        }
        else if (pGPIOx == GPIOD)
        {
            GPIOD_PCLK_EN();
        }
        else if (pGPIOx == GPIOE)
        {
            GPIOE_PCLK_EN();
        }
        else if (pGPIOx == GPIOF)
        {
            GPIOF_PCLK_EN();
        }
        else if (pGPIOx == GPIOG)
        {
            GPIOG_PCLK_EN();
        }
        else if (pGPIOx == GPIOH)
        {
            GPIOH_PCLK_EN();
        }
        else if (pGPIOx == GPIOI)
        {
            GPIOI_PCLK_EN();
        }
    }
    else if (EnorDi == DISABLE)
    {
        if (pGPIOx == GPIOA)
        {
            GPIOA_PCLK_DI();
        }
        else if (pGPIOx == GPIOB)
        {
            GPIOB_PCLK_DI();
        }
        else if (pGPIOx == GPIOC)
        {
            GPIOC_PCLK_DI();
        }
        else if (pGPIOx == GPIOD)
        {
            GPIOD_PCLK_DI();
        }
        else if (pGPIOx == GPIOE)
        {
            GPIOE_PCLK_DI();
        }
        else if (pGPIOx == GPIOF)
        {
            GPIOF_PCLK_DI();
        }
        else if (pGPIOx == GPIOG)
        {
            GPIOG_PCLK_DI();
        }
        else if (pGPIOx == GPIOH)
        {
            GPIOH_PCLK_DI();
        }
        else if (pGPIOx == GPIOI)
        {
            GPIOI_PCLK_DI();
        }
    }
}

// Initialize the GPIO port
void GPIO_Init(GPIO_Handle_t *pGPIO_Handle)
{
    // Pin Mode
    if (pGPIO_Handle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
    {
        pGPIO_Handle->pGPIOx->MODER &= ~(0x3 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);
        pGPIO_Handle->pGPIOx->MODER |= pGPIO_Handle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);
    }
    else
    {
    }

    // Pin Speed
    pGPIO_Handle->pGPIOx->OSPEEDR &= ~(0x3 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);
    pGPIO_Handle->pGPIOx->OSPEEDR |= pGPIO_Handle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);

    // PU/PD Settings
    pGPIO_Handle->pGPIOx->PUPDR &= ~(0x3 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);
    pGPIO_Handle->pGPIOx->PUPDR |= pGPIO_Handle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);

    // Output Type
    pGPIO_Handle->pGPIOx->OTYPER &= ~(0x1 << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber);
    pGPIO_Handle->pGPIOx->OTYPER |= pGPIO_Handle->GPIO_PinConfig.GPIO_PinOPType << pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber;

    // Alternate Functionality Mode
    if (pGPIO_Handle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
    {
        uint8_t temp1, temp2;
        temp1 = pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber / 8;
        temp2 = pGPIO_Handle->GPIO_PinConfig.GPIO_PinNumber % 8;
        pGPIO_Handle->pGPIOx->AFR[temp1] &= (0xF << (4 * temp2));
        pGPIO_Handle->pGPIOx->AFR[temp1] |= pGPIO_Handle->GPIO_PinConfig.GPIO_PinAltFuncMode << (4 * temp2);
    }
}

// Deinitialization of GPIO port
void GPIO_Deinit(GPIO_RegDef_t *pGPIOx)
{
    if (pGPIOx == GPIOA)
    {
        GPIOA_REG_RESET();
    }
    else if (pGPIOx == GPIOB)
    {
        GPIOB_REG_RESET();
    }
    else if (pGPIOx == GPIOC)
    {
        GPIOC_REG_RESET();
    }
    else if (pGPIOx == GPIOD)
    {
        GPIOD_REG_RESET();
    }
    else if (pGPIOx == GPIOE)
    {
        GPIOE_REG_RESET();
    }
    else if (pGPIOx == GPIOF)
    {
        GPIOF_REG_RESET();
    }
    else if (pGPIOx == GPIOG)
    {
        GPIOG_REG_RESET();
    }
    else if (pGPIOx == GPIOH)
    {
        GPIOH_REG_RESET();
    }
    else if (pGPIOx == GPIOI)
    {
        GPIOI_REG_RESET();
    }
}

// Read from Input Pin
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t pinNumber)
{
    return (uint8_t)((pGPIOx->IDR >> pinNumber) & 0x00000001);
}

// Read from Input Port
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
    return (uint16_t)(pGPIOx->IDR);
}

// Write to Output Pin
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t pinNumber, uint8_t value)
{
    if (value == GPIO_PIN_SET)
        pGPIOx->ODR |= (1 << pinNumber);
    else
        pGPIOx->ODR &= ~(1 << pinNumber);
}

// Write to Output Port
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t value)
{
    pGPIOx->ODR = value;
}

// Toggle GPIO pin
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t pinNumber)
{
    pGPIOx->ODR ^= (1 << pinNumber);
}