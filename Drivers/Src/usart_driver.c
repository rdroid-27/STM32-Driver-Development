#include "usart_driver.h"

/**************************************************************
 * @fn                  USART_PeriClockControl
 * @brief               Enables or disables the peripheral clock for the given USART port
 * @param[in] pUSARTx   Pointer to USART Peripheral Register
 * @param[in] ENorDI    ENABLE or DISABLE macro to turn clock on or off
 * @retval    None
 **************************************************************/
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

/**************************************************************
 * @fn                  USART_PeripheralControl
 * @brief               Enables or Disables the USART peripheral
 * @param[in] pUSARTx   Pointer to USART Peripheral Register
 * @param[in] ENorDI    ENABLE or DISABLE macro to turn peripheral on or off
 * @retval    None
 **************************************************************/
void USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t EnorDi)
{
    pUSARTx->CR1 = EnorDi ? (pUSARTx->CR1 | UE) : (pUSARTx->CR1 & ~UE);
}

/**************************************************************
 * @fn                      USART_Init
 * @brief                   Initialize the UART peripheral with user settings.
 * @param[in] pUSARTHandle  Pointer to the USART handle structure with config settings
 * @retval                  None
 * @note                    Call USART_PeriClockControl() before this to enable the clock.
 **************************************************************/
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
        tempreg |= RE;
    }
    else if (pUSARTHandle->USART_Config.USART_Mode == USART_MODE_ONLY_TX)
    {
        // Enable the Transmitter bit field
        tempreg |= TE;
    }
    else if (pUSARTHandle->USART_Config.USART_Mode == USART_MODE_TXRX)
    {
        // Enable the both Transmitter and Receiver bit fields
        tempreg |= (RE | TE);
    }

    // Configure the Word length configuration item
    tempreg |= pUSARTHandle->USART_Config.USART_WordLength << M;

    // Configuration of parity control bit fields
    if (pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_EN_EVEN)
    {
        // Enable the parity control
        tempreg |= (1 << PCE);
    }
    else if (pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_EN_ODD)
    {
        // Enable the parity control
        tempreg |= (1 << PCE);

        // Enable ODD parity
        tempreg |= (1 << PS);
    }

    // Program the CR1 register
    pUSARTHandle->pUSARTx->CR1 = tempreg;

    /******************************** Configuration of CR2******************************************/
    tempreg = 0;

    // Configure the number of stop bits inserted during USART frame transmission
    tempreg |= pUSARTHandle->USART_Config.USART_NoOfStopBits << STOP;

    // Program the CR2 register
    pUSARTHandle->pUSARTx->CR2 = tempreg;

    /******************************** Configuration of CR3******************************************/
    tempreg = 0;

    // Configuration of USART hardware flow control
    if (pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS)
    {
        // Enable CTS flow control
        tempreg |= (1 << CTSE);
    }
    else if (pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_RTS)
    {
        // Enable RTS flow control
        tempreg |= (1 << RTSE);
    }
    else if (pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS_RTS)
    {
        // Enable both CTS and RTS Flow control
        tempreg |= ((1 << CTSE) | (1 << RTSE));
    }

    pUSARTHandle->pUSARTx->CR3 = tempreg;
}

/*********************************************************************
 * @fn      		    USART_SetBaudRate
 * @brief               Calculate and Set the Baud Rate
 * @param[in] pUSARTx   Pointer to USART Peripheral Register
 * @param[in] ENorDI    Baud Rate user want to set
 * @retval              None
 **************************************************************/
void USART_SetBaudRate(USART_RegDef_t *pUSARTx, uint32_t BaudRate)
{

    // Variable to hold the APB clock
    uint32_t PCLKx;

    uint32_t usartdiv;

    // variables to hold Mantissa and Fraction values
    uint32_t M_part, F_part;

    uint32_t tempreg = 0;

    // Get the value of APB bus clock in to the variable PCLKx
    if (pUSARTx == USART1)
    {
        // USART1 is hanging on APB2 bus
        PCLKx = RCC_GetPCLK2Value();
    }
    else
    {
        PCLKx = RCC_GetPCLK1Value();
    }

    usartdiv = ((25 * PCLKx) / (2 * BaudRate));

    // Calculate the Mantissa part
    M_part = usartdiv / 100;

    // Place the Mantissa part in appropriate bit position
    tempreg |= DIV_Mantissa(M_part);

    // Extract the fraction part
    F_part = (usartdiv - (usartdiv * 100));

    // Calculate the final fractional
    F_part = (((F_part * 100) + 50) / 100) & ((uint8_t)0x07);

    // Place the fractional part in appropriate bit position
    tempreg |= DIV_Fraction(F_part);

    // copy the value of tempreg in to BRR register
    pUSARTx->BRR = tempreg;
}

/**
 * @fn                          USART_SendData
 * @brief                       Send data over USART
 * @param[in] pUSARTHandle      Pointer to the USART handle structure with config settings
 * @param[in] pTxBuffer         Pointer to the Transmission Buffer
 * @param[in] Len               Length of data to be transmitted
 * @return                      Void
 */
void USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len)
{

    uint16_t *pdata;
    // Loop over until "Len" number of bytes are transferred
    for (uint32_t i = 0; i < Len; i++)
    {
        // Wait until TXE flag is set in the SR
        while (!USART_GetFlagStatus(pUSARTHandle->pUSARTx, TXE))
            ;

        // This is 9bit data transfer
        if (pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
        {
            pUSARTHandle->pUSARTx->DR = (*(uint16_t *)pTxBuffer & (uint16_t)0x01FF);

            // check for USART_ParityControl
            if (pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
            {
                // No parity, 9bits of user data will be sent
                pTxBuffer += 2;
            }
            else
            {
                // Parity bit is used, 8bits of user data will be sent
                pTxBuffer++;
            }
        }
        else
        {
            // This is 8bit data transfer
            pUSARTHandle->pUSARTx->DR = (*pTxBuffer & (uint8_t)0xFF);
            pTxBuffer++;
        }
    }

    // Wait till TC flag is set in the SR
    while (!USART_GetFlagStatus(pUSARTHandle->pUSARTx, TC))
        ;
}

/*********************************************************************
 * @fn                          USART_ReceiveData
 * @brief                       Recieve data over USART
 * @param[in] pUSARTHandle      Pointer to the USART handle structure with config settings
 * @param[in] pRxBuffer         Pointer to the Reciever Buffer
 * @param[in] Len               Length of data to be Recieved
 * @return                      Void
 */
void USART_ReceiveData(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len)
{
    // Loop over until "Len" number of bytes are transferred
    for (uint32_t i = 0; i < Len; i++)
    {
        // Wait until RXNE flag is set in the SR
        while (!USART_GetFlagStatus(pUSARTHandle->pUSARTx, RXNE))
            ;

        // Check the USART_WordLength to decide whether we are going to receive 9bit of data in a frame or 8 bit
        if (pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
        {
            // We are going to receive 9bit data in a frame

            // check are we using USART_ParityControl control or not
            if (pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
            {
                // No parity is used, all 9bits will be of user data
                // Read only first 9 bits. Mask the DR with 0x01FF
                *((uint16_t *)pRxBuffer) = (pUSARTHandle->pUSARTx->DR & (uint16_t)(0x01FF));

                // Now increment the pRxBuffer two times
                pRxBuffer += 2;
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
            // Check are we using USART_ParityControl control or not
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

/*********************************************************************
 * @fn      		  - USART_SendDataWithIT
 * @brief             -
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 * @return            -
 */
uint8_t USART_SendDataIT(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len)
{
    uint8_t txstate = pUSARTHandle->USART_Config.USART_Mode;

    if (txstate != USART_BUSY_IN_TX)
    {
        pUSARTHandle->TxLen = Len;
        pUSARTHandle->pTxBuffer = pTxBuffer;
        pUSARTHandle->TxBusyState = USART_BUSY_IN_TX;

        // Implement the code to enable interrupt for TXE
        pUSARTHandle->pUSARTx->CR1 |= (1 << TXEIE);

        // Implement the code to enable interrupt for TC
        pUSARTHandle->pUSARTx->CR1 |= (1 << TCIE);
    }

    return txstate;
}

/*********************************************************************
 * @fn      		  - USART_ReceiveDataIT
 * @brief             -
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 * @return            -
 */
uint8_t USART_ReceiveDataIT(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len)
{
    uint8_t rxstate = pUSARTHandle->RxBusyState;

    if (rxstate != USART_BUSY_IN_RX)
    {
        pUSARTHandle->RxLen = Len;
        pUSARTHandle->pRxBuffer = pRxBuffer;
        pUSARTHandle->RxBusyState = USART_BUSY_IN_RX;

        // Implement the code to enable interrupt for RXNE
        pUSARTHandle->pUSARTx->CR1 |= (1 << RXNEIE);
    }

    return rxstate;
}

/*********************************************************************
 * @fn                          USART_GetFlagStatus
 * @brief                       Get the Flag status from USART_SR Register
 * @param[in] pUSARTx           Pointer to USART Register Definition
 * @param[in] StatusFlagName    Flag name to be checked
 * @return                      uint8 value
 */
uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx, uint8_t StatusFlagName)
{
    if (pUSARTx->SR & StatusFlagName)
    {
        return SET;
    }

    return RESET;
}

/*********************************************************************
 * @fn                          USART_ClearFlag
 * @brief                       Clear the Flag status from USART_SR Register
 * @param[in] pUSARTx           Pointer to USART Peripheral Register
 * @param[in] StatusFlagName    Flag name to be checked
 * @return                      Void
 */
void USART_ClearFlag(USART_RegDef_t *pUSARTx, uint16_t StatusFlagName)
{
    pUSARTx->SR &= ~(StatusFlagName);
}