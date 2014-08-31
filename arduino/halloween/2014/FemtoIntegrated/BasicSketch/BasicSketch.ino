// This is a more complex example showing many simultaneous action
//

#include <NilRTOS.h>

#include <Wire.h>
#include <LiquidCrystal.h>
#include <StepperLight.h>


// The normal serial takes 200 bytes more but is buffered
// And if we send a String for parameters it can not be understand ...
// #include <NilSerial.h>
// #define Serial NilSerial



// http://www.arduino.cc/playground/Code/Time
#include <Time.h>


#define OUT1    6
#define OUT2    8
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



//#define THR_DISTANCEPIN    IO2
#define THR_DEGECTIONPIN1  IO3
//#define THR_DEGECTIONPIN2  IO4

#define THR_MONITORING   13  // INCOMPATIBLE WITH OUT3
//#define THR_IRPIN        12
//#define THR_STEPPER      OUT2, IO2
//#define THR_SERVO        IO4

#define THR_ONE_WIRE
#define TEMPERATURE_1  IO4
//#define TEMPERATURE_2  IO5


#define PARAM_RGB1      0
#define PARAM_RGB2      1
#define PARAM_SCAN      2
#define PARAM_SERVO     3

#define PARAM_SOUND     4

#define PARAM_DETECTOR1   7   // set to one if something is detected
#define PARAM_DETECTOR2   8   // set to one if something is detected
#define PARAM_DISTANCE    9


#define PARAM_TEMP1      10
#define PARAM_TEMP2      11

#define PARAM_IRCODE     12

#define PARAM_RELAY_1   17// = 17 = R (elay)
#define PARAM_RELAY_2   18




#define PARAM_PRESENCE  23
#define PARAM_WIRE      24 // contains the active wire devices


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










