// the next line tells the Arduino you're using the Awesome Shield library
#include <Awesome.h>
// the next line tells the Arduino you're using the Awesome Shield itself
Awesome awesome;


// declare variables here
int red   = 128;
int green = 128;
int blue  = 128;

void setup()
{
  // put code here to have it run right after the Arduino turns on or resets
  Serial.begin(9600);
}

void loop()
{
  awesome.LED.turnOn(red,green,blue);
  red = awesome.knob.reading();
  red = red / 4;

}
