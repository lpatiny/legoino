// #define THR_ACTION3 1


NIL_WORKING_AREA(waThreadAction3, 0);
NIL_THREAD(ThreadAction3, arg) {

  // Initialisation bloc

  pinMode(RED1, OUTPUT);   
  pinMode(GREEN1, OUTPUT);  
  pinMode(BLUE1, OUTPUT);  


  // action block
  int action3Step=0;


  while (TRUE) {
    upAndDown(RED1,20);
    upAndDown(GREEN1,20);
    upAndDown(BLUE1,20);
    
    action3Step++;
    setParameter(PARAM_ACTION3, action3Step);
  }

}

void upAndDown(byte output, byte step) {
  for (int i=0;i<255; i=i+step) {
    analogWrite(output,i);
    nilThdSleepMilliseconds(40);
  }
  for (int i=255;i>0; i=i-step) {
    analogWrite(output,i);
    nilThdSleepMilliseconds(40);
  }
}





