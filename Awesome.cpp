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


// temperature data table for 10k thermistor with a 10k pull down resistor
const int temps[] PROGMEM = { 0, 1, 2, 3, 4, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 143, 144, 145, 146, 147, 148, 149, 150, 151, 151, 152, 153, 154, 155, 156, 157, 158, 159, 159, 160, 161, 162, 163, 164, 165, 166, 167, 167, 168, 169, 170, 171, 172, 173, 174, 175, 175, 176, 177, 178, 179, 180, 181, 182, 182, 183, 184, 185, 186, 187, 188, 189, 190, 190, 191, 192, 193, 194, 195, 196, 197, 197, 198, 199, 200, 201, 202, 203, 204, 205, 205, 206, 207, 208, 209, 210, 211, 212, 212, 213, 214, 215, 216, 217, 218, 219, 220, 220, 221, 222, 223, 224, 225, 226, 227, 228, 228, 229, 230, 231, 232, 233, 234, 235, 235, 236, 237, 238, 239, 240, 241, 242, 243, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 252, 253, 254, 255, 256, 257, 258, 259, 260, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 269, 270, 271, 272, 273, 274, 275, 276, 277, 278, 279, 279, 280, 281, 282, 283, 284, 285, 286, 287, 288, 289, 289, 290, 291, 292, 293, 294, 295, 296, 297, 298, 299, 300, 301, 301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312, 313, 314, 315, 315, 316, 317, 318, 319, 320, 321, 322, 323, 324, 325, 326, 327, 328, 329, 330, 331, 332, 333, 334, 335, 335, 336, 337, 338, 339, 340, 341, 342, 343, 344, 345, 346, 347, 348, 349, 350, 351, 352, 353, 354, 355, 356, 357, 358, 359, 360, 361, 362, 363, 364, 365, 366, 367, 368, 369, 370, 371, 372, 373, 374, 375, 376, 377, 378, 379, 380, 381, 382, 383, 384, 385, 386, 387, 388, 389, 390, 392, 393, 394, 395, 396, 397, 398, 399, 400, 401, 402, 403, 404, 405, 406, 407, 408, 410, 411, 412, 413, 414, 415, 416, 417, 418, 419, 420, 422, 423, 424, 425, 426, 427, 428, 429, 430, 432, 433, 434, 435, 436, 437, 438, 439, 441, 442, 443, 444, 445, 446, 448, 449, 450, 451, 452, 453, 455, 456, 457, 458, 459, 460, 462, 463, 464, 465, 466, 468, 469, 470, 471, 472, 474, 475, 476, 477, 479, 480, 481, 482, 484, 485, 486, 487, 489, 490, 491, 492, 494, 495, 496, 498, 499, 500, 501, 503, 504, 505, 507, 508, 509, 511, 512, 513, 515, 516, 517, 519, 520, 521, 523, 524, 525, 527, 528, 530, 531, 532, 534, 535, 537, 538, 539, 541, 542, 544, 545, 547, 548, 550, 551, 552, 554, 555, 557, 558, 560, 561, 563, 564, 566, 567, 569, 570, 572, 574, 575, 577, 578, 580, 581, 583, 585, 586, 588, 589, 591, 593, 594, 596, 598, 599, 601, 603, 604, 606, 608, 609, 611, 613, 614, 616, 618, 620, 621, 623, 625, 627, 628, 630, 632, 634, 636, 638, 639, 641, 643, 645, 647, 649, 651, 653, 654, 656, 658, 660, 662, 664, 666, 668, 670, 672, 674, 676, 678, 680, 683, 685, 687, 689, 691, 693, 695, 697, 700, 702, 704, 706, 708, 711, 713, 715, 718, 720, 722, 725, 727, 729, 732, 734, 737, 739, 741, 744, 746, 749, 752, 754, 757, 759, 762, 764, 767, 770, 773, 775, 778, 781, 784, 786, 789, 792, 795, 798, 801, 804, 807, 810, 813, 816, 819, 822, 825, 829, 832, 835, 838, 842, 845, 848, 852, 855, 859, 862, 866, 869, 873, 877, 881, 884, 888, 892, 896, 900, 904, 908, 912, 916, 920, 925, 929, 933, 938, 942, 947, 952, 956, 961, 966, 971, 976, 981, 986, 991, 997, 1002, 1007, 1013, 1019, 1024, 1030, 1036, 1042, 1049, 1055, 1061, 1068, 1075, 1082, 1088, 1096, 1103, 1110, 1118, 1126, 1134, 1142, 1150, 1159, 1168, 1177, 1186, 1196, 1206, 1216, 1226, 1237, 1248, 1260, 1272, 1284, 1297, 1310, 1324, 1338, 1353, 1369, 1385, 1402, 1420, 1439, 1459, 1480, 1502 };

