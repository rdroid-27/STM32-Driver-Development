/*
 * gpio_driver.h
 *
 *  Created on: Jul 7, 2025
 *      Author: GANDALF
 */

#ifndef INC_GPIO_DRIVER_H_
#define INC_GPIO_DRIVER_H_

#include "stm32f103xx.h"

// GPIO Pin Number
#define GPIO_PIN_0                  0
#define GPIO_PIN_1                  1
#define GPIO_PIN_2                  2
#define GPIO_PIN_3                  3
#define GPIO_PIN_4                  4
#define GPIO_PIN_5                  5
#define GPIO_PIN_6                  6
#define GPIO_PIN_7                  7
#define GPIO_PIN_8                  8
#define GPIO_PIN_9                  9
#define GPIO_PIN_10                 10
#define GPIO_PIN_11                 11
#define GPIO_PIN_12                 12
#define GPIO_PIN_13                 13
#define GPIO_PIN_14                 14
#define GPIO_PIN_15                 15

// AFIO Port Codes
#define PA                          0
#define PB                          1
#define PC                          2

// Mode options (MODE[1:0])
#define GPIO_MODE_IP                0  // Input mode
#define GPIO_MODE_OP_10MHZ          1  // Output, 10 MHz
#define GPIO_MODE_OP_2MHZ           2  // Output, 2 MHz
#define GPIO_MODE_OP_50MHZ          3  // Output, 50 MHz
#define GPIO_MODE_IT_RT             4  // Interrupt - Rising Trigger
#define GPIO_MODE_IT_FT             5  // Interrupt - Falling Trigger
#define GPIO_MODE_IT_RFT            6  // Interrupt - Rising Falling Trigger

// CNF options (CNF[1:0] for MODE = 00 → Input)
#define GPIO_CNF_ANALOG             0
#define GPIO_CNF_FLOATING           1
#define GPIO_CNF_INPUT_PUPD         2

// CNF options (for output modes)
#define GPIO_CNF_GP_PUSH_PULL       0
#define GPIO_CNF_GP_OPEN_DRAIN      1
#define GPIO_CNF_AF_PUSH_PULL       2
#define GPIO_CNF_AF_OPEN_DRAIN      3

// Pull configuration (used with CNF = 0b10)
#define GPIO_PIN_PU                 1
#define GPIO_PIN_PD                 0

// GPIO Pin Configuration Structure
typedef struct
{
    volatile uint8_t GPIO_PinNumber; // Pin number (0–15)
    volatile uint8_t GPIO_PinMode;   // Input, Output, AF, Analog (with speed or pull info) or Interrupt Mode.
    volatile uint8_t GPIO_PinCNF;    // CNF bits: configuration (PP, OD, floating, etc.)
    volatile uint8_t GPIO_PinPuPdControl;
} GPIO_PinConfig_t;

typedef struct
{
    GPIO_RegDef_t *pGPIOX;
    GPIO_PinConfig_t GPIO_PinConfig;
} GPIO_Handle_t;

/**************************************************************
 *                     GPIO Driver API Prototypes             *
 **************************************************************/

// Enables or disables peripheral clock for the GPIO port
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t ENorDI);

// Initializes a GPIO pin based on the configuration structure
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);

// Resets all registers of the GPIO port
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

// Reads the entire input port (all 16 bits)
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);

// Reads the logic level (0 or 1) from a specific input pin
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

// Writes a 16-bit value to the entire output port
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t value);

// Sets or clears a specific output pin
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t value);

// Toggles the current output state of a specific pin
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

// Configures NVIC interrupt settings for the given GPIO pin
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t ENorDI);

// 
void GPIO_IRQPriorityConfig(uint8_t IRQPriority,uint8_t IRQNumber);

// Handles the interrupt for a given GPIO pin
void GPIO_IRQHandling(uint8_t PinNumber);

#endif /* INC_GPIO_DRIVER_H_ */
