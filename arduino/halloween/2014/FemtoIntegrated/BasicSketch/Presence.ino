#ifdef THR_DISTANCEPIN
NIL_WORKING_AREA(waThreadMeasure, 0);
NIL_THREAD(ThreadMeasure, arg) {
  pinMode(THR_DISTANCEPIN, INPUT); 
  while (TRUE) {   
    setParameter(PARAM_DISTANCE,getDistance(THR_DISTANCEPIN));
    nilThdSleepMilliseconds(250);
  }
}
#endif


#ifdef THR_DEGECTIONPIN1
NIL_WORKING_AREA(waThreadDetection1, 0);
NIL_THREAD(ThreadDetection1, arg) {
  pinMode(THR_DEGECTIONPIN1, INPUT); 
  while (TRUE) {   
    setParameter(PARAM_DETECTOR1,digitalRead(THR_DEGECTIONPIN1));
    nilThdSleepMilliseconds(100);
  }
}
#endif

#ifdef THR_DEGECTIONPIN2
NIL_WORKING_AREA(waThreadDetection2, 0);
NIL_THREAD(ThreadDetection2, arg) {
  pinMode(THR_DEGECTIONPIN2, INPUT); 
  while (TRUE) {   
    setParameter(PARAM_DETECTOR2,digitalRead(THR_DEGECTIONPIN2));
    nilThdSleepMilliseconds(100);
  }
}
#endif



