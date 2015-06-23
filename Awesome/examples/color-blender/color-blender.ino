// the next line tells the Arduino you're using the Awesome Shield library
#include <Awesome.h>
// the next line tells the Arduino you're using the Awesome Shield itself
Awesome awesome;


// declare variables here
int red, green, blue;
bool wasLastPressed = false;
int counter;
int currentColor = 3;


void setup()
{
  // put code here to have it run right after the Arduino turns on or resets
  Serial.begin(9600);
}

void loop()
{
  // loop counter
  if ( awesome.button.isOn() && ! wasLastPressed ) {
    counter += 1;
    wasLastPressed = true;
  }
  if ( awesome.button.isOff() ) {
    wasLastPressed = false;
  }

  // convert loop counter to ternary value
  currentColor = counter % 3 + 1;

  switch(currentColor) {
    case 1:
      awesome.LED.turnOn(RED);
      break;
    case 2:
      awesome.LED.turnOn(GREEN);
      break;
    case 3:
      awesome.LED.turnOn(BLUE);
      break;
  }

  Serial.println(counter);
  awesome.LED.turnOn(red,green,blue);
}
