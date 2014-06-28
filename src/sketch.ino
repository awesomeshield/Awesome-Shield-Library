#include <Awesome.h>

Awesome awesome;

void setup() {
  Serial.begin(9600);
  awesome.rgbLedOn(RED);
}

int brightness = 0;

void loop() {
  analogWrite(rgbRedPin, brightness);

  if (brightness < 256) {
    brightness = brightness + 1;
  } else {
    brightness = 0;
  }
  delay(20);
}
