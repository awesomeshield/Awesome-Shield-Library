/*
  Awesome.h library - for the Awesome Shield Learning Platform
  Copyright Awesome Shield UG (haftungsbeschraenkt), all rights reserved
  MIT License
*/

#ifndef Awesome_h
#define Awesome_h

// include other libraries
#include "Arduino.h"
#include "Wire.h"
//#include "rgb_lcd.h"
#include <Servo.h>
#include <Adafruit_NeoPixel.h>

//Neopixel setup
#ifdef __AVR__
  #include <avr/power.h>
#endif

// define core board pin numbers
#define LEDPin              5
#define buzzerPin           9   // pwm
#define buttonPin           2   // io digital
#define switchOnPin         8   // io digital
#define lightSensorPin      A1
#define knobPin             A3
#define port1PrimaryPin     A5  // primary (outside) pin
#define port1SecondaryPin   A4
#define port2PrimaryPin     A0  // primary (outside) pin
#define port2SecondaryPin   3
#define port3PrimaryPin     A2  // primary (outside) pin
#define port3SecondaryPin   6

// number of neopixels connected
#define numPixels      1

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
//#define ORANGE   3008

class led {
  public:
    void turnOn(int color = WHITE);
    void turnOn(int red, int green, int blue);
    void turnOff(int color = WHITE);
    bool isOn();
    bool isOff();
    void setup();
  private:
    Adafruit_NeoPixel _pixel = Adafruit_NeoPixel(numPixels, LEDPin, NEO_GRB + NEO_KHZ800);
    void _update();
    int _redSetting;
    int _greenSetting;
    int _blueSetting;
    void _setPins (int redPin, int greenPin, int bluePin);
};

class LightSensor {
  public:
    void setVariables(int pin, uint8_t port, String componentName);
    int reading();
    void print();
  private:
    int _pin;
    uint8_t _port;
    String _componentName;
    bool _hardwareSetupComplete;
    void _setupHardware();
    int _read();
};

class Button {
  public:
    void setVariables(int pin, int portNumber, String componentName, bool readingMeaningButtonIsDown, bool needsPullup = false);
    bool isDown();
    bool isUp();
    void print();
  private:
    int _pin;
    int _portNumber;
    bool _readingMeaningButtonIsDown;
    bool _needsPullup;
    bool _hardwareSetupComplete;
    void _setupHardware();
    void _setupPullup();
    String _componentName;
};

class Buzzer {
  public:
    void setVariables(int pin, uint8_t portNumber, String componentName);
    void turnOn(unsigned int frequency = 400);
    void turnOff();
    bool isOn();
    bool isOff();
    void setSilentMode(bool newState);
  private:
    int _pin;
    uint8_t _portNumber;
    bool _silent;
    bool _stateIsOn;
    bool _hardwareSetupComplete;
    void _setupHardware();
    String _componentName;
};

class DigitalInput {
  public:
    void setVariables(int pin, uint8_t portNumber, String componentName, bool stateThatMeansIsOn, bool needsPullup = false);
    bool isOn();
    bool isOff();
    void print();
  private:
    int _pin;
    uint8_t _portNumber;
    int _stateThatMeansIsOn; // [ ] make this a bool
    bool _needsPullup;
    bool _hardwareSetupComplete;
    void _setupHardware();
    String _componentName;
};

class DigitalOutput {
  public:
    void setVariables(int pin, uint8_t portNumber, String componentName);
    void turnOn();
    void turnOff();
    bool isOn();
    bool isOff();
    void print();
  private:
    int _pin;
    uint8_t _portNumber;
    int _stateIsOn; // [ ] make this a bool
    bool _hardwareSetupComplete;
    void _setupHardware();
    String _componentName;
};

class AnalogInput {
  public:
    void setVariables(int pin, uint8_t portNumber, String componentName);
    int reading();
    void print();
  private:
    int _pin;
    uint8_t _portNumber;
    int _value;
    bool _hardwareSetupComplete;
    void _setupHardware();
    String _componentName;
};

class AnalogOutput {
  public:
    void setVariables(int pin, uint8_t portNumber, String componentName);
    void set(int newSetting);
    int setting();
    void print();
  private:
    int _pin;
    uint8_t _portNumber;
    int _currentSetting;
    bool _hardwareSetupComplete;
    void _setupHardware();
    String _componentName;
};

class SERVO {
  public:
    void setVariables(int pin, uint8_t portNumber, String componentName);
    void setPosition(int position);
    Servo _servo;
  private:
    int _pin;
    uint8_t _portNumber;
    bool _hardwareSetupComplete;
    void _setupHardware();
    String _componentName;
};

// class groveLCD {
//   public:
//     void print(String message);
//   private:
//     rgb_lcd _lcd;
//     void _setupHardware();
//     bool _hardwareSetupComplete;
// };

class electretMic {
  public:
    void setVariables(int pin, uint8_t portNumber, String componentName);
    int reading();
  private:
    int _pin;
    uint8_t _portNumber;
    bool _hardwareSetupComplete;
    void _setupHardware();
    String _componentName;
};

class UltrasonicRanger {
  public:
    void setVariables(int pin, uint8_t portNumber, String componentName);
    int reading();
  private:
    int _pin;
    uint8_t _portNumber;
    String _componentName;
};

class IRProximitySensor {
  public:
    void setVariables(int pin, uint8_t portNumber, String componentName);
    int reading();
  private:
    int _pin;
    uint8_t _portNumber;
    bool _hardwareSetupComplete;
    void _setupHardware();
    String _componentName;
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
    AnalogInput slider;
    SERVO servo;
    electretMic mic;
    UltrasonicRanger sonicSensor;
    // groveLCD LCD;
    IRProximitySensor IR;
    DigitalOutput electromagnet;
    void setVariables(int primaryPin, int secondaryPin, uint8_t portNumber);
  private:
    int _primaryPin;
    int _secondaryPin;
    uint8_t _portNumber;
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
    Button button;
    DigitalInput toggleSwitch;
    // ports
    port port1;
    port port2;
    port port3;
    void setup(int baudRate);
  private:
};

#endif
