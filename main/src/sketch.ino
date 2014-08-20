#include <Awesome.h>

#include <SD.h>                             //SD card library
#include <Wire.h>                           //One Wire library
#include "RTClib.h"                         //Real Time Clock library


Awesome aws;

void setup() {
  Serial.begin(9600);

  aws.dataLogger.setup("Temp, Light");

  aws.buzzer.setSilent(true);
}

void loop() {
  /*SDLoop();*/

  int tempRdg = aws.temperatureSensor.read();
  int lightRdg = aws.lightSensor.read();

  Serial.print("Temp = ");
  Serial.println(tempRdg);
  Serial.print("Light = ");
  Serial.println(lightRdg);
  Serial.println();

  aws.dataLogger.log(tempRdg + "," + lightRdg);

  aws.greenLED.turnOn();
  delay(100);
  aws.greenLED.turnOff();
  delay(1000);
}
