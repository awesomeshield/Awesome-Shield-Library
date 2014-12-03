#include <Awesome.h>

#include <SD.h>                             //SD card library
#include <Wire.h>                           //One Wire library
#include "RTClib.h"                         //Real Time Clock library


Awesome aws;

void setup() {
  Serial.begin(9600);

  Serial.println("Settting up ...");
  Serial.println();

  aws.buzzer.setSilent(true);

  /*aws.dataLogger.setup("Temp, Light");
  aws.dataLogger.printFileName();*/

  Serial.println("Setup Complete!");
  Serial.println();
}

void loop() {
  /*SDLoop();*/
  for (int i=2; i<200; i++) {
    aws.rgbLED.turnOn(i,0,0);
    delay (10);
  }
  for (int i=2; i<200; i++) {
    aws.rgbLED.turnOn(0,i,0);
    delay (10);
  }
  for (int i=2; i<200; i++) {
    aws.rgbLED.turnOn(0,0,i);
    delay (10);
  }
  for (int i=1; i<255; i++) {
    aws.rgbLED.turnOn(i,i,i  );
    delay (50);
  }

/*
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
  delay(1000);*/
}
