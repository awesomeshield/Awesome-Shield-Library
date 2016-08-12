// tell the Arduino you're using the Awesome Shield library
#include <Awesome.h>
// tell the Arduino you're using the Awesome Shield hardware
Awesome awesome;

// declare variables here
int red = 127;
int green = 127;
int blue = 127;

void setup() {
  awesome.setup(9600);
}

void loop() {

  // set one color to respond to the knob reading
  // awesome.knob.reading() is between 0-1023
  // divide it by 4 to get a value between 0-255
  red = awesome.knob.reading()/4;

  // turn on the LED, using the color variables as inputs
  awesome.LED.turnOn(red, green, blue);
}
