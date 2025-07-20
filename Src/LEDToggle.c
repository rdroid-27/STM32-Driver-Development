#include "gpio_driver.h"

void delay()
{
    for (uint32_t i = 0; i < 1000000; i++)
        ;
}

int main()
{
    GPIO_Handle_t GPIO_LED;

    GPIO_LED.pGPIOX = GPIOC;
    GPIO_LED.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_13;
    GPIO_LED.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OP_10MHZ;
    GPIO_LED.GPIO_PinConfig.GPIO_PinCNF = GPIO_CNF_GP_PUSH_PULL;

    GPIO_PeriClockControl(GPIOC, ENABLE);
    GPIO_Init(&GPIO_LED);

    while (1)
    {
        GPIO_ToggleOutputPin(GPIOC, GPIO_PIN_13);
        delay();
    }

    return 0;
}