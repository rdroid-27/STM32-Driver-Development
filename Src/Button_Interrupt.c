#include "gpio_driver.h"

void delay()
{
    for (uint32_t i = 0; i < 100000; i++)
        ;
}

uint8_t check_debounce(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
    if (GPIO_ReadFromInputPin(pGPIOx, PinNumber))
    {
        delay();
        if (GPIO_ReadFromInputPin(pGPIOx, PinNumber))
        {
            return 1;
        }
    }
    else
    {
        return 0;
    }
}

int main()
{
    GPIO_Handle_t GPIO_LED;
    GPIO_Handle_t GPIO_BUTTON;

    // Set GPIO for LED.
    GPIO_LED.pGPIOX = GPIOC;
    GPIO_LED.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_13;
    GPIO_LED.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OP_10MHZ;
    GPIO_LED.GPIO_PinConfig.GPIO_PinCNF = GPIO_CNF_GP_PUSH_PULL;

    GPIO_PeriClockControl(GPIOC, ENABLE);
    GPIO_Init(&GPIO_LED);

    // Set GPIO for Button
    GPIO_BUTTON.pGPIOX = GPIOA;
    GPIO_BUTTON.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_0;
    GPIO_BUTTON.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
    GPIO_BUTTON.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
    GPIO_BUTTON.GPIO_PinConfig.GPIO_PinCNF = GPIO_CNF_INPUT_PUPD;

    GPIO_PeriClockControl(GPIOA, ENABLE);
    GPIO_Init(&GPIO_BUTTON);

    // IRQ Configurations
    GPIO_IRQPriorityConfig(IRQ_NO_EXTI0, 0);
    GPIO_IRQInterruptConfig(IRQ_NO_EXTI0, ENABLE);
    while (1)
        ;
}

void EXTI0_IRQHandler(void)
{
    delay();
    GPIO_IRQHandling(GPIO_PIN_0);
    GPIO_ToggleOutputPin(GPIOC, GPIO_PIN_13);
}