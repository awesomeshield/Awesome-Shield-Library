/*
  Awesome.cpp library - for reading Awesomes
  Created by Christopher W. J. Palmer, 26 May 2014
  Part of the BrewBox Project
  Private library, not for public use.
*/

#include "Arduino.h"
#include "Awesome.h"

#include <avr/pgmspace.h>
//#include <SD.h>                             //SD card library
//#include <Wire.h>                           //One Wire library
//#include "RTClib.h"                         //Real Time Clock library

// temperature data table for 10k thermistor with a 10k pull down resistor
const int temps[] PROGMEM = { 0, 1, 2, 3, 4, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 143, 144, 145, 146, 147, 148, 149, 150, 151, 151, 152, 153, 154, 155, 156, 157, 158, 159, 159, 160, 161, 162, 163, 164, 165, 166, 167, 167, 168, 169, 170, 171, 172, 173, 174, 175, 175, 176, 177, 178, 179, 180, 181, 182, 182, 183, 184, 185, 186, 187, 188, 189, 190, 190, 191, 192, 193, 194, 195, 196, 197, 197, 198, 199, 200, 201, 202, 203, 204, 205, 205, 206, 207, 208, 209, 210, 211, 212, 212, 213, 214, 215, 216, 217, 218, 219, 220, 220, 221, 222, 223, 224, 225, 226, 227, 228, 228, 229, 230, 231, 232, 233, 234, 235, 235, 236, 237, 238, 239, 240, 241, 242, 243, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 252, 253, 254, 255, 256, 257, 258, 259, 260, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 269, 270, 271, 272, 273, 274, 275, 276, 277, 278, 279, 279, 280, 281, 282, 283, 284, 285, 286, 287, 288, 289, 289, 290, 291, 292, 293, 294, 295, 296, 297, 298, 299, 300, 301, 301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312, 313, 314, 315, 315, 316, 317, 318, 319, 320, 321, 322, 323, 324, 325, 326, 327, 328, 329, 330, 331, 332, 333, 334, 335, 335, 336, 337, 338, 339, 340, 341, 342, 343, 344, 345, 346, 347, 348, 349, 350, 351, 352, 353, 354, 355, 356, 357, 358, 359, 360, 361, 362, 363, 364, 365, 366, 367, 368, 369, 370, 371, 372, 373, 374, 375, 376, 377, 378, 379, 380, 381, 382, 383, 384, 385, 386, 387, 388, 389, 390, 392, 393, 394, 395, 396, 397, 398, 399, 400, 401, 402, 403, 404, 405, 406, 407, 408, 410, 411, 412, 413, 414, 415, 416, 417, 418, 419, 420, 422, 423, 424, 425, 426, 427, 428, 429, 430, 432, 433, 434, 435, 436, 437, 438, 439, 441, 442, 443, 444, 445, 446, 448, 449, 450, 451, 452, 453, 455, 456, 457, 458, 459, 460, 462, 463, 464, 465, 466, 468, 469, 470, 471, 472, 474, 475, 476, 477, 479, 480, 481, 482, 484, 485, 486, 487, 489, 490, 491, 492, 494, 495, 496, 498, 499, 500, 501, 503, 504, 505, 507, 508, 509, 511, 512, 513, 515, 516, 517, 519, 520, 521, 523, 524, 525, 527, 528, 530, 531, 532, 534, 535, 537, 538, 539, 541, 542, 544, 545, 547, 548, 550, 551, 552, 554, 555, 557, 558, 560, 561, 563, 564, 566, 567, 569, 570, 572, 574, 575, 577, 578, 580, 581, 583, 585, 586, 588, 589, 591, 593, 594, 596, 598, 599, 601, 603, 604, 606, 608, 609, 611, 613, 614, 616, 618, 620, 621, 623, 625, 627, 628, 630, 632, 634, 636, 638, 639, 641, 643, 645, 647, 649, 651, 653, 654, 656, 658, 660, 662, 664, 666, 668, 670, 672, 674, 676, 678, 680, 683, 685, 687, 689, 691, 693, 695, 697, 700, 702, 704, 706, 708, 711, 713, 715, 718, 720, 722, 725, 727, 729, 732, 734, 737, 739, 741, 744, 746, 749, 752, 754, 757, 759, 762, 764, 767, 770, 773, 775, 778, 781, 784, 786, 789, 792, 795, 798, 801, 804, 807, 810, 813, 816, 819, 822, 825, 829, 832, 835, 838, 842, 845, 848, 852, 855, 859, 862, 866, 869, 873, 877, 881, 884, 888, 892, 896, 900, 904, 908, 912, 916, 920, 925, 929, 933, 938, 942, 947, 952, 956, 961, 966, 971, 976, 981, 986, 991, 997, 1002, 1007, 1013, 1019, 1024, 1030, 1036, 1042, 1049, 1055, 1061, 1068, 1075, 1082, 1088, 1096, 1103, 1110, 1118, 1126, 1134, 1142, 1150, 1159, 1168, 1177, 1186, 1196, 1206, 1216, 1226, 1237, 1248, 1260, 1272, 1284, 1297, 1310, 1324, 1338, 1353, 1369, 1385, 1402, 1420, 1439, 1459, 1480, 1502 };

