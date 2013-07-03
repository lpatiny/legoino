// Small demonstration of rgb1
// RGB1 is NOT pulseWidth ModulatedThreadRGB1

NIL_WORKING_AREA(waThreadRGB1, 0);
NIL_THREAD(ThreadRGB1, arg) {
  int rgb1EventStatus=0;

  boolean rgb1Red=HIGH;
  boolean rgb1Green=HIGH;
  boolean rgb1Blue=HIGH;
  
  pinMode(RED1, OUTPUT);    
  pinMode(GREEN1, OUTPUT); 
  pinMode(BLUE1, OUTPUT); 

  while (TRUE) {
    rgb1EventStatus++;
    if (rgb1EventStatus%getParameter(PARAM_RGB1)==0) { // random color every 1s
      if (random(2)==1 && getParameter(PARAM_RGB1)!=-1 ) {
        rgb1Red=HIGH;
      } 
      else {
        rgb1Red=LOW;
      }
      if (random(2)==1 && getParameter(PARAM_RGB1)!=-1) {
        rgb1Green=HIGH;
      } 
      else {
        rgb1Green=LOW;
      }
      if (random(2)==1 && getParameter(PARAM_RGB1)!=-1) {
        rgb1Blue=HIGH;
      } 
      else {
        rgb1Blue=LOW;
      }
    }


    digitalWrite(RED1,rgb1Red);
    digitalWrite(GREEN1,rgb1Green);
    digitalWrite(BLUE1,rgb1Blue);

    // Sleep for 200 milliseconds.   
    nilThdSleepMilliseconds(40);
   
  }
}










