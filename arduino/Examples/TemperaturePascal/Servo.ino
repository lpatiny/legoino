#include <Servo.h>


// Small demonstration of a servo

Servo myservo;  // create servo object to control a servo 


int servoEventStatus=0;
int servoIncrement=1;

void setupEventServo() {
  myservo.attach(IO6);  // attaches the servo on pin IO6 to the servo object 
}

void runEventServo() {
  servoEventStatus+=servoIncrement;
  if ((servoEventStatus>180 && servoIncrement>0) || (servoEventStatus<1 && servoIncrement<0)) {
    servoIncrement*=-1;
  }
  myservo.write(servoEventStatus); 

}


