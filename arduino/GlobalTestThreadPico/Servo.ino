#ifdef THR_SERVO

#include <Servo.h>

NIL_WORKING_AREA(waThreadServo, 40);
NIL_THREAD(ThreadServo, arg) {

  Servo myservo;  // create servo object to control a servo 

    int servoEventStatus=0;
  int servoIncrease=1; // if we put a byte the increment does not work correctly
  myservo.attach(THR_SERVO);  // attaches the servo on pin IO6 to the servo object 


  while (TRUE) {
    servoEventStatus+=getParameter(PARAM_SERVO)*servoIncrease;
    if ((servoEventStatus>180 && servoIncrease>0) || (servoEventStatus<1 && servoIncrease<0)) {
      servoIncrease*=-1;
    }
    myservo.write(servoEventStatus); 

    nilThdSleepMilliseconds(20);
  }
}

#endif





