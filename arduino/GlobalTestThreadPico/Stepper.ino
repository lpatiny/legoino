
#ifdef THR_STEPPER

NIL_WORKING_AREA(waThreadStepper, 0);
NIL_THREAD(ThreadStepper, arg) {
  byte STEPPER[]=THR_STEPPER;
  for (byte i=0; i<sizeof(STEPPER); i++) {
    pinMode(STEPPER[i], OUTPUT);    
  }
  while (TRUE) {
    for (int i=0; i<200; i=i+20) {
      executeStep(i,true, 4, STEPPER[0], STEPPER[1]);
      executeStep(i,false, 4, STEPPER[0], STEPPER[1]);
    }
  }
}

int counter=0;

void executeStep(int numberSteps, boolean forward, byte currentDelay, byte port1, byte port2) {
  while (numberSteps>0) {
    numberSteps--;
    if (forward) {
      counter++;
    }
    else { 
      counter--;
    }
    switch (counter%4) {
    case 0:
      digitalWrite(port1, LOW);
      digitalWrite(port2,LOW);
      break;
    case 1:
      digitalWrite(port1, LOW);
      digitalWrite(port2,HIGH);
      break;
    case 2:
      digitalWrite(port1, HIGH);
      digitalWrite(port2,HIGH);
      break;
    case 3:
      digitalWrite(port1, HIGH);
      digitalWrite(port2,LOW);
      break;
    }
    nilThdSleepMilliseconds(currentDelay);
  }
}

#endif



