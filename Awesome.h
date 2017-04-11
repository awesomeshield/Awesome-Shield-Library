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
#include <AS_Adafruit_NeoPixel.h> // on-board LED
#include <AS_Four_Digit_Display_Arduino.h> // Grove 4-digit display

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
#define numberOfPixels      1

// the max analogWrite value
#define MAX      255

// Enumeration of possible color values
enum LedColor {WHITE,RED,GREEN,BLUE,YELLOW,PURPLE,CYAN,PINK,ORANGE};

// C major scale, two octaves from C4 to C6 {C, D, E, F, G, A, B, C, D, E, F, G, A, B, C }
const int Cmaj[] = {262, 294, 329, 349, 392, 440, 494, 523, 587, 659, 698, 784, 880, 988, 1046};
// C minor scale, two octaves from C4 to C6 {C, D, Eb, F, G, Ab, Bb, C, D, Eb, F, G, Ab, Bb, C }
const int Cmin[] = {262, 294, 311, 349, 392, 415, 466, 523, 587, 622, 698, 784, 831, 932, 1046};

class led {
  public:
    void turnOn(LedColor color = WHITE);
    void turnOn(int red, int green, int blue);
    void turnOff(LedColor color = WHITE);
    bool isOn();
    bool isOff();
    void setup();
  private:
    AS_Adafruit_NeoPixel _pixel = AS_Adafruit_NeoPixel(numberOfPixels, LEDPin, AS_NEO_GRB + AS_NEO_KHZ800);
    void _update();
    uint8_t _redSetting;
    uint8_t _greenSetting;
    uint8_t _blueSetting;
    void _setPins (uint8_t redPin, uint8_t greenPin, uint8_t bluePin);
};

class LightSensor {
  public:
    void setVariables(uint8_t pin, uint8_t port);
    int reading();
    void print();
  private:
    uint8_t _pin;
    uint8_t _port;
    bool _hardwareSetupComplete;
    void _setupHardware();
    int _read();
};

class Button {
  public:
    void setVariables(uint8_t pin, uint8_t portNumber, bool readingMeaningButtonIsDown, bool needsPullup = false);
    bool isDown();
    bool isUp();
    void print();
  private:
    uint8_t _pin;
    uint8_t _portNumber;
    bool _readingMeaningButtonIsDown;
    bool _needsPullup;
    bool _hardwareSetupComplete;
    void _setupHardware();
    void _setupPullup();
};

class Buzzer {
  public:
    void setVariables(uint8_t pin, uint8_t portNumber);
    void turnOn(unsigned int frequency = 400);
    void turnOff();
    bool isOn();
    bool isOff();
    void setSilentMode(bool newState);
    void playFanfare();
  private:
    uint8_t _pin;
    uint8_t _portNumber;
    bool _silent;
    bool _stateIsOn;
    bool _hardwareSetupComplete;
    void _setupHardware();
};

class DigitalInput {
  public:
    void setVariables(uint8_t pin, uint8_t portNumber, String componentName, bool stateThatMeansIsOn, bool needsPullup = false);
    bool isOn();
    bool isOff();
    void print();
  private:
    uint8_t _pin;
    uint8_t _portNumber;
    bool _stateThatMeansIsOn;
    bool _needsPullup;
    bool _hardwareSetupComplete;
    void _setupHardware();
    String _componentName;
};

class DigitalOutput {
  public:
    void setVariables(uint8_t pin, uint8_t portNumber, String componentName);
    void turnOn();
    void turnOff();
    bool isOn();
    bool isOff();
    void print();
  private:
    uint8_t _pin;
    uint8_t _portNumber;
    int _stateIsOn; // [ ] make this a bool
    bool _hardwareSetupComplete;
    void _setupHardware();
    String _componentName;
};

class AnalogInput {
  public:
    void setVariables(uint8_t pin, uint8_t portNumber, String componentName);
    int reading();
    void print();
  private:
    uint8_t _pin;
    uint8_t _portNumber;
    int _value;
    bool _hardwareSetupComplete;
    void _setupHardware();
    String _componentName;
};

class AnalogOutput {
  public:
    void setVariables(uint8_t pin, uint8_t portNumber, String componentName);
    void set(int newSetting);
    int setting();
    void print();
  private:
    uint8_t _pin;
    uint8_t _portNumber;
    int _currentSetting;
    bool _hardwareSetupComplete;
    void _setupHardware();
    String _componentName;
};

class SERVO {
  public:
    void setVariables(uint8_t pin, uint8_t portNumber);
    void setPosition(int position);
    Servo _servo;
  private:
    uint8_t _pin;
    uint8_t _portNumber;
    bool _hardwareSetupComplete;
    void _setupHardware();
};

class electretMic {
  public:
    void setVariables(uint8_t pin, uint8_t portNumber);
    int reading();
  private:
    uint8_t _pin;
    uint8_t _portNumber;
    bool _hardwareSetupComplete;
    void _setupHardware();
};

class UltrasonicRanger {
  public:
    void setVariables(uint8_t pin, uint8_t portNumber);
    int reading();
  private:
    int _pin;
    uint8_t _portNumber;
};

class IRProximitySensor {
  public:
    void setVariables(uint8_t pin, uint8_t portNumber);
    int reading();
  private:
    uint8_t _pin;
    uint8_t _portNumber;
    bool _hardwareSetupComplete;
    void _setupHardware();
};

class FourDigitDisplay {
  public:
    void setVariables(AS_PIN_T _clockPin, AS_PIN_T _dataPin, uint8_t portNumber);
    void display(int value);
  private:
    AS_Four_Digit_Display_Arduino _disp;
    AS_PIN_T _clockPin;  // special datatype used by SULI
    AS_PIN_T _dataPin;   // special datatype used by SULI
    uint8_t _portNumber;
    void _setupHardware();
    bool _hardwareSetupComplete;
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
    IRProximitySensor IR;
    DigitalOutput electromagnet;
    FourDigitDisplay fourDigitDisplay;
    DigitalInput IRMotionSensor;
    AnalogInput UVSensor;
    DigitalOutput LEDString;
    void setVariables(uint8_t primaryPin, uint8_t secondaryPin, uint8_t portNumber);
  private:
    uint8_t _primaryPin;
    uint8_t _secondaryPin;
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
