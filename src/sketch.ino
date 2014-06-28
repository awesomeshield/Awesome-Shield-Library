#include <Awesome.h>

Awesome awesome;

void setup() {
  Serial.begin(9600);
  awesome.rgbLedOn(GREEN);
}


void loop() {
  // read float switch
  bool floatSubmerged = awesome.switchRead();
  // if float is off
  if (floatSubmerged) {
    awesome.rgbLedOn(GREEN);
  } else {
    awesome.rgbLedOff();
  }
}
