NIL_WORKING_AREA(waThreadAction3, 0);
NIL_THREAD(ThreadAction3, arg) {

  // Initialisation bloc

  pinMode(RED1, OUTPUT);   
  pinMode(GREEN1, OUTPUT);  
  pinMode(BLUE1, OUTPUT);  


  // action block
  int action3Step=0;
  while (TRUE) {

    analogWrite(RED1,127);
    nilThdSleepMilliseconds(500);
        analogWrite(RED1,0);
    nilThdSleepMilliseconds(0);
    analogWrite(GREEN1,127);
    nilThdSleepMilliseconds(500);
        analogWrite(GREEN1,0);
    nilThdSleepMilliseconds(0);
    analogWrite(BLUE1,127);
    nilThdSleepMilliseconds(500);
    analogWrite(BLUE1,0);
    nilThdSleepMilliseconds(500);


  }
}





