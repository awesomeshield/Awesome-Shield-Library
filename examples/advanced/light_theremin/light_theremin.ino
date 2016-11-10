// tell the Arduino you're using the Awesome Shield library
#include <Awesome.h>
// tell the Arduino you're using the Awesome Shield hardware
Awesome awesome;

// declare variables here
int frequency;
int initialReading;

void setup() {
  awesome.setup(9600);
  // put your setup code here, to run once:
  initialReading = awesome.lightSensor.reading();
}

void loop() {
  // put your main code here, to run repeatedly:

  // map the light sensor reading
  // from the range 0-initialReading
  // to the range 200-600
  frequency = map(awesome.lightSensor.reading(),0,initialReading,200,600);

  // turn on the buzzer at the frequency
  awesome.buzzer.turnOn(frequency);

  // wait a small amount of time
  // so that we have a chance to hear the tone
  delay(10);
}
