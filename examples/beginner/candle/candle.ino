// tell the Arduino you're using the Awesome Shield library
#include <Awesome.h>
// tell the Arduino you're using the Awesome Shield hardware
Awesome awesome;

// declare variables here

float ratio = 0.2;
int red = 200;
int green;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  // set red to a value between 155 and 255
  red = 155 + random(100);
  // find green to be red time the ratio
  green = red * ratio;
  // turn on the LED using the variables
  // to control how strong the red and green elements are
  awesome.LED.turnOn(red, green, 0);
  // delay for a small, random amount of time
  delay(random(10));
}
