# GPIO Driver

The GPIO driver provides a register-level interface for configuring and controlling the General Purpose Input/Output (GPIO) peripherals of the **STM32F103xx** microcontroller.

It supports:

- GPIO pin configuration
- Digital input and output
- Alternate Function configuration
- Pull-up/Pull-down configuration
- External Interrupt (EXTI) configuration
- NVIC interrupt management

---

# File Overview

| File | Description |
|------|-------------|
| `gpio.h` | GPIO and AFIO register definitions, peripheral mappings, and clock control macros. |
| `gpio_driver.h` | GPIO configuration macros, data structures, and public API declarations. |
| `gpio_driver.c` | Implementation of the GPIO driver APIs. |

---

# gpio.h

This file defines the register layouts of the GPIO and AFIO peripherals and provides macros for accessing peripheral instances and controlling peripheral clocks.

## GPIO Register Structure

Each GPIO peripheral has the following register layout.

```c
typedef struct
{
    volatile uint32_t CRL;
    volatile uint32_t CRH;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t BRR;
    volatile uint32_t LCKR;

} GPIO_RegDef_t;
```

### Register Description

| Register | Description |
|----------|-------------|
| **CRL** | Configuration register for pins 0–7 |
| **CRH** | Configuration register for pins 8–15 |
| **IDR** | Input Data Register |
| **ODR** | Output Data Register |
| **BSRR** | Bit Set/Reset Register (atomic bit operations) |
| **BRR** | Bit Reset Register |
| **LCKR** | Port Configuration Lock Register |

The same structure is mapped to every GPIO peripheral base address.

```c
GPIOA
GPIOB
GPIOC
GPIOD
GPIOE
GPIOF
GPIOG
```

---

## AFIO Register Structure

The Alternate Function I/O (AFIO) peripheral controls GPIO remapping and EXTI source selection.

```c
typedef struct
{
    volatile uint32_t EVCR;
    volatile uint32_t MAPR;
    volatile uint32_t EXTICR[4];
    volatile uint32_t MAPR2;

} AFIO_RegDef_t;
```

### Register Description

| Register | Description |
|----------|-------------|
| EVCR | Event Control Register |
| MAPR | Alternate Function Remap Register |
| EXTICR1–4 | External Interrupt Configuration Registers |
| MAPR2 | Additional Remap Register |

---

## Peripheral Mapping

The register structures are mapped to their peripheral base addresses.

```c
GPIOA
GPIOB
GPIOC
GPIOD
GPIOE
GPIOF
GPIOG

AFIO
```

These macros provide direct access to the peripheral registers.

---

## Peripheral Clock Control

Every GPIO peripheral must have its clock enabled before it can be configured.

Clock enable macros:

```c
GPIOA_CLK_EN()
GPIOB_CLK_EN()
GPIOC_CLK_EN()
GPIOD_CLK_EN()
GPIOE_CLK_EN()

AFIO_CLK_EN()
```

Clock disable macros:

```c
GPIOA_CLK_DI()
GPIOB_CLK_DI()
GPIOC_CLK_DI()
GPIOD_CLK_DI()
GPIOE_CLK_DI()

AFIO_CLK_DI()
```

---

# gpio_driver.h

This file provides all user-facing GPIO configuration macros, data structures, and API declarations.

---

## GPIO Pin Macros

GPIO pins are identified using predefined macros.

```c
GPIO_PIN_0
GPIO_PIN_1
...
GPIO_PIN_15
```

---

## AFIO Port Codes

These values are used while configuring EXTI lines.

| Port | Code |
|------|------|
| GPIOA | PA |
| GPIOB | PB |
| GPIOC | PC |

---

## GPIO Modes

The driver supports the following operating modes.

| Macro | Description |
|-------|-------------|
| `GPIO_MODE_IP` | Input mode |
| `GPIO_MODE_OP_10MHZ` | Output mode (10 MHz) |
| `GPIO_MODE_OP_2MHZ` | Output mode (2 MHz) |
| `GPIO_MODE_OP_50MHZ` | Output mode (50 MHz) |
| `GPIO_MODE_IT_RT` | Interrupt on Rising Edge |
| `GPIO_MODE_IT_FT` | Interrupt on Falling Edge |
| `GPIO_MODE_IT_RFT` | Interrupt on Rising and Falling Edge |

---

## GPIO Configuration (CNF)

### Input Configuration

| Macro | Description |
|-------|-------------|
| `GPIO_CNF_ANALOG` | Analog Input |
| `GPIO_CNF_FLOATING` | Floating Input |
| `GPIO_CNF_INPUT_PUPD` | Pull-Up/Pull-Down Input |

### Output Configuration

