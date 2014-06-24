/*
  Heater.cpp library - for controlling heaters
  Created by Christopher W. J. Palmer, 26 May 2014
  Part of the BrewBox Project
  Private library, not for public use.
*/

#include "Arduino.h"
#include "TemperatureSensor.h"
#include "OneWire.h"

TemperatureSensor::TemperatureSensor(int pin)
{
  _currentTemp = 0;

  pinMode(pin, INPUT);

  _pin = pin;
}

float TemperatureSensor::read()
{
  OneWire ds(_pin);
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

  _currentTemp = TemperatureSum;
  return _currentTemp;
}

float TemperatureSensor::currentTemp() {
  return _currentTemp;
}
