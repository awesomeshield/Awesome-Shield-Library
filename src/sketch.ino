#include <Awesome.h>

Awesome awesome;

void setup() {
  Serial.begin(9600);
  awesome.rgbLedOn(GREEN);
  delay(300);
  awesome.rgbLedOff();
  delay(300);
  awesome.rgbLedOn(GREEN);
  delay(300);
  awesome.rgbLedOff();
  delay(300);
}


/* lower, upper =>   run drain
   lower, !upper =>  close drain
   !lower, !upper => feed
*/

void loop() {
  // read float switch
  bool upperFloatSubmerged = awesome.switchRead();

  if (upperFloatSubmerged) {
    openDrain();
  } else {
    closeDrain();
  }
}

void openDrain() {
  awesome.rgbLedOn(WHITE);
}

void closeDrain() {
  awesome.rgbLedOff();
}
