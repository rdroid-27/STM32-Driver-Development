/*
 * gpio_driver.h
 *
 *  Created on: Jul 7, 2025
 *      Author: GANDALF
 */

#ifndef INC_GPIO_DRIVER_H_
#define INC_GPIO_DRIVER_H_

#include "stm32f103xx.h"

#define GPIO_PIN_0                  0
#define GPIO_PIN_1                  1
#define GPIO_PIN_2                  2
#define GPIO_PIN_3                  3
#define GPIO_PIN_4                  4
#define GPIO_PIN_5                  5
#define GPIO_PIN_6                  6
#define GPIO_PIN_7                  7
             
#define GPIO_PIN_PU                 1
#define GPIO_PIN_PD                 0

#define GPIO_MODE_IP                0
#define GPIO_MODE_OP_10M            1
#define GPIO_MODE_OP_2M             2
#define GPIO_MODE_OP_50M            3

// GPIO Input Mode Options
#define ANALOG                      0
#define FLOATING_INPUT              1
#define IP_PU_PD                    2
#define RESERVED                    3
 
// GPIO Output Mode Options 
#define GPO_PP                      0
#define GPO_OD                      1
#define AFO_PP                      2
#define AFO_OD                      3
 
/*<! GPIO Pin Configuration Structure >*/
typedef struct
{
    volatile uint8_t GPIO_PinNumber; // Pin number (0–15)
    volatile uint8_t GPIO_PinMode;   // Input, Output, AF, Analog (with speed or pull info)
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
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t ENorDI);

// Handles the interrupt for a given GPIO pin
void GPIO_IRQHandling(uint8_t PinNumber);

#endif /* INC_GPIO_DRIVER_H_ */
