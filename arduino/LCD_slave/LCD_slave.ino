// ATTENTION !!!! we need to customize pins_arduino.h to use the crystal pinout !!!!!



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



#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {
    '1','2','3','A'            }
  ,
  {
    '4','5','6','B'            }
  ,
  {
    '7','8','9','C'            }
  ,
  {
    '*','0','#','D'            }
};



byte rowPins[ROWS] = {
   12, 13, 22, 23 }; //conn

 

byte colPins[COLS] = {
      8, 9, 10, 11}; //connect to the row pinouts of the keypad



Keypad keypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 




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



#define  maxSize 10
char buffer[maxSize];
char test[]={'A','B','C','D','E','F','G','H','I'};

byte currentPos=0;

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  // print the number of seconds since reset:

  byte counter=0;
  char key = keypad.getKey();
  if (key){
    if (key=='#') {
      currentPos=0;
    } else {
    buffer[currentPos]=key;
    if (currentPos<(maxSize-1)) {
      currentPos++;
    } else {
      currentPos=0;
    }
    }
    buffer[currentPos]=0;
    for (byte i=currentPos; i<maxSize; i++) {
      buffer[i]=' ';
    }
  } 
}



void requestEvent()
{
//  char bufferTime[6];
//  String millisStr=String(millis());
// millisStr.toCharArray(bufferTime,6);
 // Wire.write(bufferTime);   
  Wire.write(buffer); 
}












