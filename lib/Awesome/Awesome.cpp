/*
  Awesome.cpp library - for reading Awesomes
  Created by Christopher W. J. Palmer, 26 May 2014
  Part of the BrewBox Project
  Private library, not for public use.
*/

#include "Arduino.h"
#include "Awesome.h"

#include <SD.h>                             //SD card library
#include <Wire.h>                           //One Wire library
#include "RTClib.h"                         //Real Time Clock library



Awesome::Awesome() {
  redLED.        setup(redLedPin);
  greenLED.      setup(greenLedPin);
  rgbLED.        setup(rgbRedPin, rgbGreenPin, rgbBluePin);
  lightSensor.   setup(lightSensorPin);
  button.        setup(buttonPin);
  toggle.        setup(switchOnPin);
  buzzer.        setup(buzzerPin);
  // pinMode(micPin,INPUT);
}

// for on/off ('I/O') LEDs
void ioLED::setup(int pin) {
  _setPin(pin);
}
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

void redGreenBlueLED::setup(int redPin, int greenPin, int bluePin) {
  _setPins(redPin, greenPin, bluePin);
}
void redGreenBlueLED::_setPins (int redPin, int greenPin, int bluePin) {
  _redPin = redPin;
  _greenPin = greenPin;
  _bluePin = bluePin;
}
void redGreenBlueLED::turnOn(int c1, int c2, int c3) {
  turnOff();
  if ( c1 >= 255 ) {
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
float TemperatureSensor::_read() {
  return analogRead(_pin);
}
int TemperatureSensor::read() {
  return _read();
}

void Switch::setup(int pin) {
  _pin = pin;
  pinMode(_pin, INPUT);
}
bool Switch::read() {
  return digitalRead(_pin);
}

void Buzzer::setup(int pin) {
  _pin = pin;
  pinMode(_pin, OUTPUT);
  _silent = false;
}
void Buzzer::beep(int millis) {
  if ( _silent ) {
    return;
  } else {
    tone(_pin, 400, millis);
  }
}
void Buzzer::setSilent(bool newState) {
  _silent = newState;
  noTone(_pin);
}

void DataLogger::setup(String headers) {
  _makeFile();

  //File dataFile = SD.open(file, FILE_WRITE);
  if (_dataFile) {
    _dataFile.print("date time (yyy/mm/dd hh:mm:ss), ");
    _dataFile.print(headers);
    _dataFile.println();
    _dataFile.close();
  } else {
    Serial.println("error copying data to CSV");
  }
  // setup RTC
  Wire.begin();
  if (!_RTC.begin()) {
    _dataFile.println("RTC failed");
    Serial.println("RTC failed");
  }
  if (! _RTC.isrunning()) {
      Serial.println("RTC is NOT running!");
      // following line sets the RTC to the date & time this sketch was compiled
      // uncomment it & upload to set the time, date and start run the RTC!
      _RTC.adjust(DateTime(__DATE__, __TIME__));
  }
}
void DataLogger::log(String row) {
  File dataFile = SD.open(_filename, FILE_WRITE);
  DateTime now = _RTC.now();
  if (dataFile) {
    // print date-time
    dataFile.print(now.year(), DEC);
    dataFile.print('/');
    dataFile.print(now.month(), DEC);
    dataFile.print('/');
    dataFile.print(now.day(), DEC);
    dataFile.print(' ');
    dataFile.print(now.hour(), DEC);
    dataFile.print(':');
    dataFile.print(now.minute(), DEC);
    dataFile.print(':');
    dataFile.print(now.second(), DEC);
    dataFile.print(", ");
    // print data
    dataFile.print(row);
    dataFile.println();
    dataFile.close();
  } else {
    Serial.println("error copying data to CSV");
  }
}
void DataLogger::printFileName() {
  Serial.print("_filename is: ");
  Serial.println(_filename);
  Serial.println();
}
void DataLogger::_error(char *str) {
  Serial.print("error: ");
  Serial.println(str);
  // red LED indicates error
  digitalWrite(SDRedLEDPin, HIGH);
  // stop here and wait
  while( true );
}
void DataLogger::_makeFile() {
  char * filenameptr = _filename;

  //_filename = "DATAF000.CSV";

  // char & filenameRef = *file;
  //filenameRef = 'a';  // this does change the _filename, but only works with a single char

  /* SET _filename */
  // string containing desired file name
  String initialFileNameString = "DATAF000.csv";
  // char array to store file name
  char initialFileNameArray[13];
  // write contents of string to array
  initialFileNameString.toCharArray(initialFileNameArray,13);
  // write contents of array to _filename
  for (int i=0; i<initialFileNameString.length(); i++) {
    *(filenameptr+i) = initialFileNameArray[i];
  }

  // initialize the SD card
  if ( !SD.begin() ) {
    _error("Card failed, or not present");
  }
  Serial.println("card initialized.");

  for (uint8_t i = 0; i < 100000; i++) {
    if ( i < 10 ) {
      filenameptr[7] = i + '0';
    } else if ( i < 100 ) {
      filenameptr[6] = i/10 + '0';
      filenameptr[7] = i%10 + '0';
    } else if ( i < 1000) {
      filenameptr[5] = i/100 + '0';
      filenameptr[6] = i%100/10 + '0';
      filenameptr[7] = i%100%10 + '0';
    } else {
      Serial.println();
      Serial.println("ran out of file names");
      Serial.println();
    }
    if ( ! SD.exists(filenameptr) ) {
      // only open a new file if it doesn't exist
      _dataFile = SD.open(filenameptr, FILE_WRITE);
      break;  // leave the loop
    }
  }

  if ( ! _dataFile ) {
    _error("couldnt create file");
  }
  Serial.print("Logging to: ");
  Serial.println(filenameptr);
}

int Awesome::micRead() {
  return analogRead(micPin);
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

void Awesome::_allOkay() {
  // flash green 3 times
  for ( int i = 0; i <= 2; i++ ) {
    greenLED.turnOn();
    rgbLED.turnOn(GREEN);
    delay(300);
    greenLED.turnOff();
    rgbLED.turnOff();
    delay(150);
  }
}

void Awesome::diagnostic() {
  _LedsFlash(500);
  _LedsCycle();
  _LedsTurnOff();

  buzzer.beep(500);
  delay(500);

  Serial.print("Light reading = ");
  Serial.println(lightSensor.read());

  Serial.print("Temperature reading = ");
  Serial.println(temperatureSensor.read());
  Serial.println();

  // Serial.println(micReading());
  // delay(1000);

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
  bool initialSwitchState = toggle.read();
  redLED.turnOn();
  while (toggle.read() == initialSwitchState) {
    // wait
  }
  redLED.turnOff();
  greenLED.turnOn();
  delay(1000);
  greenLED.turnOff();

  _allOkay();
}
