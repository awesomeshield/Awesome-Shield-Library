// Temperature.h tester

#include <Temperature.h>

Temperature T1(50);
Temperature T2(51);

Temperature TempArray[2] = {
  T1,
  T2
};

void setup() {
  Serial.begin(9600);
  TempArray[0].setSetPoint(31);
}

void loop() {

  TempArray[0].read();

  Serial.print("T = ");
  Serial.println(TempArray[0].value);

  if (TempArray[0].isInCtrlRange()) {
    Serial.println("T is in range");
  } else {
    Serial.println("T is not in range");
  }

  if (TempArray[0].needsHeat()) {
    Serial.println("T needs heat");
  } else {
    Serial.println("T doesn't need heat");
  }

  Serial.println();
  delay(500);
}
