NIL_WORKING_AREA(waThreadMem, 100);
NIL_THREAD(ThreadMem, arg) {
  Serial.begin(9600);  
  while (TRUE) {   
    nilPrintUnusedStack(&Serial);
    nilThdSleepMilliseconds(1000);
  }
}

NIL_WORKING_AREA(waThread7, 100);
NIL_THREAD(Thread7, arg) {
  while (TRUE) {   
    setParameter(PARAM_DISTANCE,getDistance(ANALOG2));
    nilThdSleepMilliseconds(1000);
  }
}

 


NIL_THREADS_TABLE_BEGIN()
NIL_THREADS_TABLE_ENTRY(NULL, Thread0, NULL, waThread0, sizeof(waThread0))
NIL_THREADS_TABLE_ENTRY(NULL, Thread1, NULL, waThread1, sizeof(waThread1))
NIL_THREADS_TABLE_ENTRY(NULL, Thread2, NULL, waThread2, sizeof(waThread2))
NIL_THREADS_TABLE_ENTRY(NULL, Thread3, NULL, waThread3, sizeof(waThread3))
NIL_THREADS_TABLE_ENTRY(NULL, Thread4, NULL, waThread4, sizeof(waThread4))
//NIL_THREADS_TABLE_ENTRY(NULL, Thread5, NULL, waThread5, sizeof(waThread5))
//NIL_THREADS_TABLE_ENTRY(NULL, Thread6, NULL, waThread6, sizeof(waThread6))
//NIL_THREADS_TABLE_ENTRY(NULL, Thread7, NULL, waThread7, sizeof(waThread7))
//NIL_THREADS_TABLE_ENTRY(NULL, Thread8, NULL, waThread8, sizeof(waThread8))

NIL_THREADS_TABLE_ENTRY(NULL, ThreadMem, NULL, waThreadMem, sizeof(waThreadMem))
NIL_THREADS_TABLE_END()

