// include the library with the sketch when sending to the Arduino
#include <Awesome.h>
// tell the Arduino you're using the Awesome Shield
Awesome awesome;

// create variables
float sensorTemp;             // temperature of the senso
float airTemp;                // temperature of the air
float howMuchHotterThanAir;   // difference between sensor temperature and air temperature
float red;                    // strength of the red LED
int blue;                     // strength of the blue LED


void setup() {
  // set the air temperature equal to what the temperature sensor reads
  // when the Arduino turns on
  airTemp = awesome.temperatureSensor.check();
}

void loop() {
  // set the sensor temperature to the temperature the sensor reads
  // at the beginning of the loop
  sensorTemp = awesome.temperatureSensor.check();
  // calculate how much hotter the sensor is than the air
  howMuchHotterThanAir = sensorTemp - airTemp;
  // set the strength of the red LED to 100 times the temperature difference
  red = howMuchHotterThanAir * 100;
  // set the strength of the blue LED to the maximum value (1000)
  // minus the strength of the red LED
  // this way blue is high when red is low, and vice versa
  blue = 1000 - red;

  // make a 'tick' sound with the buzzer
  awesome.buzzer.beep(10);

  // turn on the color LED, setting the strength of red and blue as calculated
  // above
  awesome.colorLED.turnOn(red, 0, blue);

  // delay for the same amount of time as blue
  // the delay will be long when the temperature difference is low
  // and it will be short when the temperature difference is high

  // everything in the sketch will happen very quickly
  // so this delay will basically be the time between buzzer ticks
  delay(blue);
}
