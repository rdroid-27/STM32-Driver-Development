#include "usart_driver.h"

/**
 * @brief Enables or disables the peripheral clock for the given USART port
 * @param[in] pUSARTx   Pointer to the USART peripheral base address (USART1, USART2, etc.)
 * @param[in] ENorDI  ENABLE or DISABLE macro to turn clock on or off
 */
void USART_PeriClockControl(USART_RegDef_t *pUSARTx, uint8_t ENorDI)
{
    if (ENorDI == ENABLE)
    {
        if (pUSARTx == USART1)
            USART1_CLK_EN();
        if (pUSARTx == USART2)
            USART2_CLK_EN();
        if (pUSARTx == USART3)
            USART3_CLK_EN();
        if (pUSARTx == UART4)
            USART3_CLK_EN();
        if (pUSARTx == UART5)
            USART3_CLK_EN();
    }
    else
    {
        if (pUSARTx == USART1)
            USART1_CLK_DI();
        if (pUSARTx == USART2)
            USART2_CLK_DI();
        if (pUSARTx == USART3)
            USART3_CLK_DI();
        if (pUSARTx == UART4)
            USART3_CLK_DI();
        if (pUSARTx == UART5)
            USART3_CLK_DI();
    }
}

/**
 * @brief Enables or Disables the USART peripheral
 * @param[in] pUSARTx   Pointer to the USART peripheral base address (USART1, USART2, etc.)
 * @param[in] ENorDI  ENABLE or DISABLE macro to turn peripheral on or off
 */
void USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t EnorDi)
{
    if (EnorDi == ENABLE)
    {
        pUSARTx->CR1 |= (1 << 13);
    }
    else
    {
        pUSARTx->CR1 &= ~(1 << 13);
    }
}

/**
 * @brief Initializes the USART peripheral with the specified configuration
 * @param[in] pUSARTHandle  Pointer to the USART handle structure with config settings
 * @note Call USART_PeriClockControl() before this to enable the clock.
 */
void USART_Init(USART_Handle_t *pUSARTHandle)
{
    // Temporary variable
    uint32_t tempreg = 0;
    // Enable clock for peripheral
    USART_PeriClockControl(pUSARTHandle->pUSARTx, ENABLE);

    // Enable USART Tx and Rx engines according to the USART_Mode configuration item
    if (pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_RX)
    {
        // Enable the Receiver bit field
        tempreg |= (1 << USART_CR1_RE);
    }
    else if (pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_TX)
    {
        // Enable the Transmitter bit field
        tempreg |= (1 << USART_CR1_TE);
    }
    else if (pUSARTHandle->USART_Config.USART_Mode == USART_MODE_TXRX)
    {
        // Enable the both Transmitter and Receiver bit fields
        tempreg |= ((1 << USART_CR1_RE) | (1 << USART_CR1_TE));
    }

    // Configure the Word length configuration item
    tempreg |= pUSARTHandle->USART_Config.USART_WordLength << USART_CR1_M;

    // Configuration of parity control bit fields
    if (pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_EN_EVEN)
    {
        // Enable the parity control
        tempreg |= (1 << USART_CR1_PCE);
    }
    else if (pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_EN_ODD)
    {
        // Enable the parity control
        tempreg |= (1 << USART_CR1_PCE);

        // Enable ODD parity
        tempreg |= (1 << USART_CR1_PS);
    }

    // Program the CR1 register
    pUSARTHandle->pUSARTx->CR1 = tempreg;

    /******************************** Configuration of CR2******************************************/
    tempreg = 0;

    // Configure the number of stop bits inserted during USART frame transmission
    tempreg |= pUSARTHandle->USART_Config.USART_NoOfStopBits << USART_CR2_STOP;

    // Program the CR2 register
    pUSARTHandle->pUSARTx->CR2 = tempreg;

    /******************************** Configuration of CR3******************************************/
    tempreg = 0;

    // Configuration of USART hardware flow control
    if (pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS)
    {
        // Enable CTS flow control
        tempreg |= (1 << USART_CR3_CTSE);
    }
    else if (pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_RTS)
    {
        // Enable RTS flow control
        tempreg |= (1 << USART_CR3_RTSE);
    }
    else if (pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS_RTS)
    {
        // Enable both CTS and RTS Flow control
        tempreg |= ((1 << USART_CR3_CTSE) | (1 << USART_CR3_RTSE));
    }

    pUSARTHandle->pUSARTx->CR3 = tempreg;

    /******************************** Configuration of BRR(Baudrate register)******************************************/

    // Implement the code to configure the baud rate
    // We will cover this in the lecture. No action required here
}