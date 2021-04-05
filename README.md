# Arduino-8x8-matrix-library
A library for using 8x8 matrix with two shift register.
### Features

- printMessage() method
- printMat() method
- printNum() method
- parameters() method
- image() method
- rotation() method

### Getting Started
1. Download the library folder
2. Create the circuit:
  Follow 8x8 matrix circuit.pdf to create your own circuit.
3. Start coding:

```c++
#include <Matrix.h>//include library
void setup()
{
  
}
void loop()
{
   Matrix mat(2,3,4);//create the object mat
}
```
View example-matrix.ino for all functions.

## Documentation

-   To create a new matrix:
```c++
Matrix MyMatrix(signal_pin, shiftClock_pin, registerClock_pin);
```
    signal_pin,shiftClock_pin,registerClock_pin are int numbers;
    signal pin, shiftClock pin and registerClock pin must be all digital output pins.
-   To set parameters:
```c++
MyMatrix.parameters(frequency, number_of_frame);
```
    - frequency is the int number of images per second
    - number_of_frame is the int number of frames
-   To set the matrix's pattern:
```c++
MyMatrix.image(Array_pattern);
```
    - Array_pattern is the array of byte that contains the matrix's pattern.
-   To print the matrix's pattern:
```c++
MyMatrix.printMat();
```
    - This method has no arguments
    - It prints the pattern that was insert with .image() method
- To rotate the pattern:
```c++
MyMatrix.rotate(sine_angle, cosine_angle);
```
    - This method rotate the pattern
    - The argoments are floats
    - Sine_angle is the sine of the angle of the counterclockwise rotation
    - Cosine_angle is the cosine of the angle of the counterclockwise rotation
- To print a number:
```c++
MyMatrix.printNum(number_to_print, frames);
```
    - number_to_print is the two-digit integrer that will be shown
    - frames is the integrer of frames to print
- To print a message/string:
```c++
MyMatrix.printMessage(message_to_print, frames);
```
    - message_to_print is the string thet will be shown
    - frames is the integrer of frames to print for steps
