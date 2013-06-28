
#include <LiquidCrystal.h>
#include <Wire.h>

#define lcd_rs   A0
#define lcd_e    A1
#define lcd_lite A2

// we will play with ASCII code to control the slave LCD screen
// all that is under 32 (ASCII) will be considred as instruction
// 0->3 : the row
// 4->23 : the column
// 24: light on
// 25: light off
// 26: clear


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(lcd_rs, lcd_e, 0,1,2,3,4,5,6,7);

void setup() {
  // turn on the screen
  pinMode(lcd_lite, OUTPUT);
  digitalWrite(lcd_lite,HIGH);
  lcd.begin(20, 4);
  // Print a message to the LCD.
  lcd.print("hello, world!");

  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); // register event
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  // print the number of seconds since reset:
  delay(500);
}


char lcdRow=0;
char lcdColumn=0;

void receiveEvent(int howMany)
{
  while(Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    if (c<4) {
      lcdRow=c;
      lcd.setCursor(lcdColumn, lcdRow);
    } 
    else if (c<24) {
      lcdColumn=c-4; 
      lcd.setCursor(lcdColumn, lcdRow);
    } 
    else if (c==24) {
      digitalWrite(lcd_lite,HIGH);
    } 
    else if (c==25) {
      digitalWrite(lcd_lite,LOW);
    } 
    else if (c==26) {
      lcd.clear();
    } 
    else {
      lcd.print(c);         // print the character
    }
  }
}

void requestEvent()
{
  String millisStr=String(millis());
  char buffer[20];
  millisStr.toCharArray(buffer,20);
  Wire.write(buffer);        // code ASCII 26 clears the screen

}






