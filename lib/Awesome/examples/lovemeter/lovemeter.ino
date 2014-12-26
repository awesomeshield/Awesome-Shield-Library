#include <Awesome.h>
Awesome awesome;

float sensorTemp;
float airTemp;
float howMuchHotterThanAir;
float red;
int blue;


void setup() {
  airTemp = awesome.temperatureSensor.check();
}

void loop() {
  sensorTemp = awesome.temperatureSensor.check();
  howMuchHotterThanAir = sensorTemp - airTemp;
  red = howMuchHotterThanAir * 100;
  blue = 1000 - red;

  awesome.buzzer.beep(10);

  awesome.colorLED.turnOn(red, 0, blue);

  delay(blue);
}
