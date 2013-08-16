NIL_WORKING_AREA(waThreadMeasure, 0);
NIL_THREAD(ThreadMeasure, arg) {
  while (TRUE) {   
    setParameter(PARAM_DISTANCE,getDistance(ANALOG2));
    nilThdSleepMilliseconds(1000);
  }
}


// Nice way to make some monitoring about activity. This should be the lower priority process
// If the led is "stable" (blinks 500 times per seconds) it means there are not too
// many activities on the microcontroler
NIL_WORKING_AREA(waThreadMonitoring, 0);
NIL_THREAD(ThreadMonitoring, arg) {
  boolean turnOn=true;
  pinMode(IO5, OUTPUT);   
  while (TRUE) {
    if (turnOn) {
      turnOn=false;
      digitalWrite(IO5,HIGH);
    } 
    else {
      turnOn=true;
      digitalWrite(IO5,LOW);
    }
    nilThdSleepMilliseconds(1);
  }
}


NIL_THREADS_TABLE_BEGIN()


NIL_THREADS_TABLE_ENTRY(NULL, ThreadIO, NULL, waThreadIO, sizeof(waThreadIO))
NIL_THREADS_TABLE_ENTRY(NULL, ThreadRGB1, NULL, waThreadRGB1, sizeof(waThreadRGB1))
NIL_THREADS_TABLE_ENTRY(NULL, ThreadRGB2, NULL, waThreadRGB2, sizeof(waThreadRGB2))
NIL_THREADS_TABLE_ENTRY(NULL, ThreadMeasure, NULL, waThreadMeasure, sizeof(waThreadMeasure))
NIL_THREADS_TABLE_ENTRY(NULL, ThreadSerial, NULL, waThreadSerial, sizeof(waThreadSerial))

/*
NIL_THREADS_TABLE_ENTRY(NULL, ThreadServo, NULL, waThreadServo, sizeof(waThreadServo))
*/
NIL_THREADS_TABLE_ENTRY(NULL, ThreadWire, NULL, waThreadWire, sizeof(waThreadWire))

// NIL_THREADS_TABLE_ENTRY(NULL, ThreadOneWire, NULL, waThreadOneWire, sizeof(waThreadOneWire))
NIL_THREADS_TABLE_ENTRY(NULL, ThreadMonitoring, NULL, waThreadMonitoring, sizeof(waThreadMonitoring))
NIL_THREADS_TABLE_END()


