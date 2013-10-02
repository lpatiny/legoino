
#include "Arduino.h"
#include "StepperLight.h"



StepperLight::StepperLight(byte pin1, byte pin2) {
  _pin1=pin1;
  _pin2=pin2;
  pinMode(_pin1, OUTPUT);
  pinMode(_pin2, OUTPUT);
  _position=0;
}
void StepperLight::forward() {
  _position++;
  if (_position==4) _position=0;
  execute();
}
void StepperLight::backward() {
  _position--;
  if (_position==255) _position=3;
  execute();
}

void StepperLight::execute() {
  switch (_position) {
  case 0:
    digitalWrite(_pin1, LOW);
    digitalWrite(_pin2,LOW);
    break;
  case 1:
    digitalWrite(_pin1, HIGH);
    digitalWrite(_pin2,LOW);
    break;
  case 2:
    digitalWrite(_pin1, LOW);
    digitalWrite(_pin2,HIGH);
    break;
  case 3:
    digitalWrite(_pin1, HIGH);
    digitalWrite(_pin2,HIGH);
    break;
  }
}

