// tell the Arduino you're using the Awesome Shield library
#include <Awesome.h>
// tell the Arduino you're using the Awesome Shield hardware
Awesome awesome;

// declare variables
float currentTemp;            // temperature of the sensor
float airTemp;                // temperature of the air
float howMuchHotterThanAir;   // difference between sensor temperature and air temperature
float red;                    // strength of the red LED
int blue;                     // strength of the blue LED


void setup() {
  // set the air temperature to the temeprature sensor reading
  // when the Arduino turns on
  airTemp = awesome.temperatureSensor.reading();
}

void loop() {
  // set the current temeprature to the temperature sensor reading
  // at the beginning of the loop
  currentTemp = awesome.temperatureSensor.reading();
  // calculate how much hotter current temperature is than the air
  howMuchHotterThanAir = currentTemp - airTemp;
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
  awesome.LED.turnOn(red, 0, blue);

  // delay for the same amount of time as blue
  // the delay will be long when the temperature difference is low
  // and it will be short when the temperature difference is high

  // everything in the sketch will happen very quickly
  // so this delay will basically be the time between buzzer ticks
  delay(blue);
}
