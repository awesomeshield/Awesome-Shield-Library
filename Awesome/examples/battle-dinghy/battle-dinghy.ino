/*
Goals
[x] take input (x,y) of dinghy location via serial
[ ] take inputs of guesses at locations
[ ] map results of guesses
[ ] give feedback as to correct or incorrect guess (blue = water, red = boat)
Bonus:
[ ] 2 player
[ ] 1 player random dingy location
[ ] 2x1 sized piece
*/

// the next line tells the Arduino you're using the Awesome Shield library
#include <Awesome.h>
// the next line tells the Arduino you're using the Awesome Shield itself
Awesome awesome;


// 2D Array to create the blank board
char board[5][5] = {
{'W','W','W','W','W'},
{'W','W','W','W','W'},
{'W','W','W','W','W'},
{'W','W','W','W','W'},
{'W','W','W','W','W'}
};

// X- and Y-coordinates of the dinghy location
int dinghyLocationX;
int dinghyLocationY;

void setup()
{
  Serial.begin(9600);

  // take number input
  Serial.println("You'll need a very clever hiding place for your dinghy.\nThe location is represented by a number between 1 and 5,\nand a letter between A and E.\nPlease type the number, and hit enter.");
  while ( ! Serial.available() ) {
    // do nothing
  }
  String inputString = Serial.readString();
  int inputInt = inputString.toInt();
  // check type and ask for another input if not 0 < int < 6
  Serial.print("Your number is: ");
  Serial.println(inputInt);

  // take letter input
  Serial.println("Please type the letter, and hit enter.");
  while ( ! Serial.available() ) {
    // do nothing
  }
  inputString = Serial.readString();
  char inputChar = inputString[0];
  // check type and ask for another input if not 0 < int < 6
  Serial.print("Your letter is: ");
  Serial.println(inputChar);
}

void loop()
{
  // put code here to have it run over and over again
}
