#include <avr/io.h>

// Author: Luc Patiny
// we just make a program that copies from Serial to Serial1 and reverse

void setup()
{ 
  delay(2000);
  Serial.begin(9600);
  Serial1.begin(38400);
}


void loop() 
{
  // we copy from Serial1 to Serial
  if (Serial1.available()) {
    // Serial.println(Serial.available());
    char temp = Serial1.read();
    Serial.print(temp);
  } 
  else {
   // Serial.println("Not Available"); 
  }

  // we copy from Serial1 to Serial
  if (Serial.available()) {
    Serial1.write(Serial.read());
  }
}




