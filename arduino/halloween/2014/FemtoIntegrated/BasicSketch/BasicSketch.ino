// This is a more complex example showing many simultaneous action
//

#include <NilRTOS.h>

#include <Wire.h>


// Library that allows to start the watch dog allowing automatic reboot in case of crash
// The lowest priority thread should take care of the watch dog
#include <avr/wdt.h>

// The normal serial takes 200 bytes more but is buffered
// And if we send a String for parameters it can not be understand ...
// #include <NilSerial.h>
// #define Serial NilSerial



// http://www.arduino.cc/playground/Code/Time
#include <Time.h>

#define VERSION_2014


#ifdef VERSION_2012
#define SERIAL1  Serial
#define OUT1    9
#define OUT2    10
#define OUT3    4
#define OUT4    12
#define OUT5    2
#define OUT6    3
#define IO1 9
#define IO2 10
#define IO3 4
#define IO4 12
#define IO5 2
#define IO6 3

#define RED1   11
#define GREEN1 5
#define BLUE1  6

#define RED2   7
#define GREEN2 13
#define BLUE2  8
//byte IO[]={IO1, IO2, IO3, IO4, IO5, IO6};
//byte OUT[]={OUT1, OUT2, OUT3, OUT4, OUT5, OUT6};
#endif

#ifdef VERSION_2013
#define SERIAL1  Serial1
#define SERIAL0  Serial
#define OUT1    4
#define OUT2    11
#define OUT3    13
#define OUT4    6
#define IO1     8
#define IO2     18
#define IO3     20
#define IO4     19
#define RED1    5
#define GREEN1  9
#define BLUE1   10
#define RED2    21
#define GREEN2  22
#define BLUE2   23
//byte IO[]={IO1, IO2, IO3, IO4};
//byte OUT[]={OUT1, OUT2, OUT3, OUT4};
#endif


#ifdef VERSION_2014
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
byte IO[]={IO1, IO2, IO3, IO4, IO5};

byte OUT[]={OUT1, OUT2, OUT3, OUT4, OUT5};
#endif

//#define THR_DISTANCE  IO1
#define THR_DETECTION1  IO1
//#define THR_DETECTION2  IO2

#define THR_MONITORING     13  // will also take care of the watch dog
//#define THR_STEPPER      OUT3, IO3
//#define THR_SERVO        IO5
//#define THR_ONE_WIRE	   IO5	// we can put a one wire temperature probe on the bus
#define THR_WIRE 1


// #define KEYBOARD_EVENT   "X"







void setup() {
  Serial.begin(9600);
  setupLogger();
  setupDebugger();
  setupParameters();

#ifdef KEYBOARD_EVENT
  Keyboard.begin();
#endif

  nilSysBegin();
}


void loop() {
}











