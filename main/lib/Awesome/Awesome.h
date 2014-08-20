/*
  Awesome.h library - for reading Awesomes
  Created by Christopher W. J. Palmer, 26 May 2014
  Part of the BrewBox Project
  Private library, not for public use.
*/

#ifndef Awesome_h
#define Awesome_h

#define rgbRedPin       3  // PWM
#define rgbGreenPin     5
#define rgbBluePin      6
#define redLedPin       4
#define greenLedPin     7
#define buzzerPin       9
#define buttonPin       2
#define switchOnPin     8
#define lightSensorPin  A1
#define tempSensorPin   A2
#define micPin          NULL

/* Pins Kept Free
0,1               RX, TX for comms
A4, A5            for RTC on data logger shield
10, 11, 12, 13    for SD card on data logger shield
*/

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
    float _read();
};

class Switch {
  public:
    void setup(int pin);
    bool read();
  private:
    int _pin;
};

class Buzzer {
  public:
    void setup(int pin);
    void beep(int millis);
    void setSilent(bool newState);
  private:
    int _pin;
    bool _silent;
};

class Awesome {
  public:
    Awesome();

    ioLED redLED;
    ioLED greenLED;
    redGreenBlueLED rgbLED;
    Buzzer buzzer;

    LightSensor lightSensor;
    TemperatureSensor temperatureSensor;
    Switch button;
    Switch toggle;
    int   micRead();

    void diagnostic();
  private:
    void _LedsFlash(int millis);
    void _LedsTurnOn();
    void _LedsTurnOff();
    void _LedsCycle();
    void _allOkay();
};

#endif
