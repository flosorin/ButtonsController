/*******************************************************************************
https://github.com/flosorin/ButtonsController.git

Arduino library to control five buttons using only one analog pin (and ground). 

The purpose is to place the buttons in a cross to have the controls 
LEFT / RIGHT / UP / DOWN and CENTER.

For this to work, you will need five 10K resistors in addition to the 
five buttons (see schematic enclosed).

********************************************************************************/

#include "ButtonsController.h"

#define DEBOUNCE_DELAY_MS 50

/* Constructor: initialize the pin to be used for reading the button value */
ButtonsController::ButtonsController(int buttonsPinInit) 
{
  buttonsPin = buttonsPinInit;
  buttonValue = NONE;
  pinMode (buttonsPin, INPUT_PULLUP);
}

/* Return the string representation of the button value */
String ButtonsController::buttonValueToString()
{
  switch (buttonValue) {
    case NONE:
      return "NONE";
    case LEFT:
      return "LEFT";
    case CENTER:
      return "CENTER";
    case RIGHT:
      return "RIGHT";
    case UP:
      return "UP";
    case DOWN:
      return "DOWN";   
  }

  return "NONE";
}

/* Must be called in loop(), modify buttonValue if needed */
void ButtonsController::updateButtonValue()
{
  static int newValue = NONE, oldValue = NONE;
  static unsigned long lastUpdatedTime = 0;
  static boolean isVerifying = false;

  buttonValue = NONE;

  // Read new button value
  if (!isVerifying) {
    newValue = readButton();
    if (newValue != oldValue) {
      lastUpdatedTime = millis();
      isVerifying = true;
    }
  }
  // Manage debounce by waiting a bit before reading the value again
  if (isVerifying && ((millis() - lastUpdatedTime) > DEBOUNCE_DELAY_MS)) {
    // If value is still the same, take it into account and update buttonValue
    if (newValue == readButton()) {
       oldValue = newValue;
       buttonValue = newValue;
    }
    isVerifying = false;
  }
}

/* Accessor to the final button value to be used */
ButtonsValue ButtonsController::getButtonValue()
{
  return buttonValue;
}

/* Return the button value, before debouncing */
ButtonsValue ButtonsController::readButton()
{
  int buttonRawValue = 0, buttonFormattedValue = NONE;
    
  // Get raw value (use average to minimize fluctuation)
  for (int i = 0; i < 4; i++)
     buttonRawValue += analogRead(buttonsPin);
  buttonRawValue = buttonRawValue / 4;
 
  // Map raw value to the corresponding button
  if (buttonRawValue >= 228 && buttonRawValue <= 240)
    buttonFormattedValue = LEFT;
  else if (buttonRawValue >= 360 && buttonRawValue <= 380)
    buttonFormattedValue = CENTER;
  else if (buttonRawValue >= 455 && buttonRawValue <= 470)
    buttonFormattedValue = RIGHT;
  else if (buttonRawValue >= 525 && buttonRawValue <= 545)
    buttonFormattedValue = UP;
  else if (buttonRawValue >= 575 && buttonRawValue <= 650)
    buttonFormattedValue = DOWN;
  else
    buttonFormattedValue = NONE;
    
  return buttonFormattedValue;   
}