/*
I2C slave program
 
 byte 1: address: 2 ways depending the application
 000XXXXX the address of the pin
 
 or
 
 06543210
 Directly the corresponding bit with getBit and setBit
 

 
 byte2-: function + paraemters
 ID                  parameter          description
 0: nothing          -                  default action we do nothing
 1: on               -                  selectedID off
 2: off              -                  selectedID on
 3: setIntensity     byte               need to support PWM !!!
 4: setColor         byte (RGB bits)
 5: setRGB      3 bytes            need to support PWM !!!
 
 
 */

#include <NilRTOS.h>

#include <Wire.h>


// The normal serial takes 200 bytes more but is buffered
// And if we send a String for parameters it can not be understand ...
// #include <NilSerial.h>
// #define Serial NilSerial



// http://www.arduino.cc/playground/Code/Time
#include <Time.h>



#define SLAVE_ADDRESS  4

// Definition for an Default NANO ATMEGA328
#define RED1     7
#define GREEN1   8
#define BLUE1    13
#define RED2     5
#define GREEN2   6
#define BLUE2    11
#define LED3     4
#define LED4     10
#define LED5     9
#define LED6     3

// Definition for an Default PICO ATMEGA32U4
#define RED1    5
#define GREEN1  9
#define BLUE1   10
#define RED2    21
#define GREEN2  22
#define BLUE2   23
#define LED3    4
#define LED4    11
#define LED5    13
#define LED6    6

// Definition for module 10 I/O
// IO5 is on PB6
// PWM on: 3, 5, 6, 9, 10, 11 (OUT4, OUT6, OUT7, OUT9, IO1, IO2)
#define OUT1    0
#define OUT2    1
#define OUT3    2
#define OUT4    3
#define OUT5    4
#define OUT6    5
#define OUT7    6
#define OUT8    7
#define OUT9    9
#define OUT10   8
#define IO1     10
#define IO2     11
#define IO3     12
#define IO4     13
#define IO5     22
#define IO6     A0
#define IO7     A1
#define IO8     A2
#define IO9     23
#define IO10    A3


byte LEDS[]={
  OUT1, OUT2, OUT3, OUT4, OUT5, OUT6, OUT7, OUT8, OUT9, OUT10,
  IO1, IO2, IO3, IO4, IO5, IO6, IO7, IO8, IO9, IO10};

/*
byte LEDS[]={
 RED1, GREEN1, BLUE1, RED2, GREEN2, BLUE2, LED3, LED4, LED5, LED6};
 */


// #define THR_MONITORING   2  // INCOMPATIBLE WITH OUT3

#define PARAM_RGB1      0
#define PARAM_RGB2      1



void setup() {
  setupLogger();
  setupDebugger();
  setupParameters();

  for (byte i=0; i<sizeof(LEDS); i++) {
    pinMode(LEDS[i], OUTPUT);  
    setParameter(i,0);
  }
  //Serial.begin(9600);
  nilSysBegin();
}

void loop() {
}













