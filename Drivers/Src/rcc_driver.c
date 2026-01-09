#include "rcc_driver.h"

uint16_t AHB_PRESCALAR[8] = {2, 4, 8, 16, 64, 128, 256, 512};
uint16_t APB1_PRESCALAR[4] = {2, 4, 8, 16};

uint32_t RCC_GetPCLK1Value(void)
{
    uint32_t pclk1, sysclk;
    uint8_t clk_src = ((RCC->CFGR >> 2) & 0x3);
    uint8_t temp, ahbp, apb1p;
    if (clk_src == 0)
        sysclk = 16000000;
    else if (clk_src == 1)
        sysclk = 8000000;
    else if (clk_src == 2)
        ;
    // PLL based clock source
    else
        // Clock not allowed
        return 0;

    // For AHB
    temp = ((RCC->CFGR >> 4) & 0xF);
    if (temp < 8)
        ahbp = 1;
    else
        ahbp = AHB_PRESCALAR[temp - 8];

    // For APB
    temp = ((RCC->CFGR >> 10) & 0x7);
    if (temp < 8)
        apb1p = 1;
    else
        apb1p = APB1_PRESCALAR[temp - 4];

    pclk1 = (sysclk / ahbp) / apb1p;

    return pclk1;
}

uint32_t RCC_GetPCLK2Value(void)
{
    uint32_t pclk1, sysclk;
    uint8_t clk_src = ((RCC->CFGR >> 2) & 0x3);
    uint8_t temp, ahbp, apb1p;
    if (clk_src == 0)
        sysclk = 16000000;
    else if (clk_src == 1)
        sysclk = 8000000;
    else if (clk_src == 2)
        ;
    // PLL based clock source
    else
        // Clock not allowed
        return 0;

    // For AHB
    temp = ((RCC->CFGR >> 4) & 0xF);
    if (temp < 8)
        ahbp = 1;
    else
        ahbp = AHB_PRESCALAR[temp - 8];

    // For APB
    temp = ((RCC->CFGR >> 10) & 0x7);
    if (temp < 8)
        apb1p = 1;
    else
        apb1p = APB1_PRESCALAR[temp - 4];

    pclk1 = (sysclk / ahbp) / apb1p;

    return pclk1;
}