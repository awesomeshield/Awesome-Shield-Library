/*
  Button.cpp library - for reading buttons
  Created by Christopher W. J. Palmer, 26 May 2014
  Part of the BrewBox Project
  Private library, not for public use.
*/

#include "Arduino.h"
#include "Button.h"

Button::Button(int pin)
{
  _pin = pin;
  pinMode(_pin, INPUT);
}

bool Button::isPressedNow()
{
  return _read();
}

bool Button::_read()
{
  return digitalRead(_pin);
}
