/*
  Awesome.h library - for the Awesome Shield Learning Platform
  Copyright Awesome Shield UG (haftungsbeschraenkt), all rights reserved
  MIT License
*/

// include other libraries
#include "Arduino.h"
#include "Awesome.h"
#include "Wire.h"
//#include "rgb_lcd.h"
#include <avr/pgmspace.h>
#include <Servo.h>
#include <Adafruit_NeoPixel.h>

void printer(String componentName, int value) {
  Serial.print("The ");
  Serial.print(componentName);
  Serial.print(" reading is ");
  Serial.println(value);
}
void printer(String componentName, float value) {
  Serial.print("The ");
  Serial.print(componentName);
  Serial.print(" reading is ");
  Serial.println(value);
}
void printer(String componentName, bool value) {
  Serial.print("The ");
  Serial.print(componentName);
  if ( value == true) {
    Serial.println(" is on.");
  } else {
    Serial.println(" is off.");
  }
}

// when the awesome object gets created...
Awesome::Awesome() {
  // do setup for all core board components
  LED.                setup();
  lightSensor.        setVariables(lightSensorPin, "lightSensor", 0);
  knob.               setVariables(knobPin, "knob", 0);
  button.             setVariables(buttonPin, LOW, true, 0);
  toggleSwitch.       setVariables(switchOnPin, LOW, "toggleSwitch", true);
  buzzer.             setVariables(buzzerPin);
  port1.              setVariables(port1PrimaryPin, port1SecondaryPin, 1);
  port2.              setVariables(port2PrimaryPin, port2SecondaryPin, 2);
  port3.              setVariables(port3PrimaryPin, port3SecondaryPin, 3);
}
void Awesome::setup(int baudRate) {
  LED.turnOff();
  Serial.begin(baudRate);
}

port::port() {
}
void port::setVariables(int primaryPin, int secondaryPin, uint8_t portNumber) {
  // set port pins
  _primaryPin = primaryPin;
  _secondaryPin = secondaryPin;
  _portNumber = portNumber;
  // set add-on pins
  lightSensor.        setVariables(_primaryPin,  "lightSensor", _portNumber);
  button.             setVariables(_primaryPin, HIGH, false, _portNumber);
  buzzer.             setVariables(_primaryPin);
  touchSensor.        setVariables(_primaryPin, HIGH, "touchSensor");
  singleColorLED.     setVariables(_primaryPin, "single LED");
  relay.              setVariables(_primaryPin, "relay");
  knob.               setVariables(_primaryPin, "knob", _portNumber);
  temperatureSensor.  setVariables(_primaryPin, "temperatureSensor", _portNumber);
  slider.             setVariables(_primaryPin, "slider", _portNumber);
  servo.              setVariables(_primaryPin);
  mic.                setVariables(_primaryPin);
  sonicSensor.        setVariables(_primaryPin);
  IR.                 setVariables(_secondaryPin);
  electromagnet.      setVariables(_primaryPin, "electromagnet");
}

void led::setup() {
  _pixel.begin();
}
void led::_update() {
  // set color
  _pixel.setPixelColor(0, _pixel.Color(_redSetting, _greenSetting, _blueSetting));
  // turn on LED
  _pixel.show();
}
void led::turnOn(int color) {
  switch (color) {
    case RED:
      _redSetting = 255;
      _greenSetting = 0;
      _blueSetting= 0;
      break;
    case GREEN:
      _redSetting = 0;
      _greenSetting = 255;
      _blueSetting= 0;
      break;
    case BLUE:
      _redSetting = 0;
      _greenSetting = 0;
      _blueSetting= 255;
      break;
    case YELLOW:
      _redSetting = 255;
      _greenSetting = 255;
      _blueSetting= 0;
      break;
    case PURPLE:
      _redSetting = 255;
      _greenSetting = 0;
      _blueSetting= 255;
      break;
    case CYAN:
      _redSetting = 0;
      _greenSetting = 255;
      _blueSetting= 255;
      break;
    // case ORANGE:
    //   analogWrite(rgbRedPin,255);
    //   analogWrite(rgbGreenPin,165);
    //   analogWrite(rgbBluePin,0);
    //   _redSetting = 255;
    //   _greenSetting = 165;
    //   _blueSetting= 0;
    //   break;
    case WHITE:
      _redSetting = 255;
      _greenSetting = 255;
      _blueSetting = 255;
      break;
    default:
      Serial.println("Invalid input to LED.turnOn()");
  }
  _update();
}
void led::turnOn(int red, int green, int blue) {
  // make sure inputs are in acceptable range
  _redSetting = constrain(red,0,MAX);
  _greenSetting = constrain(green,0,MAX);
  _blueSetting = constrain(blue,0,MAX);
  _update();
}
void led::turnOff(int color) {
  switch (color) {
    case WHITE:
      _redSetting = 0;
      _greenSetting = 0;
      _blueSetting= 0;
      break;
    case RED:
      _redSetting = 0;
      break;
    case GREEN:
      _greenSetting = 0;
      break;
    case BLUE:
      _blueSetting= 0;
      break;
    default:
      Serial.println("Invalid input to LED.turnOff()");
  }
  _update();
}
bool led::isOn() {
  if ( _redSetting != 0 || _greenSetting != 0 || _blueSetting != 0 ) {
    return true;
  } else {
    return false;
  }
}
bool led::isOff() {
  return ! isOn();
}

