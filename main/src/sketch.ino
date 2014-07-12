#include <Awesome.h>

Awesome awesome;

void setup() {
  Serial.begin(9600);
  awesome.rgbLED.turnOn(191,80,239);
  delay(500);
  awesome.diagnostic();

  /*awesome.redLED.setPin(6);*/
}

void loop() {
  awesome.redLED.turnOn();
  awesome.greenLED.turnOff();
  delay(500);
  awesome.redLED.turnOff();
  awesome.greenLED.turnOn();
  delay(500);
  /*bool upperFloatSubmerged = awesome.switchRead();

  if (upperFloatSubmerged) {
    openDrain();
  } else {
    closeDrain();
  }

  delay(1000);
  awesome.rgbLedOn(100);
  delay(1000);*/

}

void openDrain() {
  awesome.rgbLED.turnOn(WHITE);
}

void closeDrain() {
  awesome.rgbLED.turnOn(GREEN);
}
