
# GPIO Programming Structr and Registers

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