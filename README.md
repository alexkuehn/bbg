#BBG
a small 8x8 LED Matrix eyecandy


## Purpose
This project displays some eyecandy on an 8x8 LED dotmatrix display with 32 brightness values.

## prequisites:
* ATMEGA8 controller (16MHz clock)
* serial connection (optional)
* 8x8 LED matrix
* AVR GCC 4.8 toolchain with avr-libc 1.8, Eclipse IDE
* Potentiometer on A/D as input

## Usage
After startup the freerunning standalone eyecandy patterns are selected by the Potentiometer input. The potentiometer range is divided in three coarse sections, where one of those patterns runs:

* builtin bitmap player 
* random pattern
* floating rectangle

Within these section the potentiometer adjusts the pattern speed.

If a serial connection is established, the system switches to slave mode, where a pattern can be uploaded and displayed. If the serial connection stops for a time longer than a second, the system switches back to standalone mode.

## Detailed Description
### Software
The software consists of the follwoing parts:
#### Virtual Framebuffer (virtfb)
The virtual framebuffer provides a backbuffered framebuffer with dimensions 8x8, where some basic graphical operations can be executed. After the patterns are painted, teh framebuffer can be updated, where the backbuffer is transferred to the real display

#### HAL
The HAL abstracts the hardware away and processes the display output.
The display is a multiplexed row, where the columns are controlled with a bitvalue PWM for brightness modulation. The display process is a high frequency timer to ensure low flickering.

#### Operating System (os)
The operating system adds lowlevel functionality for datacompression, PRNG and a small scheduler for non-realtime tasks.

#### Engines
The engines are the processes for displaying freerunnning patterns.

#### System (sys)
The system submodule handles the main state handling and switches between freerunning and slave mode.

#### Slave Mode Communication (com)
The slave mode communication uses the UART library by Peter Fleury.
It listens on serial port. When it receives the symbol 's', the system is switched in slave mode and waits for the display data packets. The data packet starts with symbol 'f' and is followed by 40bytes with packet 64 5-bit brightness values. 

### Hardware
#### Ports
The display is connected:

Display|Port
-------|----
Col1| PB0
Col2| PC1
Col3| PC2
Col4| PC3
Col5| PC4
Col6| PC5
Col7| PB3
Col8| PB7
Row1| PB1
Row2| PB2
Row3| PD3
Row4| PD4
Row5| PD5
Row6| PD6
Row7| PD7
Row8| PB5

## FAQ
### Do I need 16MHz clock?
Yes, with lower frequencies, the display would flicker.
 






