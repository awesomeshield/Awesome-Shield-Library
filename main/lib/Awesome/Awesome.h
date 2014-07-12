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

class redGreenBlueLED {
  public:
    void turnOn(int c1, int c2 = 0, int c3 = 0);
    void turnOff();
    void setup(int redPin, int greenPin, int bluePin);
  private:
    int _redPin;
    int _greenPin;
    int _bluePin;
    void _setPins (int redPin, int greenPin, int bluePin);
};

class LightSensor {
  public:
    void setup(int pin);
    int read();
  private:
    int _pin;
};

class TemperatureSensor {
  public:
    void setup(int pin);
    float read();
  private:
    int _pin;
    float _tempRead();
};

class Awesome {
  public:
    Awesome();

    ioLED redLED;
    ioLED greenLED;
    redGreenBlueLED rgbLED;
    LightSensor lightSensor;
    TemperatureSensor temperatureSensor;

    int   lightRead();
    int   micRead();
    bool  switchRead();
    bool  buttonRead();
    float tempRead();

    void beep(int millis);

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
