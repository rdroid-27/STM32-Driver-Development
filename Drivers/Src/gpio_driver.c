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
 *                     - ENABLE (1) to enable clock
 *                     - DISABLE (0) to disable clock
 * @retval    None
 *
 * @note      The RCC peripheral clock for the GPIO must be enabled
 *            before any read/write/config operations can be performed.
 **************************************************************/
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t ENorDI)
{
    if (ENorDI == ENABLE)
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

/**************************************************************
 * @function    GPIO_Init
 * @brief       Configures the mode and configuration for a GPIO pin
 *
 * @param[in]   pGPIOHandle - Pointer to GPIO handle structure that contains:
 *                - GPIO port base address (pGPIOx)
 *                - GPIO pin configuration structure (GPIO_PinConfig)
 *
 * @note
 *   - For STM32F103 (Blue Pill), each GPIO pin is configured via
 *     4 bits in CRL (pins 0–7) or CRH (pins 8–15):
 *       [1:0] MODE: Output speed or input mode
 *       [3:2] CNF : Configuration type (floating, pull-up/down, AF, etc.)
 *   - For input mode with pull-up or pull-down (CNF = 0b10), the
 *     ODR register must also be written to set pull type.
 *
 * @retval      None
 **************************************************************/
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
    // Enable the clock for peripheral
    GPIO_PeriClockControl(pGPIOHandle->pGPIOX, ENABLE);

    uint8_t pin_number = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber;

    if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_OP_50MHZ)
    {
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

        if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IP && pGPIOHandle->GPIO_PinConfig.GPIO_PinCNF == GPIO_CNF_INPUT_PUPD)
        {
            if (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl == GPIO_PIN_PU)
                pGPIOHandle->pGPIOX->ODR |= (1 << pin_number); // pull-up
            else
                pGPIOHandle->pGPIOX->ODR &= ~(1 << pin_number); // pull-down
        }
    }
    else
    {
        uint8_t index = (pin_number) / 4;
        uint8_t shift_index = ((pin_number) % 4) * 4;
        uint8_t shift = (pin_number % 8) * 4;

        // Step 0: Configure CRL/CRH for input with CNF = 10 (PUPD)
        volatile uint32_t *config_reg;
        if (pin_number <= 7)
            config_reg = &pGPIOHandle->pGPIOX->CRL;
        else
            config_reg = &pGPIOHandle->pGPIOX->CRH;

        *config_reg &= ~(0xF << shift); // Clear 4 bits

        uint32_t MODE = GPIO_MODE_IP; // MODE = 0b00
        uint32_t CNF = pGPIOHandle->GPIO_PinConfig.GPIO_PinCNF & 0x3;

        *config_reg |= ((MODE | (CNF << 2)) << shift);

        // Step 1: Configure pull-up or pull-down
        if (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl == GPIO_PIN_PU)
            pGPIOHandle->pGPIOX->ODR |= (1 << pin_number); // pull-up
        else
            pGPIOHandle->pGPIOX->ODR &= ~(1 << pin_number); // pull-down

        // Step 2: Enable AFIO and configure EXTICR
        AFIO_CLK_EN();
        AFIO->EXTICR[index] &= ~(0xF << shift_index);

        if (pGPIOHandle->pGPIOX == GPIOA)
            AFIO->EXTICR[index] |= (PA << shift_index);
        else if (pGPIOHandle->pGPIOX == GPIOB)
            AFIO->EXTICR[index] |= (PB << shift_index);
        else if (pGPIOHandle->pGPIOX == GPIOC)
            AFIO->EXTICR[index] |= (PC << shift_index);

        // Step 3: Configure edge trigger
        if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
        {
            EXTI->RTSR |= (1 << pin_number);
            EXTI->FTSR &= ~(1 << pin_number);
        }
        else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
        {
            EXTI->FTSR |= (1 << pin_number);
            EXTI->RTSR &= ~(1 << pin_number);
        }
        else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
        {
            EXTI->RTSR |= (1 << pin_number);
            EXTI->FTSR |= (1 << pin_number);
        }

        // Step 4: Enable interrupt mask
        EXTI->IMR |= (1 << pin_number);
    }
}

