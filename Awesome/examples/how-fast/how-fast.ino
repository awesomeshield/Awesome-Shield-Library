/* print the number of times this sketch loops per second
   using a 10 second sample
*/

int i;

void setup()
{
  // put code here to have it run right after the Arduino turns on or resets
}

void loop()
{
  // put code here to have it run over and over again
  while ( millis() < 10000) {
    i+=1;
  }
  Serial.begin(9600);
  Serial.println(i/10);
  delay(10000);
}
