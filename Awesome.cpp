/*
  Awesome.h library - for the Awesome Shield Learning Platform
  Copyright Awesome Shield UG (haftungsbeschraenkt), all rights reserved
  MIT License
*/

#include "Arduino.h"
#include "Awesome.h"
#include "Wire.h"
#include "rgb_lcd.h"
#include <avr/pgmspace.h>
#include <Servo.h>

Awesome::Awesome() {
  LED.                setup(rgbRedPin, rgbGreenPin, rgbBluePin);
  lightSensor.        setVariables(lightSensorPin);
  knob.               setVariables(knobPin);
  temperatureSensor.  setup(tempSensorPin);
  button.             setVariables(buttonPin, LOW, true);
  toggleSwitch.       setVariables(switchOnPin, LOW, true);
  buzzer.             setVariables(buzzerPin);
  port1.              setPins(port1pin, port1pin);
  port2.              setPins(port2pin, port2pin);
}

port::port() {
}
void port::setPins(int primaryPin, int secondaryPin) {
  // set port pins
  _primaryPin = primaryPin;
  _secondaryPin = secondaryPin;
  // set add-on pins
  lightSensor.        setVariables(primaryPin);
  button.             setVariables(primaryPin, HIGH);
  buzzer.             setVariables(primaryPin);
  touchSensor.        setVariables(primaryPin, HIGH);
  singleColorLED.     setVariables(primaryPin);
  relay.              setVariables(primaryPin);
  knob.               setVariables(primaryPin);
  temperatureSensor.  setVariables(primaryPin);
  lightSensor.        setVariables(primaryPin);
  slider.             setVariables(primaryPin);
  servo.              setVariables(primaryPin);
  mic.                setVariables(primaryPin);
  ultrasonicRanger.   setVariables(primaryPin);
}

void led::setup(int redPin, int greenPin, int bluePin) {
  _setPins(redPin, greenPin, bluePin);
}
void led::_setPins (int redPin, int greenPin, int bluePin) {
  _redPin = redPin;
  _greenPin = greenPin;
  _bluePin = bluePin;
}
void led::turnOn(int color) {
  switch (color) {
    case RED:
      analogWrite(rgbRedPin,MAX);
      analogWrite(rgbGreenPin,0);
      analogWrite(rgbBluePin,0);
      _redSetting = 255;
      _greenSetting = 0;
      _blueSetting= 0;
      break;
    case GREEN:
      analogWrite(rgbRedPin,0);
      analogWrite(rgbGreenPin,MAX);
      analogWrite(rgbBluePin,0);
      _redSetting = 0;
      _greenSetting = 255;
      _blueSetting= 0;
      break;
    case BLUE:
      analogWrite(rgbRedPin,0);
      analogWrite(rgbGreenPin,0);
      analogWrite(rgbBluePin,MAX);
      _redSetting = 0;
      _greenSetting = 0;
      _blueSetting= 255;
      break;
    case YELLOW:
      analogWrite(rgbRedPin,MAX);
      analogWrite(rgbGreenPin,MAX);
      analogWrite(rgbBluePin,0);
      _redSetting = 255;
      _greenSetting = 255;
      _blueSetting= 0;
      break;
    case PURPLE:
      analogWrite(rgbRedPin,MAX);
      analogWrite(rgbGreenPin,0);
      analogWrite(rgbBluePin,MAX);
      _redSetting = 255;
      _greenSetting = 0;
      _blueSetting= 255;
      break;
    case CYAN:
      analogWrite(rgbRedPin,0);
      analogWrite(rgbGreenPin,MAX);
      analogWrite(rgbBluePin,MAX);
      _redSetting = 0;
      _greenSetting = 255;
      _blueSetting= 255;
      break;
    case ORANGE:
      analogWrite(rgbRedPin,255);
      analogWrite(rgbGreenPin,165);
      analogWrite(rgbBluePin,0);
      _redSetting = 255;
      _greenSetting = 165;
      _blueSetting= 0;
      break;
    case WHITE:
      analogWrite(rgbRedPin,255);
      analogWrite(rgbGreenPin,255);
      analogWrite(rgbBluePin,255);
      _redSetting = 255;
      _greenSetting = 255;
      _blueSetting= 255;
      break;
    default:
      Serial.println("Invalid input to LED.turnOn()");
  }
  _stateIsOn = true;
}
void led::turnOn(int howMuchRed, int howMuchGreen, int howMuchBlue) {
  //  zero negative inputs
  if (howMuchRed < 0) {
    howMuchRed = 0;
  }
  if (howMuchGreen < 0) {
    howMuchGreen = 0;
  }
  if (howMuchBlue < 0) {
    howMuchBlue = 0;
  }
  // turn on LEDs
  analogWrite(_redPin, howMuchRed);
  analogWrite(_greenPin, howMuchGreen);
  analogWrite(_bluePin, howMuchBlue);
  _stateIsOn = true;
}
void led::turnOff(int color) {
  switch (color) {
    case WHITE:
      digitalWrite(_redPin,LOW);
      digitalWrite(_greenPin,LOW);
      digitalWrite(_bluePin,LOW);
      _stateIsOn = false;
      break;
    case RED:
      digitalWrite(_redPin,LOW);
      break;
    case GREEN:
      digitalWrite(_greenPin,LOW);
      break;
    case BLUE:
      digitalWrite(_bluePin,LOW);
      break;
    default:
      Serial.println("Invalid input to LED.turnOff()");
  }
}
bool led::isOn() {
  return _stateIsOn;
}
bool led::isOff() {
  bool stateIsOff = ! _stateIsOn;
  return stateIsOff;
}
void led::flash(int duration, int howMuchRed, int howMuchGreen, int howMuchBlue){
  turnOn(howMuchRed, howMuchGreen, howMuchBlue);
  delay(duration);
  turnOff();
}

