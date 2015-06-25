/*
  Awesome.h library - for the Awesome Shield Learning Platform
  Awesome Shield UG (Haftungsbeschrankt)
  MIT License
*/

#ifndef Awesome_h
#define Awesome_h

#define rgbRedPin       3   // pwm
#define rgbGreenPin     5   // pwm
#define rgbBluePin      6   // pwm
#define buzzerPin       9   // pwm
#define buttonPin       2   // io digital
#define switchOnPin     8   // io digital
#define lightSensorPin  A1
#define tempSensorPin   A2
#define knobPin         A3

// the max analogWrite value
#define MAX      255
// assign values to the text based color inputs
#define WHITE    3001
#define RED      3002
#define GREEN    3003
#define BLUE     3004
#define YELLOW   3005
#define PURPLE   3006
#define CYAN     3007

#include "Arduino.h"

class led {
  public:
    void turnOn(int color = WHITE);
    void turnOn(int howMuchRed, int howMuchGreen, int howMuchBlue);
    void turnOff();
    bool isOn();
    bool isOff();
    void flash(int duration = 1000, int  = WHITE, int howMuchGreen = 0, int howMuchBlue = 0);
    void setup(int redPin, int greenPin, int bluePin);
  private:
    int _redPin;
    int _greenPin;
    int _bluePin;
    bool _stateIsOn;
    void _setPins (int redPin, int greenPin, int bluePin);
};

class LightSensor {
  public:
    void setup(int pin);
    int reading();
  private:
    int _pin;
    int _read();
};

class Potentiometer {
  // [ ] verify range is 0-1024 (use grove one)
  public:
    void setup(int pin);
    int reading();
  private:
    int _pin;
    int _read();
};

class TemperatureSensor {
  public:
    void setup(int pin);
    float reading();
  private:
    int _pin;
    float _read();
};

class Switch {
  public:
    void setup(int pin, bool readingMeaningSwitchIsOn);
    bool isOn();
    bool isOff();
  private:
    int _pin;
    bool _readingMeaningSwitchIsOn;
};

class Button {
  public:
    void setup(int pin, bool readingMeaningButtonIsDown);
    bool isDown();
    bool isUp();
  private:
    int _pin;
    bool _readingMeaningButtonIsDown;
};

class Buzzer {
  public:
    void setup(int pin);
    void turnOn(unsigned int frequency = 400);
    void turnOff();
    bool isOn();
    bool isOff();
    void beep(unsigned long millis, unsigned int frequency = 400);
    void setSilentMode(bool newState);
  private:
    int _pin;
    bool _silent;
    bool _stateIsOn;
};

class Awesome {
  public:
    Awesome();

    led LED;
    Buzzer buzzer;

    LightSensor lightSensor;
    Potentiometer knob;
    TemperatureSensor temperatureSensor;
    Button button;
    Switch toggleSwitch;

  private:
};

#endif
