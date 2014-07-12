/*
  Awesome.h library - for reading Awesomes
  Created by Christopher W. J. Palmer, 26 May 2014
  Part of the BrewBox Project
  Private library, not for public use.
*/

#ifndef Awesome_h
#define Awesome_h

#define rgbRedPin       3  // PWM
#define rgbGreenPin     2
#define rgbBluePin      4
#define redLedPin       6
#define greenLedPin     5
#define buzzerPin       NULL
#define buttonPin       7
#define switchOnPin     8
#define lightSensorPin  A1
#define tempSensorPin   12
#define micPin          NULL

#define WHITE    300
#define RED      301
#define GREEN    302
#define BLUE     303
#define YELLOW   304
#define MAGENTA  305
#define CYAN     306

#include "Arduino.h"
#include "Timer.h"

class ioLED {
  public:
    void turnOn();
    void turnOff();
    void setup(int pin);
  private:
    void _setPin(int pin);
    int _pin;
};

class Awesome {
  public:
    Awesome();

    ioLED redLED;
    ioLED greenLED;

    int   lightRead();
    int   micRead();
    bool  switchRead();
    bool  buttonRead();
    float tempRead();

    void beep(int millis);
    void rgbLedOn(int c1, int c2 = 0, int c3 = 0);    // should be (int colour, int duration w. default)
    void rgbLedOff();
    void redLedOn();            // should be (int duration w. default)
    void redLedOff();
    void greenLedOn();          // should be (int duration w. default)
    void greenLedOff();
    // need to create LED objects use timers properly

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
