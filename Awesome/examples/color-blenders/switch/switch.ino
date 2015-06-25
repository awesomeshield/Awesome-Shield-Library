// tell the Arduino you're using the Awesome Shield library
#include <Awesome.h>
// tell the Arduino you're using the Awesome Shield hardware
Awesome awesome;

// declare variables here

// change these values to numbers between 0-255
// and see what colors you can produce :-)

// first set of variables
int red1   = 50;
int green1 = 50;
int blue1  = 50;

// second set of variables
int red2   = 200;
int green2 = 200;
int blue2  = 200;

int colorValue;

void setup() {
}

void loop() {
  if ( awesome.toggleSwitch.isOn() ) {
    // turn on the LED, using the color variables as inputs
    awesome.LED.turnOn(red1, green1, blue1);
  }
  if ( awesome.toggleSwitch.isOff() ) {
    awesome.LED.turnOn(red2, green2, blue2);
  }
}
