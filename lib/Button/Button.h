/*
  Button.h library - for reading buttons
  Created by Christopher W. J. Palmer, 26 May 2014
  Part of the BrewBox Project
  Private library, not for public use.
*/

#ifndef Button_h
#define Button_h

#include "Arduino.h"

class Button
{
  public:
    Button(int pin);
    bool isPressedNow();

  private:
    int _pin;
    float _currentTemp;
    bool _read();
};

#endif
