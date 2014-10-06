#ifdef THR_SERVO

#include <Servo.h>

NIL_WORKING_AREA(waThreadServo, 40);
NIL_THREAD(ThreadServo, arg) {

  Servo myservo;  // create servo object to control a servo 

    int servoEventStatus=0;
  int servoIncrease=1; // if we put a byte the increment does not work correctly


  while (TRUE) {
    if (getParameter(PARAM_SERVO_ACTIVE)==1) {
      myservo.attach(THR_SERVO);
      servoEventStatus+=servoIncrease;
      if ((servoEventStatus>getParameter(PARAM_SERVO_TO) && servoIncrease>0) || (servoEventStatus<getParameter(PARAM_SERVO_FROM) && servoIncrease<0)) {
        servoIncrease*=-1;
      }
      myservo.write(servoEventStatus); 
    } 
    else {
      myservo.detach();
    }
    if (getParameter(PARAM_SERVO_DELAY)>0) {
      nilThdSleepMilliseconds(getParameter(PARAM_SERVO_DELAY));
    } 
    else {
      nilThdSleepMilliseconds(5);
    }
  }
}

#endif








