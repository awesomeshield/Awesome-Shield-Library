#include <Awesome.h>

Awesome awesome;

void setup() {
  Serial.begin(9600);
}

void loop() {
  bool upperFloatSubmerged = awesome.switchRead();

  if (upperFloatSubmerged) {
    openDrain();
  } else {
    closeDrain();
  }

  delay(1000);
  awesome.rgbLedOn(100);
  delay(1000);

}

void openDrain() {
  awesome.rgbLED.turnOn(WHITE);
}

void closeDrain() {
  awesome.rgbLED.turnOn(GREEN);
}
