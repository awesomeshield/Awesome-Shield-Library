/* print the number of times this sketch loops per second
   using a 1 second sample
*/

long i = 0;
int startMillis = 0;

void setup()
{
  awesome.setup(9600);
  startMillis = millis();
}

void loop()
{
  // put code here to have it run over and over again
  if ( millis() - startMillis < 1000) {
    i+=1;
  } else {
    Serial.println(i);
  }
}
