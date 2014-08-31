NIL_WORKING_AREA(waThreadAction4, 0);
NIL_THREAD(ThreadAction4, arg) {

  // Initialisation bloc

  pinMode(RED2, OUTPUT);   
  pinMode(GREEN2, OUTPUT);  
  pinMode(BLUE2, OUTPUT);  


  // action block
  int action4Step=0;
  while (TRUE) {

    digitalWrite(RED2,HIGH);
    nilThdSleepMilliseconds(500);
    digitalWrite(RED2,LOW);
    nilThdSleepMilliseconds(0);
    digitalWrite(GREEN2,HIGH);
    nilThdSleepMilliseconds(500);
    digitalWrite(GREEN2,LOW);
    nilThdSleepMilliseconds(0);
    digitalWrite(BLUE2,HIGH);
    nilThdSleepMilliseconds(500);
    digitalWrite(BLUE2,LOW);
    nilThdSleepMilliseconds(500);


  }
}






