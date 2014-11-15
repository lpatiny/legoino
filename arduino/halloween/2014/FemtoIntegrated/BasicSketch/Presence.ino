#ifdef THR_DISTANCE
NIL_WORKING_AREA(waThreadMeasure, 0);
NIL_THREAD(ThreadMeasure, arg) {
  pinMode(THR_DISTANCE, INPUT); 
  while (TRUE) {   
    setParameter(PARAM_DISTANCE,getDistance(THR_DISTANCE));
    nilThdSleepMilliseconds(250);
  }
}
#endif


#ifdef THR_DETECTION1
NIL_WORKING_AREA(waThreadDetection1, 0);
NIL_THREAD(ThreadDetection1, arg) {

  pinMode(THR_DETECTION1, INPUT); 
  boolean needToWait=true;
  while (TRUE) {
    byte status=digitalRead(THR_DETECTION1);
    setParameter(PARAM_DETECTOR1,status);
    if ((status==1) && needToWait) {
      nilThdSleepMilliseconds(5000); // we keep this status for a while to be sure we catch this event
      needToWait=false;
    }
    if (status!=1) {
      needToWait=true;
    }
    nilThdSleepMilliseconds(100);
  }
}
#endif

#ifdef THR_DETECTION2
NIL_WORKING_AREA(waThreadDetection2, 0);
NIL_THREAD(ThreadDetection2, arg) {

  pinMode(THR_DETECTION2, INPUT); 
  boolean needToWait=true;
  while (TRUE) {
    byte status=digitalRead(THR_DETECTION2);
    setParameter(PARAM_DETECTOR2,status);
    if ((status==1) && needToWait) {
      nilThdSleepMilliseconds(5000); // we keep this status for a while to be sure we catch this event
      needToWait=false;
    }
    if (status!=1) {
      needToWait=true;
    }    
    nilThdSleepMilliseconds(100);
  }
}
#endif




