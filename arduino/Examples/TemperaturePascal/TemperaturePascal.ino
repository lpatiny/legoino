// This is a more complex example showing many simultaneous action
//
#include <Wire.h>

#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>

#include <SimpleTimer.h>


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


#define PARAM_RGB1    0
#define PARAM_RGB2    1
#define PARAM_SCAN    2
#define PARAM_TEMP1   20
#define PARAM_DISTANCE   25

byte IO[]={
  IO1, IO2, IO3, IO4, IO5, IO6};


unsigned int currentInterrupt;

SimpleTimer timer;

void setup() {
  Serial.begin(9600);
  setupWire();
  timer.setInterval(10, loopFunction);
  setupLogger();
  setupDebugger();
  setupParameters();
  setupEventRgb1();
  setupEventRgb2();
  setupEventIO();
  //setupEventServo();
  // the following function is a real time interrupt
  setupInterrupt();

  setupOneWire();
  // timer.setInterval(2000, loopOneWire);
  
  setupPascal();
  timer.setInterval(getParameter(24), loopPascal);

}

void loop() {
  // everything is managed by the timer that is a "best effort" function
  // we initialize it to be excute every 1mS
  timer.run();
}


// this function is based on "Best effort"
void loopFunction() {
  currentInterrupt++;

  int modulo=currentInterrupt%4;

  // Event that should be done every millisecond

  switch (modulo) { // events 25 times per second
  case 0:
  //  runEventRgb1();
    break;
  case 1:
  //  runEventRgb2();
    break;
  case 2:
  //  runEventIO();
    break;
  case 3:
  //  runEventServo();
    break;
  }



  modulo=currentInterrupt%100;
  switch (modulo) { // seconds event
  case 0:
    wireUpdateList();
    runWire();
    break;
  case 1:
    setParameter(PARAM_DISTANCE,getDistance(ANALOG2));
    break;  

  }

}








