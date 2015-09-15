// tell the Arduino you're using the Awesome Shield library
#include <Awesome.h>
// tell the Arduino you're using the Awesome Shield hardware
Awesome awesome;

// declare variables here
int micReading;
int threshold = 30;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

  // update the micReading variable
  // to the value returned by the mic on port 1
  micReading = awesome.port1.mic.reading();

  // print the micReading
  // to make finding a good threshold value easier
  Serial.println(micReading);

  // if the micReading is greater than the threshold
  if ( micReading > threshold ) {
    // if the LED is off
    if ( awesome.LED.isOff() ) {
      // turn the LED on
      awesome.LED.turnOn();
      // else (if the LED is on)
    } else {
      // turn the LED off
      awesome.LED.turnOff();
    }
    // wait for the sound to end
    delay(1000);
  }
}
