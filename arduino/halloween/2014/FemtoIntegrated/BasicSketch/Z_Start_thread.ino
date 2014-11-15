
#ifdef THR_MONITORING
// Nice way to make some monitoring about activity. This should be the lower priority process
// If the led is "stable" (blinks 500 times per seconds) it means there are not too
// many activities on the microcontroler
NIL_WORKING_AREA(waThreadMonitoring, 0);
NIL_THREAD(ThreadMonitoring, arg) {

  // we activate the watchdog
  // we need to make a RESET all the time otherwise automatic reboot: wdt_reset();
  wdt_enable(WDTO_8S);

  byte turnOn=0;
  pinMode(THR_MONITORING, OUTPUT);   
  while (TRUE) {
    turnOn=~turnOn;
    digitalWrite(THR_MONITORING,turnOn);
    nilThdSleepMilliseconds(250);
    if (getParameter(PARAM_STATUS)!=99) {
      wdt_reset();
    } 
    else {
      nilThdSleepMilliseconds(750);
    }
  }
}
#endif


NIL_THREADS_TABLE_BEGIN()

// First detection otherwise bad initialized variables !!!!

NIL_THREADS_TABLE_ENTRY(NULL, ThreadZigbee, NULL, waThreadZigbee, sizeof(waThreadZigbee))

#ifdef THR_DISTANCE
NIL_THREADS_TABLE_ENTRY(NULL, ThreadMeasure, NULL, waThreadMeasure, sizeof(waThreadMeasure))
#endif

#ifdef THR_DETECTION1
NIL_THREADS_TABLE_ENTRY(NULL, ThreadDetection1, NULL, waThreadDetection1, sizeof(waThreadDetection1))
#endif

#ifdef THR_DETECTION2
NIL_THREADS_TABLE_ENTRY(NULL, ThreadDetection2, NULL, waThreadDetection2, sizeof(waThreadDetection2))
#endif

#ifdef THR_SERVO
NIL_THREADS_TABLE_ENTRY(NULL, ThreadServo, NULL, waThreadServo, sizeof(waThreadServo))
#endif

#ifdef THR_STEPPER
NIL_THREADS_TABLE_ENTRY(NULL, ThreadStepper, NULL, waThreadStepper, sizeof(waThreadStepper))
#endif

#ifdef THR_ACTION1
NIL_THREADS_TABLE_ENTRY(NULL, ThreadAction1, NULL, waThreadAction1, sizeof(waThreadAction1))
#endif

#ifdef THR_ACTION2
NIL_THREADS_TABLE_ENTRY(NULL, ThreadAction2, NULL, waThreadAction2, sizeof(waThreadAction2))
#endif

#ifdef THR_ACTION3
NIL_THREADS_TABLE_ENTRY(NULL, ThreadAction3, NULL, waThreadAction3, sizeof(waThreadAction3))
#endif

#ifdef THR_ACTION4
NIL_THREADS_TABLE_ENTRY(NULL, ThreadAction4, NULL, waThreadAction4, sizeof(waThreadAction4))
#endif

#ifdef THR_ONE_WIRE
NIL_THREADS_TABLE_ENTRY(NULL, ThreadOneWire, NULL, waThreadOneWire, sizeof(waThreadOneWire))                           
#endif


NIL_THREADS_TABLE_ENTRY(NULL, ThreadSerial, NULL, waThreadSerial, sizeof(waThreadSerial))

#ifdef THR_WIRE
NIL_THREADS_TABLE_ENTRY(NULL, ThreadWire, NULL, waThreadWire, sizeof(waThreadWire))
#endif

#ifdef THR_MONITORING
NIL_THREADS_TABLE_ENTRY(NULL, ThreadMonitoring, NULL, waThreadMonitoring, sizeof(waThreadMonitoring))                           
#endif


NIL_THREADS_TABLE_END()






