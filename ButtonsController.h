/*******************************************************************************
https://github.com/flosorin/ButtonsController.git

Arduino library to control five buttons using only one analog pin (and ground). 

The purpose is to place the buttons in a cross to have the controls 
LEFT / RIGHT / UP / DOWN and CENTER.

For this to work, you will need five 10K resistors in addition to the 
five buttons (see schematic enclosed).

********************************************************************************/

#ifndef BUTTONS_CTRL_H
#define BUTTONS_CTRL_H

#include "Arduino.h"

typedef enum {NONE, LEFT, CENTER, RIGHT, UP, DOWN} ButtonsValue;

class ButtonsController {

public:
  ButtonsController(int buttonsPin); // Constructor: initialize the pin to be used for reading the button value
  String buttonValueToString();      // Return the string representation of the button value
  void updateButtonValue();         // Must be called in loop(), modify buttonValue if needed
  ButtonsValue getButtonValue();     // Accessor to the final button value to be used

private :
  ButtonsValue readButton(); // Return the button value, before debouncing
  ButtonsValue buttonValue;  // The final button value (debounced)
  int buttonsPin;            // The pin to be used for reading the button value
};

#endif // BUTTONS_CTRL_H
