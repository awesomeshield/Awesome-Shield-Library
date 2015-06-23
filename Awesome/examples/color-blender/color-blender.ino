// the next line tells the Arduino you're using the Awesome Shield library
#include <Awesome.h>
// the next line tells the Arduino you're using the Awesome Shield itself
Awesome awesome;


// declare variables here
int red, green, blue;
bool wasLastPressed = false;
int counter;
int currentColor = 3;
int colorValue;

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

  // colorValue from knob reading
  colorValue = awesome.knob.reading()/4;

  switch(currentColor) {
    case 1:
      red = colorValue;
      break;
    case 2:
      green = colorValue;
      break;
    case 3:
      blue = colorValue;
      break;
  }
  Serial.print("awesome.LED.turnOn(");
  Serial.print(red);
  Serial.print(", ");
  Serial.print(green);
  Serial.print(", ");
  Serial.print(blue);
//  Serial.println(");    // (red, green, blue)");
  switch(currentColor) {
    case 1:
      Serial.println(");    // (RED, green, blue)");
      break;
    case 2:
      Serial.println(");    // (red, GREEN, blue)");
      break;
    case 3:
      Serial.println(");    // (red, green, BLUE)");
      break;
  }
  //Serial.println(counter);
  awesome.LED.turnOn(red,green,blue);
}
