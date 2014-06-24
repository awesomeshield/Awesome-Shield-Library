/*
  Awesome.cpp library - for reading Awesomes
  Created by Christopher W. J. Palmer, 26 May 2014
  Part of the BrewBox Project
  Private library, not for public use.
*/

#include "Arduino.h"
#include "Button.h"
#include "Awesome.h"

Awesome::Awesome()
{
}

bool Awesome::button::isPressed() {
  return digitalRead(7);
}
