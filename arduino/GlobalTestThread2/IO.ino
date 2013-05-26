NIL_WORKING_AREA(waThreadIO, 0);
NIL_THREAD(ThreadIO, arg) {

  unsigned int IOEventStatus=0;
  unsigned int IOEventStatusCounter=0;



  for (int i=0; i<4; i++) {
    pinMode(IO[i], OUTPUT);    
  }


  while (TRUE) {
    IOEventStatusCounter++;
    if (IOEventStatusCounter%getParameter(PARAM_SCAN)==0) {
      IOEventStatus++;
    }
    for (int i=0; i<4; i++) {
      if (i!=IOEventStatus%4) {
        digitalWrite(IO[i],LOW);
      } 
      else {
        digitalWrite(IO[i],HIGH);
      }
    }
    // Add ticks for one second.  The MS2ST macro converts ms to system ticks.
    // int wakeTime = MS2ST(1000);
    
    
    nilThdSleepMilliseconds(40);
  }
}



