#ifdef THR_DISTANCEPIN
NIL_WORKING_AREA(waThreadMeasure, 0);
NIL_THREAD(ThreadMeasure, arg) {
  while (TRUE) {   
    setParameter(PARAM_DISTANCE,getDistance(THR_DISTANCEPIN));
    nilThdSleepMilliseconds(1000);
  }
}
#endif

// Nice way to make some monitoring about activity. This should be the lower priority process
// If the led is "stable" (blinks 500 times per seconds) it means there are not too
// many activities on the microcontroler
NIL_WORKING_AREA(waThreadMonitoring, 0);
NIL_THREAD(ThreadMonitoring, arg) {
  boolean turnOn=true;
  pinMode(THR_MONITORING, OUTPUT);   
  while (TRUE) {
    if (turnOn) {
      turnOn=false;
      digitalWrite(THR_MONITORING,HIGH);
    } 
    else {
      turnOn=true;
      digitalWrite(THR_MONITORING,LOW);
    }
    nilThdSleepMilliseconds(1);
  }
}


NIL_THREADS_TABLE_BEGIN()

NIL_THREADS_TABLE_ENTRY(NULL, ThreadStepper, NULL, waThreadStepper, sizeof(waThreadStepper))

//NIL_THREADS_TABLE_ENTRY(NULL, ThreadIO, NULL, waThreadIO, sizeof(waThreadIO))
NIL_THREADS_TABLE_ENTRY(NULL, ThreadRGB1, NULL, waThreadRGB1, sizeof(waThreadRGB1))
NIL_THREADS_TABLE_ENTRY(NULL, ThreadRGB2, NULL, waThreadRGB2, sizeof(waThreadRGB2))

#ifdef THR_SERVO
NIL_THREADS_TABLE_ENTRY(NULL, ThreadServo, NULL, waThreadServo, sizeof(waThreadServo))
#endif

#ifdef THR_DISTANCEPIN
NIL_THREADS_TABLE_ENTRY(NULL, ThreadMeasure, NULL, waThreadMeasure, sizeof(waThreadMeasure))
#endif

NIL_THREADS_TABLE_ENTRY(NULL, ThreadSerial, NULL, waThreadSerial, sizeof(waThreadSerial))

#ifdef THR_IRPIN 
NIL_THREADS_TABLE_ENTRY(NULL, ThreadIRReceiver, NULL, waThreadIRReceiver, sizeof(waThreadIRReceiver))
#endif

NIL_THREADS_TABLE_ENTRY(NULL, ThreadWire, NULL, waThreadWire, sizeof(waThreadWire))

#ifdef ONE_WIRE_BUS1
NIL_THREADS_TABLE_ENTRY(NULL, ThreadOneWire, NULL, waThreadOneWire, sizeof(waThreadOneWire))
#endif

#ifdef THR_MONITORING 
NIL_THREADS_TABLE_ENTRY(NULL, ThreadMonitoring, NULL, waThreadMonitoring, sizeof(waThreadMonitoring))
#endif

NIL_THREADS_TABLE_END()




