#include <Awesome.h>
Awesome awesome;

float temp;
float lowestTemp;     // should be air temp
float highestTemp;
int tempInterval = 3;
int red;      // change to hotness
int blue;     // change to coldness
float howHotIsIt; // change to hotter than air


void setup() {
  Serial.begin(9600);
  //awesome.buzzer.setSilent(true);
  lowestTemp = awesome.temperatureSensor.read() - 0.25;
  highestTemp = lowestTemp + tempInterval;
}

void loop() {
  // we're going to need to use the current temperature in our calculations
  // so let's store it in a variable called 'temp'
  // I picked this name because it's short, and reminds me what the variable means
  temp = awesome.temperatureSensor.read();
  /*Serial.print("temp = ");
  Serial.println(temp);*/

  // mathematically, this interpolation.. that's gonna be a DOOZEY to explain
  // we need to measure how hot it is
  // we particularly need to know how much hotter than room temperature it is
  // [ ] break this into two variables: 'hotter than air temp' and 'maximum hotter than air temp'
  // explain each value, and the use of their ratio
  howHotIsIt = (temp - lowestTemp ) / ( highestTemp - lowestTemp );

  // if temp < lowest temp [ ] change
  if ( howHotIsIt < 0 ) {
    // adjust air temp ... the air got colder
    lowestTemp = temp - 0.25;
    // since the temperature is colder than we expected, me
    red = 0;
    } else if ( howHotIsIt < 1 ) {
      red = howHotIsIt * 100;
      } else {
        red = 100;
      }

    blue = 100 - red;

    red = red * 2.5;
    blue = blue * 2.5;

    // make a tick noise, adjust the length to what works for you
    awesome.buzzer.beep(5);

    // turn on the RGB with the right amount of red and blue
    awesome.rgbLED.turnOn(red,0,blue);

    // the longer this delay is, the farther apart the tick noises will be
    // we want the ticks to be farther apart when the temperature is lower (colder)
    // the number we found for how much blue light we want does the same thing
    // the amount of blue is bigger when the sensor is colder
    delay(blue);
  }