Awesome::Awesome() {
  redLED.             setup(redLedPin);
  greenLED.           setup(greenLedPin);
  colorLED.           setup(rgbRedPin, rgbGreenPin, rgbBluePin);
  lightSensor.        setup(lightSensorPin);
  temperatureSensor.  setup(tempSensorPin);
  button.             setup(buttonPin);
  toggle.             setup(switchOnPin);
  buzzer.             setup(buzzerPin);
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
void redGreenBlueLED::turnOn(int ColorOrHowMuchRed, int howMuchGreen, int howMuchBlue) {
  if ( ColorOrHowMuchRed > 255 && howMuchGreen == 0 && howMuchBlue == 0 ) {
    switch (ColorOrHowMuchRed) {
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
      case PURPLE:
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
    //  zero negative inputs
    if (ColorOrHowMuchRed < 0) {
      ColorOrHowMuchRed = 0;
    }
    if (howMuchGreen < 0) {
      howMuchGreen = 0;
    }
    if (howMuchBlue < 0) {
      howMuchBlue = 0;
    }
    // turn on LEDs
    if (ColorOrHowMuchRed != 0) {
      analogWrite(_redPin, ColorOrHowMuchRed);
    }
    if (howMuchGreen != 0) {
      analogWrite(_greenPin, howMuchGreen);
    }
    if (howMuchBlue != 0) {
      analogWrite(_bluePin, howMuchBlue);
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
double LightSensor::check() {
  int lightADCReading = analogRead(_pin);
  // Calculating the voltage of the Analog to Digital Converter ADC for light
  double lightInputVoltage = 5.0 * ((double)lightADCReading / 1024.0);
  // Calculating the resistance of the photoresistor in the voltage divider
  double lightResistance = (10.0 * 5.0) / lightInputVoltage - 10.0;
  // Calculating the intensity of light in lux
  double currentLightInLux = 255.84 * pow(lightResistance, -10/9);
  return currentLightInLux;
}

void TemperatureSensor::setup(int pin) {
  _pin = pin;
  pinMode(_pin,INPUT);
}
float TemperatureSensor::_check() {
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
  // Serial.print("averageData = ");
  // Serial.println(averageData);

  int therm;
  therm = averageData-238;
  // therm=analogRead(_pin)-238;
  therm=pgm_read_word(&temps[therm]);
  float result = therm;
  result = result / 10;
  return result;
}
float TemperatureSensor::check() {
  return _check();
}

void Switch::setup(int pin) {
  _pin = pin;
  pinMode(_pin, INPUT);
}
bool Switch::check() {
  return digitalRead(_pin);
}

void Buzzer::setup(int pin) {
  _pin = pin;
  pinMode(_pin, OUTPUT);
  _silent = false;
}
void Buzzer::beep(unsigned long millis, unsigned int frequency) {
  if ( _silent ) {
    return;
  } else {
    tone(_pin, frequency, millis);
    delay(millis + 5);
  }
}
void Buzzer::setSilentMode(bool newState) { // [] 'change to setSilentMode'
  _silent = newState;
  if (_silent) {
    noTone(_pin);
  }
}

/*
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

  // SET _filename
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
*/

/*
int Awesome::miccheck() {
  return analogRead(micPin);
}
*/

void Awesome::_LedsFlash(int millis) {
  _LedsTurnOn();
  delay(millis);
  _LedsTurnOff();
}

void Awesome::_LedsTurnOn() {
  colorLED.turnOn(WHITE);
  redLED.turnOn();
  greenLED.turnOn();
}

void Awesome::_LedsTurnOff() {
  colorLED.turnOff();
  redLED.turnOff();
  greenLED.turnOff();
}

void Awesome::_LedsCycle() {
  colorLED.turnOn(RED);
  delay(150);
  colorLED.turnOn(GREEN);
  delay(150);
  colorLED.turnOn(BLUE);
  delay(150);
  colorLED.turnOn(CYAN);
  delay(150);
  colorLED.turnOn(YELLOW);
  delay(150);
  colorLED.turnOn(PURPLE);
  delay(150);
  colorLED.turnOn(WHITE);
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
    colorLED.turnOn(GREEN);
    delay(300);
    greenLED.turnOff();
    colorLED.turnOff();
    delay(150);
  }
}

/*
void Awesome::test() {
  _LedsFlash(500);
  _LedsCycle();
  _LedsTurnOff();

  buzzer.beep(500);
  delay(500);

  Serial.print("Light reading = ");
  Serial.println(lightSensor.check());

  Serial.print("Temperature reading = ");
  Serial.println(temperatureSensor.check());
  Serial.println();

  // Serial.println(micReading());
  // delay(1000);

  // flash green LED once button is pushed
  redLED.turnOn();
  while ( ! button.check() ) {
    // wait
  }
  greenLED.turnOn();
  delay(1000);
  greenLED.turnOff();
  redLED.turnOff();
  delay(500);

  // flash green LED once switch is flipped
  bool initialSwitchState = toggle.check();
  redLED.turnOn();
  while (toggle.check() == initialSwitchState) {
    // wait
  }
  greenLED.turnOn();
  delay(1000);
  greenLED.turnOff();
  redLED.turnOff();

} */
