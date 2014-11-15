#ifdef THR_STEPPER

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

// type 1: 0 1 2 3
// type 2: 0 2 1 3


void StepperLight::execute() {
  switch (_position) {
  case 0:
    digitalWrite(_pin1, LOW);
    digitalWrite(_pin2,LOW);
    break;
  case 2:
    digitalWrite(_pin1, HIGH);
    digitalWrite(_pin2,LOW);
    break;
  case 1:
    digitalWrite(_pin1, LOW);
    digitalWrite(_pin2,HIGH);
    break;
  case 3:
    digitalWrite(_pin1, HIGH);
    digitalWrite(_pin2,HIGH);
    break;
  }
}



NIL_WORKING_AREA(waThreadStepper, 0);
NIL_THREAD(ThreadStepper, arg) {

  StepperLight stepper1(THR_STEPPER);

  while(true) {
    for (int i=0; i<400; i++) {
      stepper1.forward();
      nilThdSleepMilliseconds(20);
    }
    for (int i=0; i<400; i++) {
      stepper1.backward();
      nilThdSleepMilliseconds(20);
    }
  }
}

#endif





