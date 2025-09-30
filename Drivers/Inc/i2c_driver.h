#include "stm32f103xx.h"

// I2C Macros
#define I2C_SCL_SPEED_SM 100000
#define I2C_SCL_SPEED_FM4K 400000
#define I2C_SCL_SPEED_FM2K 200000

#define I2C_ACK_ENABLE 1
#define I2C_ACK_DISABLE 0

#define I2C_DUTY_2 0
#define I2C_DUTY_16_9 1

#define I2C_CR1_START 8
#define I2C_CR1_STOP 9

#define FLAG_SET 1
#define FLAG_RESET 0

// I2C SR1 Bits

#define I2C_SR1_SB 0
#define I2C_SR1_ADDR 1
#define I2C_SR1_BTF 2
#define I2C_SR1_ADD103 3
#define I2C_SR1_STOPF 4
#define I2C_SR1_RxNE 6
#define I2C_SR1_TxE 7
#define I2C_SR1_BERR 8
#define I2C_SR1_ARLO 9
#define I2C_SR1_AF 10
#define I2C_SR1_OVR 11
#define I2C_SR1_PECERR 12
#define I2C_SR1_TIMEOUT 14
#define I2C_SR1_SMBALERT 15

// I2C Status Flags
#define I2C_FLAG_SB (1 << I2C_SR1_SB)
#define I2C_FLAG_ADDR (1 << I2C_SR1_ADDR)
#define I2C_FLAG_BTF (1 << I2C_SR1_BTF)
#define I2C_FLAG_ADD10 (1 << I2C_SR1_ADD10)
#define I2C_FLAG_STOPF (1 << I2C_SR1_STOPF)
#define I2C_FLAG_RxNE (1 << I2C_SR1_RxNE)
#define I2C_FLAG_TxE (1 << I2C_SR1_TxE)
#define I2C_FLAG_BERR (1 << I2C_SR1_BERR)
#define I2C_FLAG_ARLO (1 << I2C_SR1_ARLO)
#define I2C_FLAG_AF (1 << I2C_SR1_AF)
#define I2C_FLAG_OVR (1 << I2C_SR1_OVR)
#define I2C_FLAG_PECERR (1 << I2C_SR1_PECERR)
#define I2C_FLAG_TIMEOUT (1 << I2C_SR1_TIMEOUT)
#define I2C_FLAG_SMBALERT (1 << I2C_SR1_SMBALERT)

// I2C Configuration Structure
typedef struct
{
    volatile uint32_t I2C_SCLSpeed;     // Device mode: Master (1) or Slave (0)
    volatile uint8_t I2C_DeviceAddress; // Bus configuration: Full-duplex, Half-duplex, or Simplex RX-only
    volatile uint8_t I2C_ACKControl;    // Serial clock speed (baud rate control)
    volatile uint8_t I2C_FmDutyCycle;   // Data frame format: 8-bit or 16-bit
} I2C_Config_t;

typedef struct
{
    I2C_RegDef_t *pI2Cx;
    I2C_Config_t I2CConfig;
} I2C_Handle_t;

/**************************************************************
 *                     I2C Driver API Prototypes             *
 **************************************************************/

// Enables or disables the peripheral clock for the given I2C port
void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t ENorDI);

// Initializes the I2C peripheral with the specified configuration
void I2C_Init(I2C_Handle_t *pI2CHandle);

// Enable or disable I2C
void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);

// Send and Recieve Data
void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddr);

// // Enable or disable SSI (Internal Slave Select)
// void I2C_SSIConfig(I2C_RegDef_t *pI2Cx, uint8_t EnorDi);

// // Resets the I2C peripheral registers to their default state
// void I2C_DeInit(I2C_RegDef_t *pI2Cx);

// // Sends data using the I2C peripheral in blocking mode
// void I2C_SendData(I2C_RegDef_t *pI2Cx, uint8_t *pTxBuffer, uint32_t len);

// // Receives data using the I2C peripheral in blocking mode
// void I2C_RecieveData(I2C_RegDef_t *pI2Cx, uint8_t *pRxBuffer, uint32_t len);

// // Enables or disables the interrupt for the given I2C IRQ number
// void I2C_IRQInterruptConfig(uint8_t IRQNumber, uint8_t ENorDI);

// // Sets the priority of the given I2C interrupt number
// void I2C_IRQPriorityConfig(uint32_t IRQPriority, uint8_t IRQNumber);

// // Handles the I2C interrupt and clears the flags
// void I2C_IRQHandling(I2C_Handle_t *pI2CHandle);