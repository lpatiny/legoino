#define THR_ACTION2 1

NIL_WORKING_AREA(waThreadAction2, 0);
NIL_THREAD(ThreadAction2, arg) {

  int action2Step=0;

  while (TRUE) {
    if (getParameter(PARAM_STATUS)<sizeof(IO)){
      byte i=(byte)getParameter(PARAM_STATUS);

      pinMode(IO[i], OUTPUT); 
      pinMode(OUT[i], OUTPUT); 


      digitalWrite(IO[i], HIGH); 
      digitalWrite(OUT[i], LOW);
      nilThdSleepMilliseconds(250);
      digitalWrite(IO[i], LOW); 
      digitalWrite(OUT[i], HIGH);
      nilThdSleepMilliseconds(750);
      digitalWrite(OUT[i], LOW); 
    }

    setParameter(PARAM_ACTION2, action2Step);
    nilThdSleepMilliseconds(40);
  }




}














