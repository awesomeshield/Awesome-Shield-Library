#include <Awesome.h>

#include <SD.h>                             //SD card library
#include <Wire.h>                           //One Wire library
#include "RTClib.h"                         //Real Time Clock library

#define redLEDpin          2                // LEDs on SD card

char filename[] = "DATAF000.CSV";           //filename for CSV file
File logfile;                               //indicate CSV file exists
RTC_DS1307 RTC;                             //Define RTC module

Awesome aws;

/* Data Logger Functions */
void SDSetup() {
  // initialize the SD card
  if ( !SD.begin() ) {
      error("Card failed, or not present");
    }
  Serial.println("card initialized.");
  // create a new file
  for (uint8_t i = 0; i < 100000; i++) {
    /*filename[5] = i/100 + '0';
    filename[6] = i/10 + '0';*/
    if ( i < 10 ) {
      filename[7] = i + '0';
    } else if ( i < 100 ) {
      filename[6] = i/10 + '0';
      filename[7] = i%10 + '0';
    } else if ( i < 1000) {
      filename[5] = i/100 + '0';
      filename[6] = i%100/10 + '0';
      filename[7] = i%100%10 + '0';
    } else {
      Serial.println();
      Serial.println("ran out of file names");
      Serial.println();
    }
    if (! SD.exists(filename)) {
      // only open a new file if it doesn't exist
      logfile = SD.open(filename, FILE_WRITE);
      break;  // leave the loop!
    }
  }
  if (! logfile) {
    error("couldnt create file");
  }
  Serial.print("Logging to: ");
  Serial.println(filename);
  File dataFile = SD.open(filename, FILE_WRITE);
  if (dataFile) {
    dataFile.print("date time (yyy/mm/dd hh:mm:ss), ");
    dataFile.print("Temperature, ");
    dataFile.print("Light Level ");
    dataFile.println();
    dataFile.close();
  } else {
    Serial.println("error copying data to CSV");
  }
}
void error(char *str)
  {
    Serial.print("error: ");
    Serial.println(str);

    // red LED indicates error
    digitalWrite(redLEDpin, HIGH);
    while(1);
  }
void SDLoop()
{
  File dataFile = SD.open(filename, FILE_WRITE);
  DateTime now = RTC.now();
  if (dataFile) {
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
    dataFile.print(aws.temperatureSensor.read());
    dataFile.print(",");
    dataFile.print(aws.lightSensor.read());
    dataFile.println();
    dataFile.close();
  } else {
    Serial.println("error copying data to CSV");
  }
}
void timeSetup()
{
    Wire.begin();
    if (!RTC.begin()) {
      logfile.println("RTC failed");
      Serial.println("RTC failed");
    }
    if (! RTC.isrunning()) {
        Serial.println("RTC is NOT running!");
        // following line sets the RTC to the date & time this sketch was compiled
        // uncomment it & upload to set the time, date and start run the RTC!
        RTC.adjust(DateTime(__DATE__, __TIME__));
    }
}

void setup() {
  Serial.begin(9600);
  timeSetup();
  SDSetup();
  aws.buzzer.setSilent(true);
  aws.diagnostic();
}

void loop() {
  SDLoop();
  aws.greenLED.turnOn();
  delay(100);
  aws.greenLED.turnOff();
  delay(1000);
}
