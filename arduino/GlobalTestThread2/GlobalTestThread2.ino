// This is a more complex example showing many simultaneous action
//

#include <NilRTOS.h>

#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>

// The normal serial takes 200 bytes more but is buffered
// And if we send a String for parameters it can not be understand ...
// #include <NilSerial.h>
// #define Serial NilSerial

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
#define PARAM_WIRE      24 // contains the active wire devices
#define PARAM_DISTANCE  25

byte IO[]={
  IO1, IO2, IO3, IO4, IO5, IO6};

void setup() {
  setupLogger();
  setupDebugger();
  setupParameters();
  nilSysBegin();
}


void loop() {
}









