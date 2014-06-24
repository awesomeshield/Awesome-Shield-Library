#include <OneWire.h>
//#include <Button.h>
#include <Awesome.h>

// LEDs
#define rgbRedPin       2
#define rgbGreenPin     3
#define rgbBluePin      4
#define redLedPin       6
#define greenLedPin     5

// buzzer
#define buzzerPin       NULL

// mechanical inputs
#define buttonPin       7
#define switchOnPin     8

// environmental inputs
#define lightSensorPin  A1
#define tempSensorPin   12
#define micPin          NULL

Awesome awesome;

void setup() {
  Serial.begin(9600);

  // LEDs
  pinMode(rgbRedPin,OUTPUT);
  pinMode(rgbGreenPin,OUTPUT);
  pinMode(rgbBluePin,OUTPUT);
  pinMode(redLedPin,OUTPUT);
  pinMode(greenLedPin,OUTPUT);

  // buzzer
  pinMode(buzzerPin,OUTPUT);

  // mechanical inputs
  pinMode(buttonPin,INPUT);
  pinMode(switchOnPin,INPUT);

  // environmental inputs
  pinMode(lightSensorPin,INPUT);
  pinMode(tempSensorPin,INPUT);
  pinMode(micPin,INPUT);
}

void loop() {

  // diagnostic();
}

void diagnostic() {

  // LedsFlash(500);                       // works
  // LedsCycle();                          // works

  // beep(500);                            // works!

  // buttonReadOut();                      // works
  // delay(1500);
  // switchReadOut();                      // works
  // delay(1500);

  // Serial.println(lightSensorReading()); // works

  // Serial.println(tempSensorReading());  // works

  /*Serial.println(micReading());  //
  delay(1000);*/

  // environmental inputs
    // #define micPin          A1

}

int lightSensorReading() {
  return analogRead(lightSensorPin);
}

int micReading() {
  return analogRead(micPin);
}

void switchReadOut() {
  if (switchIsOn()) {
    digitalWrite(greenLedPin,HIGH);
    digitalWrite(redLedPin,LOW);
  } else {
    digitalWrite(greenLedPin,LOW);
    digitalWrite(redLedPin,HIGH);
  }
}

bool switchIsOn() {
  return digitalRead(switchOnPin);
}

void buttonReadOut() {
  if (buttonIsPressed()) {
    digitalWrite(greenLedPin,HIGH);
    digitalWrite(redLedPin,LOW);
  } else {
    digitalWrite(greenLedPin,LOW);
    digitalWrite(redLedPin,HIGH);
  }
}

bool buttonIsPressed() {
  return awesome.button.isPressed();
}

void LedsFlash(int millis) {
  LedsTurnOn();
  delay(millis);
  LedsTurnOff();
}

void LedsTurnOn() {
  digitalWrite(rgbRedPin,HIGH);
  digitalWrite(rgbGreenPin,HIGH);
  digitalWrite(rgbBluePin,HIGH);
  digitalWrite(redLedPin,HIGH);
  digitalWrite(greenLedPin,HIGH);
}

void LedsTurnOff() {
  digitalWrite(rgbRedPin,LOW);
  digitalWrite(rgbGreenPin,LOW);
  digitalWrite(rgbBluePin,LOW);
  digitalWrite(redLedPin,LOW);
  digitalWrite(greenLedPin,LOW);
}

void LedsCycle() {
  digitalWrite(rgbRedPin,HIGH);
  delay(150);
  digitalWrite(rgbRedPin,LOW);
  delay(150);
  digitalWrite(rgbGreenPin,HIGH);
  delay(150);
  digitalWrite(rgbGreenPin,LOW);
  delay(150);
  digitalWrite(rgbBluePin,HIGH);
  delay(150);
  digitalWrite(rgbBluePin,LOW);
  delay(150);
  digitalWrite(redLedPin,HIGH);
  delay(150);
  digitalWrite(redLedPin,LOW);
  delay(150);
  digitalWrite(greenLedPin,HIGH);
  delay(150);
  digitalWrite(greenLedPin,LOW);
  delay(150);
}

void beep(int millis) {
  tone(buzzerPin, 400, millis);
}

float tempSensorReading() {
  OneWire ds(tempSensorPin);
  //returns the temperature from one DS18S20 in DEG Celsius

  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
      //no more sensors on chain, reset search
      ds.reset_search();
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Device is not recognized");
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); // start conversion, with parasite power on at the end

  byte present = ds.reset();
  ds.select(addr);
  ds.write(0xBE); // Read Scratchpad

  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds.read();
  }

  ds.reset_search();

  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;

  return TemperatureSum;
}
