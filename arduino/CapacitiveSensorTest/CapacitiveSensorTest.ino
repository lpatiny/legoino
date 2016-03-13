#include <CapacitiveSensor.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */

#define OUT1    6
#define OUT2    10   // there was a bug in first version and was set to 8 like IO5
#define OUT3    12
#define OUT4    14
#define OUT5    15
#define IO1     21
#define IO2     20
#define IO3     19
#define IO4     22
#define IO5     8
#define RED1    9
#define GREEN1  11
#define BLUE1   5
#define RED2    16
#define GREEN2  18
#define BLUE2   23



int last=0;
int difference=0;


void setup()                    
{
  pinMode(OUT1, OUTPUT);
  pinMode(IO1, INPUT);
  Serial.begin(9600);

}

void loop()                    
{

  digitalWrite(OUT1, HIGH);
  delay(100);
  long start = micros();
  digitalWrite(OUT1,LOW);
  while(!digitalRead(IO1)) {
  }
  difference=micros() - start;
  Serial.print(difference); 
  Serial.print(" - ");
  Serial.println(difference-last);
  last=difference;
}



