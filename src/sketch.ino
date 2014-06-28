#include <Awesome.h>

Awesome awesome;

void setup() {
  Serial.begin(9600);
  awesome.greenLedOn();
  delay(300);
  awesome.greenLedOff();
  delay(300);
  awesome.greenLedOn();
  delay(300);
  awesome.greenLedOff();
  delay(300);
}

/*
  lower,  upper =>  run drain
  lower,  !upper => close drain
  !lower, !upper => top up with feed water
*/

void loop() {
  bool upperFloatSubmerged = awesome.switchRead();

  if (upperFloatSubmerged) {
    openDrain();
  } else {
    closeDrain();
  }
}

void openDrain() {
  awesome.greenLedOn();
}

void closeDrain() {
  awesome.greenLedOff();
}
