#include <Awesome.h>

Awesome aws;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if ( aws.toggle.read() ) {
    aws.greenLED.turnOn();
  } else {
    aws.greenLED.turnOff();
  }
  delay(100);
}
