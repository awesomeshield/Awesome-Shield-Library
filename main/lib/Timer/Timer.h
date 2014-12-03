/*
  Timer.h library - for reading Timers
  Created by Christopher W. J. Palmer, 26 May 2014
  Part of the BrewBox Project
  Private library, not for public use.
*/

#ifndef Timer_h
#define Timer_h

#include "Arduino.h"

class Timer
{
  public:
    Timer(int duration);
    bool isDone();
  private:
    int _remainingTime;
    int _startTime;
    int _duration;
};

#endif
