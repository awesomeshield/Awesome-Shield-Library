// tell the Arduino you're using the Awesome Shield library
#include <Awesome.h>
// tell the Arduino you're using the Awesome Shield hardware
Awesome awesome;

// declare variables here
int red = 127, green = 127, blue = 127; // begin at half of maximum value

int colorValue;

void setup() {
  Serial.begin(9600);
}

void loop() {

  // set one color to respond to the knob reading
  // awesome.knob.reading() is between 0-1023
  // divide it by 4 to get a value between 0-255
  blue = awesome.knob.reading()/4;

  // turn on the LED, using the color variables as inputs
  awesome.LED.turnOn(red, green, blue);
}
