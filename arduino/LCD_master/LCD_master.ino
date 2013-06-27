#include <Wire.h>

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
}

void loop()
{
  Wire.beginTransmission(4); // transmit to device #4
  Wire.write(0); // row
  Wire.write(0+4); // column
  Wire.write("First line");        // sends five bytes
  Wire.endTransmission();    // stop transmitting

  delay(1000);

  Wire.beginTransmission(4); // transmit to device #4
  Wire.write(1); // row
  Wire.write(10+4); // column
  Wire.write("Second");        // sends five bytes
  Wire.endTransmission();    // stop transmitting

  delay(1000);

  Wire.beginTransmission(4); // transmit to device #4
  Wire.write(2); // row
  Wire.write(0+4); // column
  Wire.write("Third line");        // sends five bytes
  Wire.endTransmission();    // stop transmitting

  delay(1000);

  for (byte i=0; i<50; i++) {
    Wire.beginTransmission(4); // transmit to device #4
    Wire.write(3); // row
    Wire.write(0+4); // column
    String millisStr=String(millis());
    char buffer[20];
    millisStr.toCharArray(buffer,20);
    Wire.write(buffer);        // code ASCII 26 clears the screen
    Wire.endTransmission();    // stop transmitting
    delay(100);
  }



  Wire.beginTransmission(4); // transmit to device #4
  Wire.write(2); // row
  Wire.write(0+4); // column
  Wire.write(26);        // code ASCII 26 clears the screen
  Wire.endTransmission();    // stop transmitting

  delay(500);

  Wire.beginTransmission(4); // transmit to device #4
  Wire.write(2); // row
  Wire.write(0+4); // column
  Wire.write(25);        // off screen
  Wire.endTransmission();    // stop transmitting

  delay(500);

  Wire.beginTransmission(4); // transmit to device #4
  Wire.write(0); // row
  Wire.write(0+4); // column
  Wire.write(24);        // on screen
  Wire.endTransmission();    // stop transmitting
  
}




