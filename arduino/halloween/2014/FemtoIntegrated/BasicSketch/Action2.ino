#define THR_ACTION2 1

NIL_WORKING_AREA(waThreadAction2, 0);
NIL_THREAD(ThreadAction2, arg) {

  int action2Step=0;

  pinMode(RED1, OUTPUT);   
  pinMode(GREEN1, OUTPUT);  
  pinMode(BLUE1, OUTPUT); 

  while (TRUE) {

    analogWrite(RED1, getParameter(PARAM_VAR1));
    analogWrite(GREEN1, getParameter(PARAM_VAR1));
    analogWrite(BLUE1, getParameter(PARAM_VAR1));


    action2Step++;
    setParameter(PARAM_ACTION2, action2Step);
    nilThdSleepMilliseconds(40);
  }




}















