#include <Awesome.h>

#include <SD.h>                             //SD card library
#include <Wire.h>                           //One Wire library
#include "RTClib.h"                         //Real Time Clock library


Awesome awesome;

void setup() {
}

void loop() {
  awesome.test();
}