void LightSensor::setVariables(int pin, String componentName, uint8_t port) {
  _pin = pin;
  _port = port;
  _hardwareSetupComplete = false;
}
int LightSensor::reading() {
  if ( ! _hardwareSetupComplete ) {
    _setupHardware();
  }
  return _read();
}
void LightSensor::print() {
  printer("lightSensor", reading());
}
void LightSensor::_setupHardware() {
  pinMode(_pin,INPUT);
  _hardwareSetupComplete = true;
}
int LightSensor::_read() {
  return analogRead(_pin);
}

void TemperatureSensor::setup(int pin) {
  _pin = pin;
  pinMode(_pin,INPUT);
}
float TemperatureSensor::_read() {
  int numData=5;
  int rawData[numData-1];
  for (short i=0;i<numData;i++) {
    rawData[i] = analogRead(_pin);
    // Serial.print("rawData[i] = ");
    // Serial.println(rawData[i]);
    delay(10);
  }
  int averageData = 0;
  for (short i=0;i<numData;i++) {
    averageData += rawData[i];
  }
  averageData = averageData / numData;

  float result = log(10000.0/(1024.0/averageData-1));
  result = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * result * result ))* result );
  result = result - 273.15;

  return result;
}
float TemperatureSensor::reading() {
  return _read();
}
void TemperatureSensor::print() {
  printer("tempereSensor", reading());
}

void Button::setVariables(int pin, bool readingMeaningButtonIsDown, bool needsPullup, int portNumber ) {
  _pin = pin;
  _readingMeaningButtonIsDown = readingMeaningButtonIsDown;
  _needsPullup = needsPullup;
  _hardwareSetupComplete = false;
  _portNumber = portNumber;
}
bool Button::isDown() {
  if ( ! _hardwareSetupComplete ) {
    _setupHardware();
  }
  if ( _needsPullup ) {
    _setupPullup();
  }
  if (_readingMeaningButtonIsDown == HIGH ) {
    return digitalRead(_pin);
  } else {
    return ! digitalRead(_pin);
  }
}
bool Button::isUp() {
    return ! isDown();
}
void Button::print() {
  // specialized print function for buttons
  Serial.print("The button");
  if ( _portNumber != 0) {
    Serial.print(" connected to port");
    Serial.print(_portNumber);
  }
  if ( isUp() ) {
    Serial.println(" is up.");
  } else {
    Serial.println(" is down.");
  }
}
void Button::_setupHardware() {
  pinMode(_pin, INPUT);
  _hardwareSetupComplete = true;
}
void Button::_setupPullup() {
  pinMode(_pin,OUTPUT);
  digitalWrite(_pin,HIGH);
  pinMode(_pin,INPUT);
}

void Buzzer::setVariables(int pin) {
  _pin = pin;
  _silent = false;
  bool _hardwareSetupComplete = false;
}
void Buzzer::turnOn(unsigned int frequency) {
  if ( ! _hardwareSetupComplete ) {
    _setupHardware();
  }
  if ( ! _silent ) {
    tone(_pin, frequency);
    _stateIsOn = true;
  }
}
void Buzzer::turnOff() {
  if ( ! _hardwareSetupComplete ) {
    _setupHardware();
  }
  noTone(_pin);
  _stateIsOn = false;
}
bool Buzzer::isOn() {
  return _stateIsOn;
}
bool Buzzer::isOff() {
  return ! _stateIsOn;
}
void Buzzer::beep(unsigned long millis, unsigned int frequency) {
  if ( _silent ) {
    return;
  } else {
    turnOn(frequency);
    delay(millis);
    turnOff();
  }
}
void Buzzer::setSilentMode(bool newState) {
  _silent = newState;
  if ( _silent ) {
    turnOff();
  }
}
void Buzzer::_setupHardware() {
  pinMode(_pin, OUTPUT);
  _hardwareSetupComplete = true;
}

// void groveLCD::_setupHardware() {
//   _lcd.begin(16, 2);
//   delay(10);        // [ ] test to see if needed
// }
// void groveLCD::print(String message) {
//   if ( ! _hardwareSetupComplete ) {
//     _setupHardware();
//   }
//   _lcd.setCursor(0, 0);
//   _lcd.print(message);
// }

