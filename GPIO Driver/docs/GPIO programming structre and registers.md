[⬅️ Back to Introduction to GPIO](./Introduction%20to%20GPIO.md)<br>
[⬅️ Back to README](../README.md)

# GPIO Programming Structre and Registers

## Introduction

This documentation provides the information regarding the programming structure and about the GPIO registers for STM32F4XX MCU board.

## GPIO Programming Structure
- Generally GPIO ports have following registers that can be configured as per the user applications:
		- Port Direction (Mode) Register: modes like input, output, analog, etc.
		- Port Speed Register
		- Port Output Type Register
		- Port Input Data Register: used to read data from GPIO port.
		- Port Output Data Register: used to write data to GPIO port.
		- Other Port Configuration Registers.
- In STM32, all the GPIO ports are connected to processor over AHB1 Bus.
- The STM32F407VG has 9 GPIO ports, hence it supports 144 GPIO pins.
- But the Discovery Development board, we have only 5 GPIO ports i.e. 80 GPIO pins.

### GPIO Registers
- GPIO port mode register (GPIOx_MODER)
	-  32-bit Register
	- 2 bits are used to define mode of a single pin, hence it is 32-bits long.
	- Each pin has 4 modes: Input (Reset State) (00), General purpose Output (01), Alternate Functionality (10) and Analog Mode (11).
	- In the Output Mode, the input driver is also ON so it also possible to read data from Input Buffer even if it is in Output Mode.
	- In alternate funcinality mode, the output goes directly to the assigned peripherals output and not to the output buffer register. Where as the input goes to both the input buffer register as well as assigned peripherals input.
- GPIO port output type register (GPIOx_OTYPER)
	- 32-bit Register but upper 16 bits (16-31) are reserved.
	- Single bit is used to define the output type of a pin i.e Output push-pull (Reset State) (0) or Output open-drain (1).
	- GPIO port output speed register (GPIOx_OSPEEDR)
	- 32-bit register
	- We can configure how quick the GPIO transitions from High to Low or Low to High or basically the slew rate of the pin.
	- 2 bits are used to define speed of a single pin.
	- Each pin has 4 modes: Low Speed (00), Medium Speed (01), High Speed (10) and Very High Speed (11).
- GPIO port pull-up/pull-down register (GPIOx_PUPDR)
	- 32-bit register
	- 2 bits are used for a single pin and each pin has 4 modes: No pull-up and pull-down (00), Pull-up(01), Pull-down (10) and Reserved (11).
- GPIO port input data register (GPIOx_IDR)
	- 32-bit Register but upper 16 bits (16-31) are reserved.
	- We can only read data from this register.
- GPIO port output data register (GPIOx_ODR)
	- 32-bit Register but upper 16 bits (16-31) are reserved.
	- These bits can we read and written by programmer.
- GPIO alternate function low register (GPIOx_AFRL) and GPIO alternate function high register (GPIOx_AFRH)
	- 32-bit Registers
	- Each pin has 16 Alternate Functionality modes, hence 4 bits of the register represent a single pin.
	- Therefore using this alternate function low register we can configure lower pins of the  GPIO i.e. from Pin 0 to Pin 7.
	- Using this alternate function high register we can configure higher pins of the  GPIO i.e. from Pin 8 to Pin 15.
- RCC AHB1 peripheral clock enable register (RCC_AHB1ENR)
	- This 32 bit register has bit 0 to bit 8 assigned for enabling GPIO ports A to I repectively.
	- '1' means the clock will be enabled for that GPIO port and '0' means disable.

NOTE: These values depends on the vendor providing MCU, hence all the details should be checked in the DATA SHEET of MCU.

[⬅️ Back to README](../README.md)
