/*
  Awesome.h library - for reading Awesomes
  Created by Christopher W. J. Palmer, 26 May 2014
  Part of the BrewBox Project
  Private library, not for public use.
*/

#ifndef Awesome_h
#define Awesome_h

#define rgbRedPin       3   // pwm
#define rgbGreenPin     5   // pwm
#define rgbBluePin      6   // pwm
#define redLedPin       4   // io digital
#define greenLedPin     7   // io digital
#define buzzerPin       9   // pwm
#define buttonPin       2   // io digital
#define switchOnPin     8   // io digital
#define lightSensorPin  A1
#define tempSensorPin   A2
#define micPin          NULL

#define SDRedLEDPin          2      // for SD shield only

/* Pins Kept Free
0,1               RX, TX for comms
A4, A5            for RTC on data logger shield
10, 11, 12, 13    for SD card on data logger shield
*/

// assign values to the text based color inputs
#define WHITE    3001  // more of a turquoise
#define RED      3002
#define GREEN    3003
#define BLUE     3004
#define YELLOW   3005  // more of a turqoise
#define PURPLE   3006  // good
#define CYAN     3007  // nice

#include "Arduino.h"
//#include "Timer.h"
// #include <SD.h>                             //SD card library
// #include <Wire.h>                           //One Wire library
//#include "RTClib.h"                         //Real Time Clock library

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
    void turnOn(int ColorOrHowMuchRed, int howMuchGreen = 0, int howMuchBlue = 0);
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
    double check();
  private:
    int _pin;
};

class TemperatureSensor {
  public:
    void setup(int pin);
    float check();
  private:
    int _pin;
    float _check();
};

class Switch {
  public:
    void setup(int pin);
    bool check();
  private:
    int _pin;
};

class Buzzer {
  public:
    void setup(int pin);
    void beep(unsigned long millis, unsigned int frequency = 400);
    void setSilentMode(bool newState);
  private:
    int _pin;
    bool _silent;
};

/*
class DataLogger {
  public:
    void setup(String headers);   // include optional NOTIMESTAMP argument
    void log(String row);         // include optional NOTIMESTAMP argument
    void printFileName();
  private:
    char _filename[];
    File _dataFile;
    RTC_DS1307 _RTC;
    void _RTCSetup();
    void _error(char *str);
    void _makeFile();
};
*/

class Awesome {
  public:
    Awesome();

    ioLED redLED;
    ioLED greenLED;
    redGreenBlueLED colorLED;
    Buzzer buzzer;

    LightSensor lightSensor;
    TemperatureSensor temperatureSensor;
    Switch button;
    Switch toggle;
    //int   miccheck();

    //DataLogger dataLogger;

    //void test();
  private:
    void _LedsFlash(int millis);
    void _LedsTurnOn();
    void _LedsTurnOff();
    void _LedsCycle();
    void _allOkay();
};

#endif
