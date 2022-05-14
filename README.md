# ArduinoLEDMatrixSnake
## Description
This project is an implementation of the classic game "Snake" created for an LED Matrix and Arduino Uno. A python script is included to listen for keyboard input and send it through the serial port to the Arduino. 
## Dependencies
In order to use this project, users will need an Arduino Uno, 8x8 LED Matrix, 8 jumper wires, 8 220 Ohm resistors and a breadboard. The project also requires Arduino IDE and Python version 3.9 with the following libraries installed:
- [pynput](https://pypi.org/project/pynput)
- [pyserial](https://pypi.org/project/pyserial)
## Setup
Clone the repository to your device in your desired directory:

`git clone https://github.com/thomashart17/ArduinoLEDMatrixSnake`

Setup the Arduino and LED Matrix as show in the following diagram:

[Arduino Setup](images/ArduinoSetup.jpg)

Using Arduino IDE, build and upload the code in Snake.ino to your Arduino board.

In the main.py file, change the PORT variable to the name of the serial port where you connected your Arduino.

## Controls
Run the main.py file to start the input listener and use the following controls:
- Enter: Start game
- Arrow Keys: Change snake direction
- Escape: Stop the input listener