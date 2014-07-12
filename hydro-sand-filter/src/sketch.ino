#include <Awesome.h>

Awesome easy;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting...");
}

void openDrain() {
  easy.rgbLED.turnOn(WHITE);    // make it control relay for drain valve
}

void closeDrain() {
  easy.rgbLED.turnOn(RED);    // make it control relay for drain valve
}

void loop() {
  Serial.print("Looping.");

  bool upperFloatSubmerged = easy.button.read();  // make it read float switch
  bool lowerFloatSubmerged = easy.toggleSwitch.read();

  Serial.print("Upper Float: ");
  Serial.println(upperFloatSubmerged);
  Serial.print("Low Float: ");
  Serial.println(lowerFloatSubmerged);

  if ( lowerFloatSubmerged ) {
    openDrain();
    // do not change feed status
  } else if ( upperFloatSubmerged ) {
    Serial.print("Error: float malfunction. Upper float reads submerged, lower float reads not submerged. Check float switches. One may be stuck.");
    closeDrain();
    // closeFeed() if possible
  } else {
    Serial.print("Both float switches read not submerged. Check filter to ensure sand bed is not dry.");
    closeDrain();
    // openFeed() if possible
  }

  // just to keep things from running to fast
  delay(50);
}
