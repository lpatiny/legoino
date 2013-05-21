#include <Servo.h>


// Small demonstration of a servo

Servo myservo;  // create servo object to control a servo 


int servoEventStatus=0;
int servoIncrease=1;

void setupEventServo() {
  myservo.attach(IO6);  // attaches the servo on pin IO6 to the servo object 
}

void runEventServo() {
  servoEventStatus+=getParameter(PARAM_SERVO)*servoIncrease;
  if ((servoEventStatus>180 && servoIncrease>0) || (servoEventStatus<1 && servoIncrease<0)) {
    servoIncrease*=-1;
  }
  myservo.write(servoEventStatus); 

}


