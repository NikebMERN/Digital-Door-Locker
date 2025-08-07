# Digital Door Lock with IR Remote and Servo

## Overview
This project implements a digital door lock controlled by an IR remote. Users enter a numeric code using the remote’s number buttons and confirm with the power button. If the entered code matches the preset code, the door unlocks using a servo motor and a green LED lights up. If the code is wrong, the red LED blinks.

## Features
- IR remote input with real-time code display via Serial Monitor
- Servo motor controls door lock/unlock position
- Red and green LEDs indicate lock status
- Automatic timeout resets code entry after 10 seconds of inactivity

## Hardware Requirements
- Arduino board (e.g. Uno, Mega)
- IR receiver module
- IR remote control
- Servo motor
- Red and green LEDs with appropriate resistors
- Connecting wires and breadboard

## Wiring
- IR Receiver signal to Arduino pin 2
- Servo signal to Arduino pin 9
- Red LED to pin 10 (with resistor)
- Green LED to pin 11 (with resistor)
- Common ground for all components

## Usage
1. Upload the code to your Arduino.
2. Open the Serial Monitor at 9600 baud to view code inputs and status.
3. Enter the preset code (default is `1234`) using the IR remote.
4. Press the power button (`O`) to confirm the code.
5. Door unlocks with green LED if the code matches.
6. Wrong code triggers red LED blinking.

## License
This project is released under the MIT License.
