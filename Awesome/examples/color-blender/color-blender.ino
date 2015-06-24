// the next line tells the Arduino you're using the Awesome Shield library
#include <Awesome.h>
// the next line tells the Arduino you're using the Awesome Shield itself
Awesome awesome;


// declare variables here
int red, green, blue;
bool pressedLastLoop = false;
int pressCounter;
int colorNumber = 3;
int colorValue;

// a function to print the current red, green, and blue values
// to serial, written inside the LED turnOn() function
void serialUpdate() {
  Serial.print("awesome.LED.turnOn(");
  Serial.print(red);
  Serial.print(", ");
  Serial.print(green);
  Serial.print(", ");
  Serial.print(blue);
}

void setup()
{
  // put code here to have it run right after the Arduino turns on or resets
  Serial.begin(9600);
}

void loop() {
  // if the button is down & it was not pressed during the last loop
  // this means the button was pressed between last loop
  // and the current loop
  if ( awesome.button.isDown() && ! pressedLastLoop ) {
    // increase the pressCounter
    pressCounter += 1;
    // save the information that button was pressed last loop
    pressedLastLoop = true;
  }
  // if the button is up
  if ( awesome.button.isUp() ) {
    // save the information that the button was not pressed last loop
    pressedLastLoop = false;
  }

  // convert loop pressCounter to value that is either 1, 2 or 3
  colorNumber = pressCounter % 3 + 1;

  // awesome.knob.reading() is between 0-1023
  // divide it by 4 to get a value between 0-255
  colorValue = awesome.knob.reading()/4;

  switch(colorNumber) {
    // when colorNumber is 1:
    case 1:
      red = colorValue;
      serialUpdate();
      Serial.println(");    // (RED, green, blue)");
      break;
    // when colorNumber is 2:
    case 2:
      green = colorValue;
      serialUpdate();
      Serial.println(");    // (red, GREEN, blue)");
      break;
    // when colorNumber is 3:
    case 3:
      blue = colorValue;
      serialUpdate();
      Serial.println(");    // (red, green, BLUE)");
      break;
  }
  awesome.LED.turnOn(red, green, blue);
}
