#include <Awesome.h>
Awesome awesome;

float temp;
float lowestTemp;
float highestTemp;
int tempInterval = 2;
int red;
int blue;
float delayTime;
float howHotIsIt;


void setup() {
  Serial.begin(9600);
  //awesome.buzzer.setSilent(true);
  lowestTemp = awesome.temperatureSensor.read() - 0.5;
  highestTemp = lowestTemp + tempInterval;
}

void loop() {
  temp = awesome.temperatureSensor.read();
  /*Serial.print("temp = ");
  Serial.println(temp);*/

  // interpolate.. that's gonna be a doozey
  howHotIsIt = (temp - lowestTemp ) / ( highestTemp - lowestTemp );

  if ( howHotIsIt < 1 ) {
  red = howHotIsIt * 255;
  } else {
    red = 255;
  }
  if ( howHotIsIt < 255 ) {
    blue = 255 - howHotIsIt * 255;
  } else {
    blue = 0;
  }
  // turn on the RGB with the right amount of red and blue
  awesome.rgbLED.turnOn(red,0,blue);

  /*Serial.print("RED, BLUE = ");
  Serial.print(red);
  Serial.print(",  ");
  Serial.println(blue);*/

  Serial.println();

  // make a tick noise, adjust the length to what works for you
  awesome.buzzer.beep(5);

  // the longer this delay is, the farther apart the tick noises will be
  delay(blue);
}
