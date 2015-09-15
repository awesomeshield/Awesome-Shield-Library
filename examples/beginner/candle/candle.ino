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
  red = 155 + random(100);
  green = red * ratio;
  awesome.LED.turnOn(red, green, 0);
  delay(random(10));
}
