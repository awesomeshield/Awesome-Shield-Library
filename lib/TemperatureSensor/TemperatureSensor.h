/*
  Heater.h library - for controlling heaters
  Created by Christopher W. J. Palmer, 26 May 2014
  Part of the BrewBox Project
  Private library, not for public use.
*/

#ifndef TemperatureSensor_h
#define TemperatureSensor_h

#include "Arduino.h"

class TemperatureSensor
{
  public:
  }(int pin);

    // commands
    float read();

    // get state
    float currentTemp();

  private:
    int _pin;
    float _currentTemp;

};

#endif
