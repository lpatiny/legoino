/*
  Blink
 Turns on an LED on for one second, then off for one second, repeatedly.
 
 This example code is in the public domain.
 */

#define OUT1    2
#define OUT2    4
#define OUT3    9
#define OUT4    10
#define IO1     A0
#define IO2     A1
#define IO3     A2
#define IO4     A3
#define RED1    5
#define GREEN1  6
#define BLUE1   11
#define RED2    7
#define GREEN2  8
#define BLUE2   13

#define TEST {2,4,9,10,5,6,11,7,8,13,A0,A1,A2,A3}

byte test[]=TEST;
void setup() {                

  
  for (int i=0; i<sizeof(test); i++) {
    pinMode(test[i], OUTPUT);
  }
}

void loop() {
  for (int i=0; i<sizeof(test); i++) {
    digitalWrite(test[i], HIGH);
    delay(200);
  }
  delay(500);              // wait for a second
  for (int i=0; i<sizeof(test); i++) {
    digitalWrite(test[i], LOW);
    delay(200);
  }  
  delay(500);              // wait for a second
}

