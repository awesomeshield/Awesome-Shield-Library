// tell the Arduino you're using the Awesome Shield library
#include <Awesome.h>
// tell the Arduino you're using the Awesome Shield hardware
Awesome awesome;

// declare variables here
bool lastSwitchState;

void setup() {
  awesome.setup(9600);
  // put your setup code here, to run once:
  awesome.LED.turnOn();
  delay(500);
  awesome.LED.turnOn(RED);
  delay(500);
  awesome.LED.turnOn(GREEN);
  delay(500);
  awesome.LED.turnOn(BLUE);
  delay(500);
  awesome.LED.turnOff();
  delay(500);

  awesome.buzzer.beep(500);

  // put your main code here, to run repeatedly:
  Serial.println("Waiting for button press...");
  awesome.LED.turnOn(RED);
  while ( ! awesome.button.isDown() ) {
    // wait
  }
  Serial.println("...button working.");
  awesome.LED.turnOn(GREEN);
  delay(500);

  awesome.LED.turnOn(RED);
  lastSwitchState = awesome.toggleSwitch.isOn();
  Serial.println("Waiting for toggle switch...");
  awesome.LED.turnOn(RED);
  while ( awesome.toggleSwitch.isOn() == lastSwitchState ) {
    // wait
  }
  Serial.println("...toggle switch working.");
  awesome.LED.turnOn(GREEN);
  delay(500);
  awesome.LED.turnOff();
}

void loop() {
  Serial.print("Temperature reading = ");
  Serial.println(awesome.temperatureSensor.reading());
  Serial.print("Light reading = ");
  Serial.println(awesome.lightSensor.reading());
  Serial.print("Knob reading = ");
  Serial.println(awesome.knob.reading());
  delay(1000);
}
