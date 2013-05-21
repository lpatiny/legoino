// This is a more complex example showing many simultaneous action
//

#include <NilRTOS.h>

#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>

#include <NilSerial.h>
#define Serial NilSerial

// We want to save and load easily from EEPROM
#include <EEPROM.h>
#include <EXROM.h>

// http://www.arduino.cc/playground/Code/Time
#include <Time.h>



#define   IO1    9
#define   IO2   10
#define   IO3    4
#define   IO4   12
#define   IO5    2
#define   IO6    3


#define   RED1   11
#define   GREEN1  5
#define   BLUE1   6

#define   RED2    7
#define   GREEN2 13
#define   BLUE2   8

#define   ANALOG1 A1
#define   ANALOG2 A2


#define PARAM_RGB1      0
#define PARAM_RGB2      1
#define PARAM_SCAN      2
#define PARAM_SERVO     3
#define PARAM_RELAY_1   17// = 17 = R (elay)
#define PARAM_RELAY_2   18
#define PARAM_TEMP1     20
#define PARAM_DISTANCE  25


byte IO[]={
  IO1, IO2, IO3, IO4, IO5, IO6};









void setup() {
  Serial.begin(9600);
//  setupWire();
  //  timer.setInterval(10, loopFunction);
  setupLogger();
  setupDebugger();
  setupParameters();


//  setupEventServo();
  // the following function is a real time interrupt
//  setupInterrupt();

  setupOneWire();
  // timer.setInterval(5000, loopOneWire);


  nilSysBegin();
}

void loop() {
  // everything is managed by the timer that is a "best effort" function
  // we initialize it to be execute every 1mS
  // timer.run();
}


// this function is based on "Best effort"
void loopFunction() {
  // Event that should be done every millisecond
  // events 25 times per second
  runEventServo();
  // seconds event
  wireUpdateList();
  runWire();
  setParameter(PARAM_DISTANCE,getDistance(ANALOG2));
}