void LightSensor::setVariables(int pin) {
  _pin = pin;
  _hardwareSetupComplete = false;
}
int LightSensor::reading() {
  if ( ! _hardwareSetupComplete ) {
    _setupHardware();
  }
  return _read();
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

void Button::setVariables(int pin, bool readingMeaningButtonIsDown, bool needsPullup) {
  _pin = pin;
  _readingMeaningButtonIsDown = readingMeaningButtonIsDown;
  _needsPullup = needsPullup;
  _hardwareSetupComplete = false;
}
bool Button::isDown() {
  if ( ! _hardwareSetupComplete) {
    _setupHardware();
  }
  if ( _needsPullup ) {
    _setupPullup();
  }
  if (_readingMeaningButtonIsDown == HIGH) {
    return digitalRead(_pin);
  } else {
    return ! digitalRead(_pin);
  }
}
bool Button::isUp() {
    return ! isDown();
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
    noTone(_pin);
  }
}
void Buzzer::_setupHardware() {
  pinMode(_pin, OUTPUT);
  _hardwareSetupComplete = true;
}

void groveLCD::_setupHardware() {
  _lcd.begin(16, 2);
  delay(10);        // [ ] test to see if needed
}
void groveLCD::print(String message) {
  if ( ! _hardwareSetupComplete ) {
    _setupHardware();
  }
  _lcd.setCursor(0, 0);
  _lcd.print(message);
}

void DigitalInput::setVariables(int pin, bool stateThatMeansIsOn, bool needsPullup){
  _pin = pin;
  _stateThatMeansIsOn = stateThatMeansIsOn;
  _needsPullup = needsPullup;
  _hardwareSetupComplete = false;
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
void DigitalInput::_setupHardware() {
  pinMode(_pin, INPUT);
  _hardwareSetupComplete = true;
}

void DigitalOutput::setVariables(int pin) {
  _pin = pin;
  _hardwareSetupComplete = false;
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
void DigitalOutput::_setupHardware() {
  pinMode(_pin, OUTPUT);
  _hardwareSetupComplete = true;
}

void AnalogInput::setVariables(int pin) {
  _pin = pin;
  _hardwareSetupComplete = false;
}
int AnalogInput::reading() {
  // _value = 0;
  // // take 5 readings
  // for (int i; i < 5; i++) {
  //   _value = _value + analogRead(_pin);
  //   delay(2);
  // }
  // _value = (float)l_value / (float)l5; // THIS IS THE PROBLEM
  // // return average reading
  // return _value;
    // return analogRead(_pin);
    return analogRead(_pin);
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
