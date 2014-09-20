NIL_WORKING_AREA(waThreadAction2, 0);
NIL_THREAD(ThreadAction2, arg) {



  while (TRUE) {
    if (getParameter(25)<sizeof(IO)){
      byte i=(byte)getParameter(25);

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
    nilThdSleepMilliseconds(50);
  }




}













