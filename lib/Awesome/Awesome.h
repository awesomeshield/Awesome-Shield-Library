/*
  Awesome.h library - for reading Awesomes
  Created by Christopher W. J. Palmer, 26 May 2014
  Part of the BrewBox Project
  Private library, not for public use.
*/

#ifndef Awesome_h
#define Awesome_h

#define rgbRedPin       3      // 3
#define rgbGreenPin     2      // 5
#define rgbBluePin      4      // 6
#define redLedPin       6
#define greenLedPin     5
#define buzzerPin       NULL
#define buttonPin       7
#define switchOnPin     8
#define lightSensorPin  A1
#define tempSensorPin   12
#define micPin          NULL

#define RED      1
#define GREEN    2
#define BLUE     3
#define YELLOW   4
#define MAGENTA  5
#define CYAN     6
#define WHITE    7

#include "Arduino.h"

class Awesome
{
  public:
    Awesome();
    int lightRead();
    int micRead();
    bool switchRead();
    bool buttonRead();
    float tempRead();

    void beep(int millis);
    void rgbLedOn(int colour);
    void rgbLedOff();

    void diagnostic();
  private:
    bool _switchIsOn();
    bool _buttonIsPressed();
    void _LedsFlash(int millis);
    void _LedsTurnOn();
    void _LedsTurnOff();
    void _LedsCycle();
};

#endif
