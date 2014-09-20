// This is a more complex example showing many simultaneous action
//

#include <NilRTOS.h>

#include <Wire.h>
#include <StepperLight.h>

// Library that allows to start the watch dog allowing automatic reboot in case of crash
// The lowest priority thread should take care of the watch dog
#include <avr/wdt.h>

// The normal serial takes 200 bytes more but is buffered
// And if we send a String for parameters it can not be understand ...
// #include <NilSerial.h>
// #define Serial NilSerial



// http://www.arduino.cc/playground/Code/Time
#include <Time.h>


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



//#define THR_DISTANCE  IO1
#define THR_DETECTION1  IO1
//#define THR_DETECTION2  IO2

#define THR_MONITORING     13  // will also take care of the watch dog
//#define THR_STEPPER      OUT3, IO3
//#define THR_SERVO        IO4

//#define THR_ONE_WIRE	IO5	// we can put a one wire temperature probe on the bus


#define PARAM_RGB1      0
#define PARAM_RGB2      1
#define PARAM_SCAN      2
#define PARAM_SERVO     3

#define PARAM_FIRST_SOUND     4 // we are able to play a random sound between FIRST and LAST
#define PARAM_LAST_SOUND      5
#define PARAM_SOUND_LENGTH    6 // and stop the sound after a define time


#define PARAM_DETECTOR1   7   // set to one if something is detected
#define PARAM_DETECTOR2   8   // set to one if something is detected
#define PARAM_DISTANCE    9


#define PARAM_TEMPERATURE   10  // just for fun we could register temperature

#define PARAM_IRCODE        11  // we could add a IR receiver

#define PARAM_RELAY_1   17    // 17 = R (elay)
#define PARAM_RELAY_2   18


byte IO[]={
  IO1, IO2, IO3, IO4, IO5};

byte OUT[]={
  OUT1, OUT2, OUT3, OUT4, OUT5};

void setup() {
  Serial.begin(9600);
  setupLogger();
  setupDebugger();
  setupParameters();
  nilSysBegin();
}


void loop() {
}