| Macro | Description |
|-------|-------------|
| `GPIO_CNF_GP_PUSH_PULL` | General Purpose Push-Pull |
| `GPIO_CNF_GP_OPEN_DRAIN` | General Purpose Open-Drain |
| `GPIO_CNF_AF_PUSH_PULL` | Alternate Function Push-Pull |
| `GPIO_CNF_AF_OPEN_DRAIN` | Alternate Function Open-Drain |

---

## Pull Configuration

| Macro | Description |
|-------|-------------|
| `GPIO_PIN_PU` | Internal Pull-Up |
| `GPIO_PIN_PD` | Internal Pull-Down |

---

# GPIO_PinConfig_t

Stores the complete configuration for a GPIO pin.

```c
typedef struct
{
    uint8_t GPIO_PinNumber;
    uint8_t GPIO_PinMode;
    uint8_t GPIO_PinCNF;
    uint8_t GPIO_PinPuPdControl;

} GPIO_PinConfig_t;
```

### Members

| Member | Description |
|---------|-------------|
| `GPIO_PinNumber` | GPIO pin (0–15) |
| `GPIO_PinMode` | Pin operating mode |
| `GPIO_PinCNF` | Pin configuration |
| `GPIO_PinPuPdControl` | Pull-up/Pull-down selection |

---

# GPIO_Handle_t

Combines the GPIO peripheral and its pin configuration.

```c
typedef struct
{
    GPIO_RegDef_t *pGPIOX;
    GPIO_PinConfig_t GPIO_PinConfig;

} GPIO_Handle_t;
```

This structure is passed to the initialization function.

---

# Driver APIs

## GPIO_PeriClockControl()

```c
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx,
                           uint8_t ENorDI);
```

Enables or disables the clock for a GPIO peripheral through the RCC APB2 peripheral clock register.

---

## GPIO_Init()

```c
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
```

Initializes a GPIO pin according to the user configuration.

Depending on the selected mode, this function:

- Enables the GPIO peripheral clock
- Configures CRL or CRH
- Configures MODE and CNF bits
- Configures internal pull-up/pull-down
- Configures AFIO EXTI source mapping (interrupt modes)
- Configures EXTI trigger selection
- Enables the EXTI interrupt mask

---

## GPIO_DeInit()

```c
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);
```

Resets all registers of the selected GPIO peripheral using the RCC APB2 reset register.

---

## GPIO_ReadFromInputPort()

```c
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
```

Reads the complete 16-bit Input Data Register (IDR).

Returns the logic level of all GPIO pins.

---

## GPIO_ReadFromInputPin()

```c
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx,
                              uint8_t PinNumber);
```

Reads the logic level of a single GPIO pin.

Return values:

- `0` → LOW
- `1` → HIGH

---

## GPIO_WriteToOutputPort()

```c
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx,
                            uint16_t Value);
```

Writes a 16-bit value directly to the Output Data Register (ODR).

---

## GPIO_WriteToOutputPin()

```c
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx,
                           uint8_t PinNumber,
                           uint8_t Value);
```

Sets or clears an individual GPIO output pin using the BSRR register, providing atomic bit operations without affecting other pins.

---

## GPIO_ToggleOutputPin()

```c
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx,
                          uint8_t PinNumber);
```

Toggles the current output state of the specified GPIO pin.

---

## GPIO_IRQInterruptConfig()

```c
void GPIO_IRQInterruptConfig(uint8_t IRQNumber,
                             uint8_t ENorDI);
```

Enables or disables the corresponding interrupt in the NVIC using the ISER and ICER registers.

---

## GPIO_IRQPriorityConfig()

```c
void GPIO_IRQPriorityConfig(uint32_t IRQPriority,
                            uint8_t IRQNumber);
```

Assigns a priority to the specified interrupt by programming the NVIC Interrupt Priority Registers (IPR).

Lower priority values indicate higher interrupt priority.

---

## GPIO_IRQHandling()

```c
void GPIO_IRQHandling(uint8_t PinNumber);
```

Clears the pending interrupt flag in the EXTI Pending Register (PR) after an interrupt has been serviced.

---

# Typical Initialization Flow

```text
Enable GPIO Clock
        │
        ▼
Configure GPIO_Handle_t
        │
        ▼
Call GPIO_Init()
        │
        ▼
Read/Write GPIO
        │
        ▼
(Optional)
Configure NVIC Interrupt
        │
        ▼
Handle EXTI Interrupt
        │
        ▼
Clear Pending Flag
```

---

# Notes

- GPIO clocks must be enabled before accessing GPIO registers.
- Interrupt modes automatically configure the AFIO and EXTI peripherals.
- Individual output pins are modified atomically using the `BSRR` register.
- `GPIO_IRQHandling()` should be called from the corresponding EXTI interrupt service routine to clear the pending interrupt flag.