Awesome::Awesome() {
  LED.                setup(rgbRedPin, rgbGreenPin, rgbBluePin);
  lightSensor.        setVariables(lightSensorPin);
  knob.               setup(knobPin);
  temperatureSensor.  setup(tempSensorPin);
  button.             setup(buttonPin, LOW, true);
  toggleSwitch.       setup(switchOnPin, LOW, true);
  buzzer.             setup(buzzerPin);
  port1.              setPins(port1pin, port1pin);
  port2.              setPins(port2pin, port2pin);
}

port::port() {
}
void port::setPins(int primaryPin, int secondaryPin) {
  // set port pins
  _primaryPin = primaryPin;
  _secondaryPin = secondaryPin;
  // set ad-on pins
  lightSensor.        setVariables(primaryPin);
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
      break;
    case GREEN:
      analogWrite(rgbRedPin,0);
      analogWrite(rgbGreenPin,MAX);
      analogWrite(rgbBluePin,0);
      break;
    case BLUE:
      analogWrite(rgbRedPin,0);
      analogWrite(rgbGreenPin,0);
      analogWrite(rgbBluePin,MAX);
      break;
    case YELLOW:
      analogWrite(rgbRedPin,MAX);
      analogWrite(rgbGreenPin,MAX);
      analogWrite(rgbBluePin,0);
      break;
    case PURPLE:
      analogWrite(rgbRedPin,MAX);
      analogWrite(rgbGreenPin,0);
      analogWrite(rgbBluePin,MAX);
      break;
    case CYAN:
      analogWrite(rgbRedPin,0);
      analogWrite(rgbGreenPin,MAX);
      analogWrite(rgbBluePin,MAX);
      break;
    case WHITE:
      analogWrite(rgbRedPin,255);
      analogWrite(rgbGreenPin,255);
      analogWrite(rgbBluePin,255);
      break;
    default:
      Serial.println("Invalid input");
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
void led::turnOff() {
  digitalWrite(_redPin,LOW);
  digitalWrite(_greenPin,LOW);
  digitalWrite(_bluePin,LOW);
  _stateIsOn = false;
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
  int therm;
  therm = averageData-238;
  therm=pgm_read_word(&temps[therm]);
  float result = therm;
  result = result / 10;
  return result;
}
float TemperatureSensor::reading() {
  return _read();
}

void Button::setup(int pin, bool readingMeaningButtonIsDown, bool needsPullup) {
  _pin = pin;
  _readingMeaningButtonIsDown = readingMeaningButtonIsDown;
  _needsPullup = needsPullup;
  pinMode(_pin, INPUT);
}
bool Button::isDown() {
  if ( _needsPullup ) {
    pinMode(_pin,OUTPUT);
    digitalWrite(_pin,HIGH);
    pinMode(_pin,INPUT);
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

void Buzzer::setup(int pin) {
  _pin = pin;
  pinMode(_pin, OUTPUT);
  _silent = false;
}
void Buzzer::turnOn(unsigned int frequency) {
  if ( ! _silent ) {
    tone(_pin, frequency);
    _stateIsOn = true;
  }
}
void Buzzer::turnOff() {
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
  if (_silent) {
    noTone(_pin);
  }
}

void groveLCD::setup() {
  _lcd.begin(16, 2);
}
void groveLCD::print(String message) {
  _lcd.setCursor(0, 0);
  if ( message.length() > 16 ) {
    _lcd.autoscroll();
    _lcd.print(message);
  } else {
    _lcd.print(message);
  }
}

void DigitalInput::setup(int pin, bool stateThatMeansIsOn, bool needsPullup){
  _pin = pin;
  _stateThatMeansIsOn = stateThatMeansIsOn;
  _needsPullup = needsPullup;
  pinMode(pin, INPUT);
}
bool DigitalInput::isOn(){
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

void DigitalOutput::setup(int pin) {
  _pin = pin;
  pinMode(_pin, OUTPUT);
}
void DigitalOutput::turnOn() {
  digitalWrite(_pin, HIGH);
  _stateIsOn = true;
}
void DigitalOutput::turnOff() {
  digitalWrite(_pin, LOW);
  _stateIsOn = false;
}
bool DigitalOutput::isOn() {
  return _stateIsOn;
}
bool DigitalOutput::isOff() {
  return ! _stateIsOn;
}

void AnalogInput::setup(int pin) {
  pinMode(pin,INPUT);
  _pin = pin;
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

void AnalogOutput::setup(int pin) {
  _pin = pin;
  pinMode(_pin,OUTPUT);
}
void AnalogOutput::set(int newSetting) {
  analogWrite(_pin, newSetting);
  _currentSetting = newSetting;
}
int AnalogOutput::setting() {
  return _currentSetting;
}

void SERVO::setup(int pin) {
  _pin = pin;
  _servo.attach(_pin);
  setPosition(0);
}
void SERVO::setPosition(int position){
  if ( position > 180 ) {
    _positionSetting = 180;
  } else {
    _positionSetting = position;
  }
  _servo.write(_positionSetting);
}
int SERVO::currentPosition(){
  return _positionSetting;
}

void electretMic::setup(int pin) {
  _pin = pin;
  pinMode(_pin, INPUT);
}
int electretMic::reading() {
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
