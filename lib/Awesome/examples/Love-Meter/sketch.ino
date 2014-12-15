#include <Awesome.h>
Awesome awesome;

int temp;

void setup() {
}

void loop() {
  temp = awesome.temperatureSensor.read();
  awesome.buzzer.beep(10);
  delay(temp);
}
