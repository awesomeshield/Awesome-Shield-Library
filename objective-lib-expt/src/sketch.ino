#include "Awesome.h"

Awesome aws;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  aws.myBox.length = 7;
  Serial.println(aws.myBox.length);
  delay (500);
}
