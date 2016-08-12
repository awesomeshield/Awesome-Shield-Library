// tell the Arduino you're using the Awesome Shield library
#include <Awesome.h>
// tell the Arduino you're using the Awesome Shield hardware
Awesome awesome;

// declare variables here

// change these values to numbers between 0-255
// and see what colors you can produce :-)
int red   = 100;
int green = 100;
int blue  = 100;

int colorValue;

void setup() {
  awesome.setup(9600);
  // turn on the LED, using the color variables as inputs
  awesome.LED.turnOn(red, green, blue);
}

void loop() {
}
