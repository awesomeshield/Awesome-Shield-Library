#include <Awesome.h>

Awesome awesome;

void setup() {
  Serial.begin(9600);
  Serial.println("Ready");
}

void loop() {

  Serial.println("Temperature, in Celsius: ");
  Serial.println(awesome.temperatureSensor.read());
  Serial.println();
  delay(500);
}
