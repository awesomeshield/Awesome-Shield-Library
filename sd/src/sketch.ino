#include "SD.h"

// A simple data logger for the Arduino analog pins
#define LOG_INTERVAL  1000 // mills between entries

#define lightSensorPin  A1


// the digital pins that connect to the LEDs
#define redLEDpin 3
#define greenLEDpin 4

// for the data logging shield, we use digital pin 10 for the SD cs line
const int chipSelect = 10;

// the logging file
File logfile;

void error(char *str)
{
  Serial.print("error: ");
  Serial.println(str);

  // red LED indicates error
  digitalWrite(redLEDpin, HIGH);

  while(1);
}

void setup()
{
  Serial.begin(9600);
  Serial.println();

  pinMode(lightSensorPin, INPUT);

  // initialize the SD card
  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");

  // create a new file
  char filename[] = "LOGGER00.CSV";
  for (uint8_t i = 0; i < 100; i++) {
    filename[6] = i/10 + '0';
    filename[7] = i%10 + '0';
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

  logfile.println("temp");

  /*if (logfile.writeError || !logfile.sync()) {
    error("write header");
  }*/

  pinMode(redLEDpin, OUTPUT);
  pinMode(greenLEDpin, OUTPUT);

   // If you want to set the aref to something other than 5v
  //analogReference(EXTERNAL);
}

void loop()
{
  // delay for the amount of time we want between readings
  delay(LOG_INTERVAL-300);

  digitalWrite(greenLEDpin, HIGH);

  int lightReading = analogRead(lightSensorPin);

  logfile.print(lightReading);

  Serial.println(lightReading);

  delay (300);

  digitalWrite(greenLEDpin, LOW);
}
