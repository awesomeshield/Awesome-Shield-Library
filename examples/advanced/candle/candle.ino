// tell the Arduino you're using the Awesome Shield library
#include <Awesome.h>
// tell the Arduino you're using the Awesome Shield hardware
Awesome awesome;

// declare variables here

float ratio = 0.2;
int red = 200;
int green;

void makeCandleLight() {
  // do not let red go below 155, or above 255
  if ( red < 155 ) {
    red = 155;
  } else if ( red > 255 ) {
    red = 255;
  }
  //
  green = red * ratio;
  awesome.LED.turnOn(red, green, 0);
  delay(random(10));
}

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  red = red + random(-5,5);

  // occasionally flicker for 25 iterations
  if ( random(100) == 1 ) {
    for ( int i = 0; i < random(10,50); i++ ) {
       // flicker
      red = 155 + random(100);
      makeCandleLight();
    }
  }

  makeCandleLight();
}
