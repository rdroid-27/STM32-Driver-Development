#include "stm32f103xx.h"

// User Configurable Items
typedef struct
{
    volatile uint8_t USART_Mode;
    volatile uint32_t USART_Baud;
    volatile uint8_t USART_NoOfStopBits;
    volatile uint8_t USART_WordLength;
    volatile uint8_t USART_ParityControl;
    volatile uint8_t USART_HWFlowControl;
} USART_Config_t;

// Handle Structure for USART
typedef struct
{
    USART_RegDef_t *pUSARTx;
    USART_Config_t USART_Config;
    uint8_t *pTxBuffer;
    uint8_t *pRxBuffer;
    uint32_t TxLen;
    uint32_t RxLen;
    uint8_t TxBusyState;
    uint8_t RxBusyState;
} USART_Handle_t;

// USART_Mode
#define USART_MODE_ONLY_TX 0
#define USART_MODE_ONLY_RX 1
#define USART_MODE_TXRX 2

// USART_Baud
#define USART_STD_BAUD_1200 1200
#define USART_STD_BAUD_2400 400
#define USART_STD_BAUD_9600 9600
#define USART_STD_BAUD_19200 19200
#define USART_STD_BAUD_38400 38400
#define USART_STD_BAUD_57600 57600
#define USART_STD_BAUD_115200 115200
#define USART_STD_BAUD_230400 230400
#define USART_STD_BAUD_460800 460800
#define USART_STD_BAUD_921600 921600
#define USART_STD_BAUD_2M 2000000
#define SUART_STD_BAUD_3M 3000000

// USART_NoOfStopBits
#define USART_STOPBITS_1 0
#define USART_STOPBITS_0_5 1
#define USART_STOPBITS_2 2
#define USART_STOPBITS_1_5 3

// USART_WordLength
#define USART_WORDLEN_8BITS 0
#define USART_WORDLEN_9BITS 1

// USART_ParityControl
#define USART_PARITY_EN_ODD 2
#define USART_PARITY_EN_EVEN 1
#define USART_PARITY_DISABLE 0

// USART_HWFlowControl
#define USART_HW_FLOW_CTRL_NONE 0
#define USART_HW_FLOW_CTRL_CTS 1
#define USART_HW_FLOW_CTRL_RTS 2
#define USART_HW_FLOW_CTRL_CTS_RTS 3

#define RXNE (1 << 5)
#define TC (1 << 6)
#define TXE (1 << 7)

#define RE (1 << 2)
#define TE (1 << 3)
#define RXNEIE (1 << 5)
#define TCIE (1 << 6)
#define TXEIE (1 << 7)
#define PS (1 << 9)
#define PCE (1 << 10)
#define M (1 << 12)

#define STOP (1 << 12)

#define RTSE (1 << 8)
#define CTSE (1 << 9)

#define DIV_Mantissa(x) (x << 4)
#define DIV_Fraction(y) (y << 0)

// Application states
#define USART_BUSY_IN_RX 1
#define USART_BUSY_IN_TX 2
#define USART_READY 0

#define USART_EVENT_TX_CMPLT 0
#define USART_EVENT_RX_CMPLT 1
#define USART_EVENT_IDLE 2
#define USART_EVENT_CTS 3
#define USART_EVENT_PE 4
#define USART_ERR_FE 5
#define USART_ERR_NE 6
#define USART_ERR_ORE 7

/**************************************************************
 *                     USART Driver API Prototypes             *
 **************************************************************/

/*
 * Peripheral Clock setup
 */
void USART_PeriClockControl(USART_RegDef_t *pUSARTx, uint8_t EnorDi);

/*
 * Init and De-init
 */
void USART_Init(USART_Handle_t *pUSARTHandle);
void USART_DeInit(USART_RegDef_t *pUSARTx);

/*
 * Data Send and Receive
 */
void USART_SendData(USART_RegDef_t *pUSARTx, uint8_t *pTxBuffer, uint32_t Len);
void USART_ReceiveData(USART_RegDef_t *pUSARTx, uint8_t *pRxBuffer, uint32_t Len);
uint8_t USART_SendDataIT(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len);
uint8_t USART_ReceiveDataIT(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len);

/*
 * IRQ Configuration and ISR handling
 */
void USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void USART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void USART_IRQHandling(USART_Handle_t *pHandle);

/*
 * Other Peripheral Control APIs
 */
void USART_PeripheralControl(USART_RegDef_t *pUSARTx, uint8_t EnOrDi);
uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx, uint32_t FlagName);
void USART_ClearFlag(USART_RegDef_t *pUSARTx, uint16_t StatusFlagName);

/*
 * Application callback
 */
void USART_ApplicationEventCallback(USART_Handle_t *pUSARTHandle, uint8_t AppEv);