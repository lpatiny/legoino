#ifdef THR_STEPPER

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





