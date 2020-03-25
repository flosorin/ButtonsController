/*******************************************************************************
https://github.com/flosorin/ButtonsController.git

Arduino library to control five buttons using only one analog pin (and ground). 

The purpose is to place the buttons in a cross to have the controls 
LEFT / RIGHT / UP / DOWN and CENTER.

For this to work, you will need five 10K resistors in addition to the 
five buttons (see schematic enclosed).

This example displays the pressed button as string on the serial line.

*******************************************************************************/

#include <ButtonsController.h>

ButtonsController buttons = ButtonsController(A1);

void setup() 
{
  Serial.begin (9600);
}

void loop() 
{
  buttons.updateButtonValue(); // Must be called in loop as frequently as possible
  
  if (buttons.getButtonValue() != NONE)
    Serial.println(buttons.buttonValueToString());
}
