/*
  Awesome.cpp library - for reading Awesomes
  Created by Christopher W. J. Palmer, 26 May 2014
  Part of the BrewBox Project
  Private library, not for public use.
*/

#include "Arduino.h"
#include "OneWire.h"
#include "Awesome.h"

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

Awesome::Awesome()
{
  redLED.setup(redLedPin);
  greenLED.setup(greenLedPin);
  pinMode(rgbRedPin,OUTPUT);
  pinMode(rgbGreenPin,OUTPUT);
  pinMode(rgbBluePin,OUTPUT);
  //pinMode(redLedPin,OUTPUT);
  pinMode(greenLedPin,OUTPUT);

  pinMode(buzzerPin,OUTPUT);

  pinMode(buttonPin,INPUT);
  pinMode(switchOnPin,INPUT);

  pinMode(lightSensorPin,INPUT);
  pinMode(tempSensorPin,INPUT);
  pinMode(micPin,INPUT);
}

int Awesome::lightRead() {
  return analogRead(lightSensorPin);
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

bool Awesome::buttonRead() {
  return _buttonIsPressed();
}

bool Awesome::_buttonIsPressed() {
  return digitalRead(buttonPin);
}

void Awesome::rgbLedOn(int c1, int c2, int c3) {
  rgbLedOff();
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
      analogWrite(rgbRedPin, c1);
    }
    if (c2 != 0) {
      analogWrite(rgbGreenPin, c2);
    }
    if (c3 != 0) {
      analogWrite(rgbBluePin, c3);
    }
  }
}

void Awesome::rgbLedOff() {
  digitalWrite(rgbRedPin,LOW);
  digitalWrite(rgbGreenPin,LOW);
  digitalWrite(rgbBluePin,LOW);
}

void Awesome::redLedOn() {
  digitalWrite(redLedPin,HIGH);
}
void Awesome::redLedOff() {
  digitalWrite(redLedPin,LOW);
}
void Awesome::greenLedOn() {
  digitalWrite(greenLedPin,HIGH);
}
void Awesome::greenLedOff() {
  digitalWrite(greenLedPin,LOW);
}

void Awesome::beep(int millis) {
  tone(buzzerPin, 400, millis);
}

float Awesome::tempRead() {
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

void Awesome::diagnostic() {
  _LedsFlash(500);
  _LedsCycle();

  beep(500);

  if (buttonRead()) {
    greenLedOn();
    redLedOff();
  } else {
    greenLedOff();
    redLedOn();
  }
  delay(1500);
  if (switchRead()) {
    greenLedOn();
    redLedOff();
  } else {
    greenLedOff();
    redLedOn();
  }

  delay(1500);

  Serial.println(lightRead());

  Serial.println(tempRead());
  Serial.println();

  _LedsTurnOff();

  // Serial.println(micReading());
  // delay(1000);
}

void Awesome::_LedsFlash(int millis) {
  _LedsTurnOn();
  delay(millis);
  _LedsTurnOff();
}

void Awesome::_LedsTurnOn() {
  digitalWrite(rgbRedPin,HIGH);
  digitalWrite(rgbGreenPin,HIGH);
  digitalWrite(rgbBluePin,HIGH);
  digitalWrite(redLedPin,HIGH);
  digitalWrite(greenLedPin,HIGH);
}

void Awesome::_LedsTurnOff() {
  digitalWrite(rgbRedPin,LOW);
  digitalWrite(rgbGreenPin,LOW);
  digitalWrite(rgbBluePin,LOW);
  digitalWrite(redLedPin,LOW);
  digitalWrite(greenLedPin,LOW);
}

void Awesome::_LedsCycle() {
  rgbLedOn(RED);
  delay(150);
  rgbLedOn(GREEN);
  delay(150);
  rgbLedOn(BLUE);
  delay(150);
  rgbLedOn(CYAN);
  delay(150);
  rgbLedOn(YELLOW);
  delay(150);
  rgbLedOn(MAGENTA);
  delay(150);
  rgbLedOn(WHITE);
  delay(150);
  digitalWrite(redLedPin,HIGH);
  delay(150);
  digitalWrite(redLedPin,LOW);
  delay(150);
  digitalWrite(greenLedPin,HIGH);
  delay(150);
  digitalWrite(greenLedPin,LOW);
  delay(150);
}