/**************************************************************
 * @function    GPIO_DeInit
 * @brief       Resets all registers of the given GPIO port
 *
 * @param[in]   pGPIOX - Base address of GPIO port (e.g., GPIOA, GPIOB...)
 *
 * @note
 *   - This uses RCC->APB2RSTR to reset the GPIO peripheral.
 *   - The reset bit is set and then cleared immediately after,
 *     to avoid holding the GPIO in reset state.
 *
 * @retval      None
 **************************************************************/
void GPIO_DeInit(GPIO_RegDef_t *pGPIOX)
{
    if (pGPIOX == GPIOA)
    {
        RCC->APB2RSTR |= (1 << 2);
        RCC->APB2RSTR &= ~(1 << 2);
    }
    else if (pGPIOX == GPIOB)
    {
        RCC->APB2RSTR |= (1 << 3);
        RCC->APB2RSTR &= ~(1 << 3);
    }
    else if (pGPIOX == GPIOC)
    {
        RCC->APB2RSTR |= (1 << 4);
        RCC->APB2RSTR &= ~(1 << 4);
    }
    else if (pGPIOX == GPIOD)
    {
        RCC->APB2RSTR |= (1 << 5);
        RCC->APB2RSTR &= ~(1 << 5);
    }
    else if (pGPIOX == GPIOE)
    {
        RCC->APB2RSTR |= (1 << 6);
        RCC->APB2RSTR &= ~(1 << 6);
    }
    else if (pGPIOX == GPIOF)
    {
        RCC->APB2RSTR |= (1 << 7);
        RCC->APB2RSTR &= ~(1 << 7);
    }
    else if (pGPIOX == GPIOG)
    {
        RCC->APB2RSTR |= (1 << 8);
        RCC->APB2RSTR &= ~(1 << 8);
    }
}

/**************************************************************
 * @function    GPIO_ReadFromInputPort
 * @brief       Reads the entire 16-bit input port value
 *
 * @param[in]   pGPIOx - Pointer to the GPIO peripheral (GPIOA, GPIOB, etc.)
 *
 * @retval      16-bit value representing all 16 input pins (IDR[15:0])
 *
 * @note
 *   - Each bit corresponds to one pin (0: low, 1: high)
 *   - Useful for reading all pin states at once
 **************************************************************/
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx)
{
    return (uint16_t)((pGPIOx->IDR) & 0xFFFF);
}

/**************************************************************
 * @function    GPIO_ReadFromInputPin
 * @brief       Reads the logic level from a specific GPIO input pin
 *
 * @param[in]   pGPIOx     - Pointer to GPIO peripheral (e.g., GPIOA)
 * @param[in]   PinNumber  - GPIO pin number (0 to 15)
 *
 * @retval      uint8_t    - 0 if pin is LOW, 1 if pin is HIGH
 *
 * @note
 *   - This reads the bit in IDR corresponding to the pin number.
 *   - Return is normalized to 0 or 1.
 **************************************************************/
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
    return (uint8_t)(((pGPIOx->IDR) >> PinNumber) & 0x1);
}

/**************************************************************
 * @function    GPIO_WriteToOutputPort
 * @brief       Writes a 16-bit value to the entire GPIO output port
 *
 * @param[in]   pGPIOx - Pointer to the GPIO peripheral (GPIOA, GPIOB, etc.)
 * @param[in]   value  - 16-bit value to write to output pins (ODR)
 *
 * @note
 *   - Each bit of `value` corresponds to one output pin:
 *       Bit 0 → Pin 0, Bit 1 → Pin 1, ..., Bit 15 → Pin 15
 *   - This directly overwrites the entire ODR register.
 **************************************************************/
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t value)
{
    pGPIOx->ODR = value;
}

/**************************************************************
 * @function    GPIO_WriteToOutputPin
 * @brief       Writes logic HIGH or LOW to a specific GPIO output pin
 *
 * @param[in]   pGPIOx     - Pointer to GPIO peripheral (e.g., GPIOA)
 * @param[in]   PinNumber  - GPIO pin number (0 to 15)
 * @param[in]   value      - Logic level to write (0 = LOW, 1 = HIGH)
 *
 * @retval      None
 *
 * @note
 *   - Only the selected pin is modified; other output pins remain unchanged.
 *   - This modifies the ODR (Output Data Register) directly.
 **************************************************************/
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t value)
{
    if (value == 1)
    {
        // Set the bit
        pGPIOx->BSRR |= (1 << PinNumber);
    }
    else
    {
        // Clear the bit
        pGPIOx->BSRR |= (1 << (PinNumber + 16));
    }
}

