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

/*********************************************************************
 * @fn      		  - USART_SendData
 * @brief             -
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 * @return            -
 * @Note              - Resolve all the TODOs
 */
void USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len)
{

    uint16_t *pdata;
    // Loop over until "Len" number of bytes are transferred
    for (uint32_t i = 0; i < Len; i++)
    {
        // Implement the code to wait until TXE flag is set in the SR
        while (!USART_GetFlagStatus(pUSARTHandle->pUSARTx, USART_SR_TXE))
            ;

        // Check the USART_WordLength item for 9BIT or 8BIT in a frame
        if (pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
        {
            // if 9BIT, load the DR with 2bytes masking the bits other than first 9 bits
            pdata = (uint16_t *)pTxBuffer;
            pUSARTHandle->pUSARTx->DR = (*pdata & (uint16_t)0x01FF);

            // check for USART_ParityControl
            if (pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
            {
                // No parity is used in this transfer. so, 9bits of user data will be sent
                pTxBuffer++;
                pTxBuffer++;
            }
            else
            {
                // Parity bit is used in this transfer . so , 8bits of user data will be sent
                // The 9th bit will be replaced by parity bit by the hardware
                pTxBuffer++;
            }
        }
        else
        {
            // This is 8bit data transfer
            pUSARTHandle->pUSARTx->DR = (*pTxBuffer & (uint8_t)0xFF);

            // Implement the code to increment the buffer address
            pTxBuffer++;
        }
    }

    // Implement the code to wait till TC flag is set in the SR
    while (!USART_GetFlagStatus(pUSARTHandle->pUSARTx, USART_SR_TC))
        ;
}

/*********************************************************************
 * @fn      		  - USART_ReceiveData
 * @brief             -
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 * @return            -
 * @Note              -
 */
void USART_ReceiveData(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len)
{
    // Loop over until "Len" number of bytes are transferred
    for (uint32_t i = 0; i < Len; i++)
    {
        // Implement the code to wait until RXNE flag is set in the SR
        while (!USART_GetFlagStatus(pUSARTHandle->pUSARTx, USART_SR_RXNE))
            ;

        // Check the USART_WordLength to decide whether we are going to receive 9bit of data in a frame or 8 bit
        if (pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
        {
            // We are going to receive 9bit data in a frame

            // check are we using USART_ParityControl control or not
            if (pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
            {
                // No parity is used. so, all 9bits will be of user data

                // read only first 9 bits. so, mask the DR with 0x01FF
                *((uint16_t *)pRxBuffer) = (pUSARTHandle->pUSARTx->DR & (uint16_t)(0x01FF));

                // Now increment the pRxBuffer two times
                pRxBuffer++;
                pRxBuffer++;
            }
            else
            {
                // Parity is used, so, 8bits will be of user data and 1 bit is parity
                *pRxBuffer = (pUSARTHandle->pUSARTx->DR & (uint8_t)0xFF);

                // Increment the pRxBuffer
                pRxBuffer++;
            }
        }
        else
        {
            // We are going to receive 8bit data in a frame

            // check are we using USART_ParityControl control or not
            if (pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
            {
                // No parity is used , so all 8bits will be of user data

                // read 8 bits from DR
                *pRxBuffer = pUSARTHandle->pUSARTx->DR;
            }

            else
            {
                // Parity is used, so , 7 bits will be of user data and 1 bit is parity

                // read only 7 bits , hence mask the DR with 0X7F
                *pRxBuffer = (uint8_t)pUSARTHandle->pUSARTx->DR & 0x7F;
            }

            // increment the pRxBuffer
            pRxBuffer++;
        }
    }
}

// /*********************************************************************
//  * @fn      		  - USART_SendDataWithIT
//  *
//  * @brief             -
//  *
//  * @param[in]         -
//  * @param[in]         -
//  * @param[in]         -
//  *
//  * @return            -
//  *
//  * @Note              - Resolve all the TODOs

//  */
// uint8_t USART_SendDataIT(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len)
// {
//     uint8_t txstate = pUSARTHandle->TODO;

//     if (txstate != USART_BUSY_IN_TX)
//     {
//         pUSARTHandle->TODO = Len;
//         pUSARTHandle->pTxBuffer = TODO;
//         pUSARTHandle->TxBusyState = TODO;

//         // Implement the code to enable interrupt for TXE
//         TODO

//             // Implement the code to enable interrupt for TC
//             TODO
//     }

//     return txstate;
// }

// /*********************************************************************
//  * @fn      		  - USART_ReceiveDataIT
//  *
//  * @brief             -
//  *
//  * @param[in]         -
//  * @param[in]         -
//  * @param[in]         -
//  *
//  * @return            -
//  *
//  * @Note              - Resolve all the TODOs

//  */
// uint8_t USART_ReceiveDataIT(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len)
// {
//     uint8_t rxstate = pUSARTHandle->TODO;

//     if (rxstate != TODO)
//     {
//         pUSARTHandle->RxLen = Len;
//         pUSARTHandle->pRxBuffer = TODO;
//         pUSARTHandle->RxBusyState = TODO;

//         // Implement the code to enable interrupt for RXNE
//         TODO
//     }

//     return rxstate;
// }

uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx, uint32_t FlagName)
{
    uint8_t Status = (pUSARTx->SR >> FlagName) & (0x01);
    return Status;
}