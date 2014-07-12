/*
  Awesome.cpp library - for reading Awesomes
  Created by Christopher W. J. Palmer, 26 May 2014
  Part of the BrewBox Project
  Private library, not for public use.
*/

#include "Arduino.h"
#include "OneWire.h"
#include "Awesome.h"

// for on/off ('I/O') LEDs
void ioLED::turnOn() {
  digitalWrite(_pin,HIGH);
}
void ioLED::turnOff() {
  digitalWrite(_pin,LOW);
}
void ioLED::_setPin(int pin) {
  _pin = pin;
  pinMode(_pin,OUTPUT);
}
void ioLED::setup(int pin) {
  _setPin(pin);
}

void redGreenBlueLED::turnOn(int c1, int c2, int c3) {
  turnOff();
  if (c1 >= 255) {
    switch (c1) {
      case RED:
        digitalWrite(rgbRedPin,HIGH);
        digitalWrite(rgbGreenPin,LOW);
        digitalWrite(rgbBluePin,LOW);
        break;
      case GREEN:
        digitalWrite(rgbRedPin,LOW);
        digitalWrite(rgbGreenPin,HIGH);
        digitalWrite(rgbBluePin,LOW);
        break;
      case BLUE:
        digitalWrite(rgbRedPin,LOW);
        digitalWrite(rgbGreenPin,LOW);
        digitalWrite(rgbBluePin,HIGH);
        break;
      case YELLOW:
        digitalWrite(rgbRedPin,HIGH);
        digitalWrite(rgbGreenPin,HIGH);
        digitalWrite(rgbBluePin,LOW);
        break;
      case MAGENTA:
        digitalWrite(rgbRedPin,HIGH);
        digitalWrite(rgbGreenPin,LOW);
        digitalWrite(rgbBluePin,HIGH);
        break;
      case CYAN:
        digitalWrite(rgbRedPin,LOW);
        digitalWrite(rgbGreenPin,HIGH);
        digitalWrite(rgbBluePin,HIGH);
        break;
      case WHITE:
        digitalWrite(rgbRedPin,HIGH);
        digitalWrite(rgbGreenPin,HIGH);
        digitalWrite(rgbBluePin,HIGH);
        break;
      default:
        Serial.println("Invalid input");
    }
  } else {
    if (c1 != 0) {
      analogWrite(_redPin, c1);
    }
    if (c2 != 0) {
      analogWrite(_greenPin, c2);
    }
    if (c3 != 0) {
      analogWrite(_bluePin, c3);
    }
  }
}
void redGreenBlueLED::turnOff() {
  digitalWrite(_redPin,LOW);
  digitalWrite(_greenPin,LOW);
  digitalWrite(_bluePin,LOW);
}
void redGreenBlueLED::_setPins (int redPin, int greenPin, int bluePin) {
  _redPin = redPin;
  _greenPin = greenPin;
  _bluePin = bluePin;
}
void redGreenBlueLED::setup(int redPin, int greenPin, int bluePin) {
  _setPins(redPin, greenPin, bluePin);
}

void LightSensor::setup(int pin) {
  _pin = pin;
  pinMode(_pin,INPUT);
}
int LightSensor::read() {
  return analogRead(_pin);
}

void TemperatureSensor::setup(int pin) {
  _pin = pin;
  pinMode(_pin,INPUT);
}
float TemperatureSensor::_tempRead() {
  OneWire ds(tempSensorPin);
  //returns the temperature from one DS18S20 in DEG Celsius

  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
      //no more sensors on chain, reset search
      ds.reset_search();
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Device is not recognized");
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); // start conversion, with parasite power on at the end

  byte present = ds.reset();
  ds.select(addr);
  ds.write(0xBE); // Read Scratchpad

  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds.read();
  }

  ds.reset_search();

  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;

  return TemperatureSum;
}
float TemperatureSensor::read() {
  return _tempRead();
}

void Button::setup(int pin) {
  _pin = pin;
  pinMode(_pin, INPUT);
}
bool Button::read() {
  return digitalRead(_pin);
}

int Awesome::micRead() {
  return analogRead(micPin);
}

bool Awesome::switchRead() {
  return _switchIsOn();
}

bool Awesome::_switchIsOn() {
  return digitalRead(switchOnPin);
}

void Awesome::beep(int millis) {
  tone(buzzerPin, 400, millis);
}

void Awesome::_LedsFlash(int millis) {
  _LedsTurnOn();
  delay(millis);
  _LedsTurnOff();
}

void Awesome::_LedsTurnOn() {
  rgbLED.turnOn(WHITE);
  redLED.turnOn();
  greenLED.turnOn();
}

void Awesome::_LedsTurnOff() {
  rgbLED.turnOff();
  redLED.turnOff();
  greenLED.turnOff();
}

void Awesome::_LedsCycle() {
  rgbLED.turnOn(RED);
  delay(150);
  rgbLED.turnOn(GREEN);
  delay(150);
  rgbLED.turnOn(BLUE);
  delay(150);
  rgbLED.turnOn(CYAN);
  delay(150);
  rgbLED.turnOn(YELLOW);
  delay(150);
  rgbLED.turnOn(MAGENTA);
  delay(150);
  rgbLED.turnOn(WHITE);
  delay(150);
  redLED.turnOn();
  delay(150);
  redLED.turnOff();
  delay(150);
  greenLED.turnOn();
  delay(150);
  greenLED.turnOff();
  delay(150);
}

Awesome::Awesome() {
  redLED.      setup(redLedPin);
  greenLED.    setup(greenLedPin);
  rgbLED.      setup(rgbRedPin, rgbGreenPin, rgbBluePin);
  lightSensor. setup(lightSensorPin);
  button.      setup(buttonPin);

  pinMode(buzzerPin,OUTPUT);

  pinMode(switchOnPin,INPUT);

  pinMode(tempSensorPin,INPUT);
  pinMode(micPin,INPUT);
}

void Awesome::diagnostic() {
  _LedsFlash(500);
  _LedsCycle();
  _LedsTurnOff();

  beep(500);

  // flash green LED once button is pushed
  redLED.turnOn();
  while ( ! button.read() ) {
    // wait
  }
  redLED.turnOff();
  greenLED.turnOn();
  delay(1000);
  greenLED.turnOff();

  delay(500);

  // flash green LED once switch is flipped
  bool initialSwitchState = switchRead();
  redLED.turnOn();
  while (switchRead() == initialSwitchState) {
    // wait
  }
  redLED.turnOff();
  greenLED.turnOn();
  delay(1000);
  greenLED.turnOff();

  delay(500);

  Serial.println(lightSensor.read());

  Serial.println(temperatureSensor.read());
  Serial.println();

  // Serial.println(micReading());
  // delay(1000);
}