/**************************************************************
 * @function    GPIO_ToggleOutputPin
 * @brief       Toggles the logic level of a specific GPIO output pin
 *
 * @param[in]   pGPIOx     - Pointer to GPIO peripheral (e.g., GPIOA)
 * @param[in]   PinNumber  - GPIO pin number (0 to 15)
 *
 * @retval      None
 *
 * @note
 *   - Uses XOR to toggle the bit in the ODR register.
 **************************************************************/
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
    pGPIOx->ODR ^= (1 << PinNumber);
}

/**************************************************************
 * @function    GPIO_IRQInterruptConfig
 * @brief       Enables or disables a specific IRQ number in the NVIC
 *
 * @param[in]   IRQNumber  - IRQ number to enable/disable (0–95)
 * @param[in]   ENorDI     - ENABLE or DISABLE macro
 *
 * @retval      None
 *
 * @note
 *   - Uses NVIC ISER (for enable) and ICER (for disable) registers.
 *   - IRQs 0–31 → ISER0/ICER0, 32–63 → ISER1/ICER1, 64–95 → ISER2/ICER2.
 **************************************************************/
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t ENorDI)
{
    if (ENorDI == ENABLE)
    {
        if (IRQNumber <= 31)
        {
            *NVIC_ISER0 |= (1 << IRQNumber);
        }
        else if (IRQNumber > 31 && IRQNumber < 64)
        {
            *NVIC_ISER1 |= (1 << (IRQNumber % 32));
        }
        else if (IRQNumber >= 64 && IRQNumber < 96)
        {
            *NVIC_ISER2 |= (1 << (IRQNumber % 64));
        }
    }
    else
    {
        if (IRQNumber <= 31)
        {
            *NVIC_ICER0 |= (1 << IRQNumber);
        }
        else if (IRQNumber > 31 && IRQNumber < 64)
        {
            *NVIC_ICER1 |= (1 << (IRQNumber % 32));
        }
        else if (IRQNumber >= 64 && IRQNumber < 96)
        {
            *NVIC_ICER2 |= (1 << (IRQNumber % 64));
        }
    }
}

/**************************************************************
 * @function    GPIO_IRQPriorityConfig
 * @brief       Configures the priority for a given IRQ number
 *
 * @param[in]   IRQPriority - Priority level (0–67, lower is higher priority)
 * @param[in]   IRQNumber   - IRQ number (0–95)
 *
 * @retval      None
 *
 * @note
 *   - Priority is written to the NVIC_IPR (Interrupt Priority Register).
 *   - Each IPR register holds priority for 4 IRQs, 8 bits per IRQ.
 *   - STM32 uses only upper 4 bits of each 8-bit priority field.
 **************************************************************/
void GPIO_IRQPriorityConfig(uint32_t IRQPriority, uint8_t IRQNumber)
{
    uint8_t iprx = IRQNumber / 4;
    uint8_t iprx_section = IRQNumber % 4;

    *(NVIC_IPR_BASEADDR + (iprx)) |= (IRQPriority << ((8 * iprx_section) + 4));
}

/**************************************************************
 * @function    GPIO_IRQHandling
 * @brief       Clears the pending interrupt flag for a GPIO EXTI line
 *
 * @param[in]   PinNumber  - GPIO pin number (0 to 15) linked to EXTI line
 *
 * @retval      None
 *
 * @note
 *   - Clears EXTI_PR register by writing '1' to the bit corresponding to the pin.
 *   - Always check if the pending bit is set before clearing.
 **************************************************************/
void GPIO_IRQHandling(uint8_t PinNumber)
{
    // Clear the bit for pin number in EXTI Pending Register
    if (EXTI->PR & (1 << PinNumber))
        EXTI->PR |= (1 << PinNumber);
}
