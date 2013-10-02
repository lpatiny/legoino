#ifndef StepperLight_h
#define StepperLight_h

#include "Arduino.h"

class StepperLight {
public:
  StepperLight(byte pin1, byte pin2);
  void forward();
  void backward();
private:
  byte _position;
  byte _pin1;
  byte _pin2;
  void execute();
};
#endif