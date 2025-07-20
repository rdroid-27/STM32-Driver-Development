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
    GPIO_BUTTON.pGPIOX = GPIOB;
    GPIO_BUTTON.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_12;
    GPIO_BUTTON.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
    GPIO_BUTTON.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IP;
    GPIO_BUTTON.GPIO_PinConfig.GPIO_PinCNF = GPIO_CNF_INPUT_PUPD;

    GPIO_PeriClockControl(GPIOB, ENABLE);
    GPIO_Init(&GPIO_BUTTON);

    while (1)
    {
        // 1. Glow the LED when Button is Pressed
        if (!(GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_12)))
        {
            GPIO_WriteToOutputPin(GPIOC, GPIO_PIN_13, RESET);
        }
        else
        {
            GPIO_WriteToOutputPin(GPIOC, GPIO_PIN_13, SET);
        }

        // 2. Toggle LED when Button is pressed
        // LED glows only when there is no debounce
        if (check_debounce(GPIOB, GPIO_PIN_12))
        {
            GPIO_ToggleOutputPin(GPIOC, GPIO_PIN_13);
            // Wait for button to be released
            while (!GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_12))
                ;
        }
    }

    return 0;
}