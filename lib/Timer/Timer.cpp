/*
  Timer.cpp library - for reading Timers
  Created by Christopher W. J. Palmer, 26 May 2014
  Part of the BrewBox Project
  Private library, not for public use.
*/

#include "Arduino.h"
#include "Timer.h"

Timer::Timer(int duration) {
  _duration = duration;
  _startTime = millis();
}

bool Timer::isDone() {
  _remainingTime = _duration - millis() - _startTime;
  return (_remainingTime < _duration);
}