void DigitalInput::setVariables(int pin, bool stateThatMeansIsOn, String componentName, bool needsPullup){
  _pin = pin;
  _stateThatMeansIsOn = stateThatMeansIsOn;
  _needsPullup = needsPullup;
  _hardwareSetupComplete = false;
  _componentName = componentName;
}
bool DigitalInput::isOn(){
  if ( ! _hardwareSetupComplete ) {
    _setupHardware();
  }
  if ( _needsPullup ) {
    pinMode(_pin,OUTPUT);
    digitalWrite(_pin,HIGH);
    pinMode(_pin,INPUT);
  }
  if ( _stateThatMeansIsOn == HIGH) {
    return digitalRead(_pin);
  } else {
    return ! digitalRead(_pin);
  }
}
bool DigitalInput::isOff(){
  return ! isOn();
}
void DigitalInput::print() {
  printer(_componentName, isOn());
}
void DigitalInput::_setupHardware() {
  pinMode(_pin, INPUT);
  _hardwareSetupComplete = true;
}

void DigitalOutput::setVariables(int pin, String name) {
  _pin = pin;
  _hardwareSetupComplete = false;
  _componentName = name;
}
void DigitalOutput::turnOn() {
  if ( ! _hardwareSetupComplete ) {
    _setupHardware();
  }
  digitalWrite(_pin, HIGH);
  _stateIsOn = true;
}
void DigitalOutput::turnOff() {
  if ( ! _hardwareSetupComplete ) {
    _setupHardware();
  }
  digitalWrite(_pin, LOW);
  _stateIsOn = false;
}
bool DigitalOutput::isOn() {
  return _stateIsOn;
}
bool DigitalOutput::isOff() {
  return ! _stateIsOn;
}
void DigitalOutput::print() {
  printer(_componentName, isOn());
}
void DigitalOutput::_setupHardware() {
  pinMode(_pin, OUTPUT);
  _hardwareSetupComplete = true;
}

void AnalogInput::setVariables(int pin, String componentName, uint8_t portNumber) {
  _pin = pin;
  _portNumber = portNumber;
  _hardwareSetupComplete = false;
  _componentName = componentName;
}
int AnalogInput::reading() {
  _value = 0;
  // take 5 readings
  for (int i = 0; i < 5; i++) {
    _value = _value + analogRead(_pin);
    delay(2);
  }
  _value = (float)_value / (float)5; // problem fixed?
  // return average reading
  return _value;
}
void AnalogInput::print() {
  printer(_componentName, reading());
}
void AnalogInput::_setupHardware() {
  pinMode(_pin,INPUT);
  _hardwareSetupComplete = true;
}

void AnalogOutput::setVariables(int pin) {
  _pin = pin;
  _hardwareSetupComplete = false;
}
void AnalogOutput::set(int newSetting) {
  if ( ! _hardwareSetupComplete ) {
    _setupHardware();
  }
  analogWrite(_pin, newSetting);
  _currentSetting = newSetting;
}
int AnalogOutput::setting() {
  return _currentSetting;
}
void AnalogOutput::_setupHardware() {
  pinMode(_pin,OUTPUT);
  _hardwareSetupComplete = true;
}

void SERVO::setVariables(int pin){
  _pin = pin;
  _hardwareSetupComplete = false;
}
void SERVO::setPosition(int position) {
  if ( ! _hardwareSetupComplete ) {
    _setupHardware();
  }
  _servo.write(position);
}
void SERVO::_setupHardware() {
  _servo.attach(_pin);
  _hardwareSetupComplete = true;
}

void electretMic::setVariables(int pin) {
  _pin = pin;
  _hardwareSetupComplete = false;
}
int electretMic::reading() {
  if ( ! _hardwareSetupComplete ) {
    _setupHardware();
  }
  int threshhold = 85;
  int loops = 15;
  int value = 0;
  // take the sum of some readings
  for (int i=0; i<loops; i++) {
    value += analogRead(_pin);
    delay(1);
  }
  // find the average reading
  value = float(value) / loops;
  // high pass filter to decrease noise
  value = value - threshhold;
  // map new value to normal analog reading range
  map(value,0,1023-threshhold-600,0,1023);
  // make sure value stays within expected range
  value = constrain(value,0,1023);
  return value;
}
void electretMic::_setupHardware() {
  pinMode(_pin, INPUT);
  _hardwareSetupComplete = true;
}

void UltrasonicRanger::setVariables(int pin) {
  _pin = pin;
}
int UltrasonicRanger::reading() {
  // send a request for data
  pinMode(_pin, OUTPUT);
	digitalWrite(_pin, LOW);
	delayMicroseconds(2);
	digitalWrite(_pin, HIGH);
	delayMicroseconds(5);
	digitalWrite(_pin,LOW);
	pinMode(_pin,INPUT);
  // record the duration of the pulse
	long duration;
	duration = pulseIn(_pin,HIGH);
  // calculate the range, in centimeters
	long range;
	range = duration/29/2;
	return range;
}

void IRProximitySensor::setVariables(int pin) {
  _pin = pin;
  _hardwareSetupComplete = false;
}
void IRProximitySensor::_setupHardware() {
  pinMode(_pin,INPUT);
  _hardwareSetupComplete = true;
}
int IRProximitySensor::reading() {
  if ( ! _hardwareSetupComplete ) {
    _setupHardware();
  }
  return analogRead(_pin);
}
