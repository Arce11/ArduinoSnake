# Arduino Snake

This is a toy project and my first take on Arduino itself. It implements a snake game on an 8x8 LED Matrix using an Arduino board. The full basic functionality is included: score counting (on 7-segment displays), random "food" generation and game over on self and edge colissions. Matrix illumination is handled by cycling through each LED very quickly, one at a time.

## Circuitry 'n stuff

The design was implemented on an Arduino Uno board. Two serial/parallel ```74HC595N``` ICs were used to handle the 16 pins of the LED Matrix through 4 Arduino pins. The matrix itself is a ```REC-M1388ASR``` circuit. The two ```74HC595N``` chips are used for the row and column selection respectively. Additionally, a triple 7-segment (common-cathode) display is used to keep track of the score. Note that the third display is not needed since the maximum score will always be below 64. The display ends up taking up most of the available I/O pins, and a game expansion would probably require another serial/parallel IC to handle it. Finally, two buttons connect directly to the Arduino for LEFT/RIGHT turning in-game. No reset functionality is included, other than reseting the board itself


Code parameters are available in ```parameters.h``` to make changes to pin layout and several parameters simpler. 

![Demo CountPages alpha](https://share.gifyoutube.com/KzB6Gb.gif)



## Disclaimer

This is just a for-fun project and may contain bugs or sub-optimal coding, just so you know.
