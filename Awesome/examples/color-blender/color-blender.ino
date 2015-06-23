// the next line tells the Arduino you're using the Awesome Shield library
#include <Awesome.h>
// the next line tells the Arduino you're using the Awesome Shield itself
Awesome awesome;

// color variables
int red   = 128;
int green = 128;
int blue  = 128;

// color select variable
int colorSelect = 3;
int state = 0;
int knobValue;

void onPress() {
  colorSelect += 1;
}

void setup() {
  // put code here to have it run right after the Arduino turns on or resets
  Serial.begin(9600);
  attachInterrupt(0, onPress, RISING);
}

void loop() {
  state = colorSelect % 3;
  knobValue = awesome.knob.reading()/4;

  Serial.println(state);

  if ( awesome.button.isOn() ) {
    switch ( state ) {
      case 0:  // red
        awesome.LED.turnOn(RED);
        break;
      case 1:  // green
        awesome.LED.turnOn(GREEN);
        break;
      case 2:  // blue
        awesome.LED.turnOn(BLUE);
        break;
      default:
        break;
    }
  } else {
    switch ( state ) {
      case 0:  // red
        red = knobValue;
        break;
      case 1:  // green
        green = knobValue;
        break;
      case 2:  // blue
        blue = knobValue;
        break;
      default:
        break;
    }
    awesome.LED.turnOn(red,green,blue);
  }
}
