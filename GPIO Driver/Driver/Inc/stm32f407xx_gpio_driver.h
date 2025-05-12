/*
 * stm32f407xx_gpio_driver.h
 *
 *  Created on: Apr 24, 2025
 *      Author: GANDALF
 */

#ifndef INC_STM32F407XX_GPIO_DRIVER_H_
#define INC_STM32F407XX_GPIO_DRIVER_H_

#include "stm32f407xx.h"

// Macros for GPIO Pin possible modes
#define GPIO_MODE_IN 0
#define GPIO_MODE_OUT 1
#define GPIO_MODE_ALTFN 2
#define GPIO_MODE_ANALOG 3
#define GPIO_MODE_IT_RT 4
#define GPIO_MODE_IT_FT 5
#define GPIO_MODE_IT_RFT 6

// Macros for GPIO Pin Output types
#define GPIO_OP_TYPE_PP 0
#define GPIO_OP_TYPE_OD 1

// Macros for GPIO Pin possible Output speed modes
#define GPIO_OP_SPEED_LOW 0
#define GPIO_OP_SPEED_MED 1
#define GPIO_OP_SPEED_HIGH 2
#define GPIO_OP_SPEED_VERYHIGH 3

// Macros for GPIO Pin possible Pull-up/Pull-down modes
#define GPIO_NO_PUPD 0
#define GPIO_PU 1
#define GPIO_PD 2

// Macros for GPIO Pin Numbers
#define GPIO_PIN_0 0
#define GPIO_PIN_1 1
#define GPIO_PIN_2 2
#define GPIO_PIN_3 3
#define GPIO_PIN_4 4
#define GPIO_PIN_5 5
#define GPIO_PIN_6 6
#define GPIO_PIN_7 7
#define GPIO_PIN_8 8
#define GPIO_PIN_9 9
#define GPIO_PIN_10 10
#define GPIO_PIN_11 11
#define GPIO_PIN_12 12
#define GPIO_PIN_13 13
#define GPIO_PIN_14 14
#define GPIO_PIN_15 15

// <------------------------------------------------------------------------------>

// Pin Configuration Structure for GPIO Pin
/* This structure is used to hold all the settings needed to configure a single GPIO pin. Instead of setting each value separately, we put all the configurations into one structure for easy management and cleaner code.
 */
typedef struct
{
    uint8_t GPIO_PinNumber;
    uint8_t GPIO_PinMode;
    uint8_t GPIO_PinSpeed;
    uint8_t GPIO_PinPuPdControl;
    uint8_t GPIO_PinOPType;
    uint8_t GPIO_PinAltFuncMode;
} GPIO_PinConfig_t;

// <------------------------------------------------------------------------------>

// Handle Structure for a GPIO Pin
/* This structure is used to group everything needed to initialize and use a GPIO pin.
 */
typedef struct
{
    GPIO_RegDef_t *pGPIOx;
    GPIO_PinConfig_t GPIO_PinConfig;
} GPIO_Handle_t;

// <------------------------------------------------------------------------------>

// Driver APIs

void GPIO_Init(GPIO_Handle_t *pGPIO_Handle);
void GPIO_Deinit(GPIO_RegDef_t *pGPIOx);

void GPIO_PeriClkControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);

uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t pinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t pinNumber, uint8_t value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t pinNumber);

void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);

void GPIO_IRQHandling(uint8_t pinNumber);

#endif /* INC_STM32F407XX_GPIO_DRIVER_H_ */
