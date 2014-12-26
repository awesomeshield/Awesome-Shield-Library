#include <Awesome.h>
Awesome awesome;

float sensorTemp;
float airTemp;
float howMuchHotterThanAir;
float red;


void setup() {
  airTemp = awesome.temperatureSensor.check();
}

void loop() {
  sensorTemp = awesome.temperatureSensor.check();
  howMuchHotterThanAir = sensorTemp - airTemp;
  red = howMuchHotterThanAir * 100;
  awesome.colorLED.turnOn(red, 0, 0);
}
