/*
  Awesome.h library - for the Awesome Shield Learning Platform
  Copyright Awesome Shield UG (haftungsbeschraenkt), all rights reserved
  MIT License
*/

#ifndef Awesome_h
#define Awesome_h

#include "Arduino.h"
#include "Wire.h"
#include "rgb_lcd.h"
#include <Servo.h>

#define rgbRedPin       5   // pwm
#define rgbGreenPin     6   // pwm
#define rgbBluePin      3   // pwm

#define buzzerPin       9   // pwm
#define buttonPin       2   // io digital
#define switchOnPin     8   // io digital
#define lightSensorPin  A1
#define tempSensorPin   A2
#define knobPin         A3
#define port1pin        A5  // primary (outside) pin
#define port2pin        A0  // primary (outside) pin

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
    void setVariables(int pin);
    int reading();
  private:
    int _pin;
    bool _hardwareSetupComplete;
    void _setupHardware();
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

class Button {
  public:
    void setVariables(int pin, bool readingMeaningButtonIsDown, bool needsPullup = false);
    bool isDown();
    bool isUp();
  private:
    int _pin;
    bool _readingMeaningButtonIsDown;
    bool _needsPullup;
    bool _hardwareSetupComplete;
    void _setupHardware();
    void _setupPullup();
};

class Buzzer {
  public:
    void setVariables(int pin);
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
    bool _hardwareSetupComplete;
    void _setupHardware();
};

class DigitalInput {
  public:
    void setVariables(int pin, bool stateThatMeansIsOn, bool needsPullup = false);
    bool isOn();
    bool isOff();
  private:
    int _pin;
    int _stateThatMeansIsOn;
    bool _needsPullup;
    bool _hardwareSetupComplete;
    void _setupHardware();
};

class DigitalOutput {
  public:
    void setVariables(int pin);
    void turnOn();
    void turnOff();
    bool isOn();
    bool isOff();
  private:
    int _pin;
    int _stateIsOn;
    bool _hardwareSetupComplete;
    void _setupHardware();
};

class AnalogInput {
  public:
    void setVariables(int pin);
    int reading();
  private:
    int _pin;
    int _value;
    bool _hardwareSetupComplete;
    void _setupHardware();
};

class AnalogOutput {
  public:
    void setVariables(int pin);
    void set(int newSetting);
    int setting();
  private:
    int _pin;
    int _currentSetting;
    bool _hardwareSetupComplete;
    void _setupHardware();
};

class SERVO {
  public:
    void setVariables(int pin);
    void setPosition(int position);
    Servo _servo;
  private:
    int _pin;
    bool _hardwareSetupComplete;
    void _setupHardware();

};

class groveLCD {
  public:
    void setup();
    void print(String message);
  private:
    rgb_lcd _lcd;
};

class electretMic {
  public:
    void setVariables(int pin);
    int reading();
  private:
    int _pin;
    bool _hardwareSetupComplete;
    void _setupHardware();
};

class port {
  public:
    port();
    Button button;
    Buzzer buzzer;
    DigitalInput touchSensor;
    DigitalOutput singleColorLED;
    DigitalOutput relay;
    AnalogInput knob;
    AnalogInput temperatureSensor;
    AnalogInput lightSensor;
    SERVO servo;
    electretMic mic;
    void setPins(int primaryPin, int secondaryPin);
  private:
    int _primaryPin;
    int _secondaryPin;
};

class Awesome {
  public:
    Awesome();
    // outputs
    led LED;
    Buzzer buzzer;
    // inputs
    LightSensor lightSensor;
    AnalogInput knob;
    TemperatureSensor temperatureSensor;
    Button button;
    DigitalInput toggleSwitch;
    // ports
    port port1;
    port port2;
  private:
};

#endif
