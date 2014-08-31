NIL_WORKING_AREA(waThreadAction2, 0);
NIL_THREAD(ThreadAction2, arg) {

  // Initialisation bloc





  // action block
  int action2Step=0;

  for (byte i=0; i<sizeof(IO); i++) {
    pinMode(IO[i], OUTPUT);   
  }

  while (TRUE) {
    for (byte i=0; i<sizeof(IO); i++) {
      digitalWrite(IO[i], HIGH);   
      nilThdSleepMilliseconds(500);  // 25 times per seconds
      digitalWrite(IO[i], LOW);   
      nilThdSleepMilliseconds(500);  // 25 times per seconds
    }
  }


}





