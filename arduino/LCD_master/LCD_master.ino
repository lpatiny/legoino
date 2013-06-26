#include <Wire.h>

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
}

void loop()
{
  lcdPrint(0x00,0x00,'Hello');
  delay(2000);
  lcdPrint(1,0,"Test");
    delay(1000);
  lcdPrint(2,0,"Second Test");
  delay(1000);
  lcdPrint(0,0,"            ");
  lcdPrint(1,0,"            ");
  lcdPrint(2,0,"            ");
  
}


void lcdPrint(byte row, byte col, char message[]) {
  Wire.beginTransmission(4); // transmit to device #4
  Wire.write(row);
  Wire.write(col+4);
  Wire.write(message);        // sends five bytes
  Wire.endTransmission();    // stop transmitting
}

