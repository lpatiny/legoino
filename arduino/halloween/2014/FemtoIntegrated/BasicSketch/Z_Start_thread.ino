

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

// First detection otherwise bad initialized variables !!!!

NIL_THREADS_TABLE_ENTRY(NULL, ThreadZigbee, NULL, waThreadZigbee, sizeof(waThreadZigbee))

#ifdef THR_DISTANCEPIN
NIL_THREADS_TABLE_ENTRY(NULL, ThreadMeasure, NULL, waThreadMeasure, sizeof(waThreadMeasure))
#endif

#ifdef THR_DEGECTIONPIN1
NIL_THREADS_TABLE_ENTRY(NULL, ThreadDetection1, NULL, waThreadDetection1, sizeof(waThreadDetection1))
#endif

#ifdef THR_DEGECTIONPIN2
NIL_THREADS_TABLE_ENTRY(NULL, ThreadDetection2, NULL, waThreadDetection2, sizeof(waThreadDetection2))
#endif



NIL_THREADS_TABLE_ENTRY(NULL, ThreadAction1, NULL, waThreadAction1, sizeof(waThreadAction1))
NIL_THREADS_TABLE_ENTRY(NULL, ThreadAction2, NULL, waThreadAction2, sizeof(waThreadAction2))
NIL_THREADS_TABLE_ENTRY(NULL, ThreadAction3, NULL, waThreadAction3, sizeof(waThreadAction3))
NIL_THREADS_TABLE_ENTRY(NULL, ThreadAction4, NULL, waThreadAction4, sizeof(waThreadAction4))

#ifdef THR_ONE_WIRE
NIL_THREADS_TABLE_ENTRY(NULL, ThreadOneWire, NULL, waThreadOneWire, sizeof(waThreadOneWire))                           
#endif


NIL_THREADS_TABLE_ENTRY(NULL, ThreadSerial, NULL, waThreadSerial, sizeof(waThreadSerial))



NIL_THREADS_TABLE_ENTRY(NULL, ThreadWire, NULL, waThreadWire, sizeof(waThreadWire))



NIL_THREADS_TABLE_END()




