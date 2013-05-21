NIL_WORKING_AREA(waThreadMem, 100);
NIL_THREAD(ThreadMem, arg) {
  Serial.begin(9600);  
  while (TRUE) {   
    nilPrintUnusedStack(&Serial);
    nilThdSleepMilliseconds(1000);
  }
}

NIL_THREADS_TABLE_BEGIN()
NIL_THREADS_TABLE_ENTRY(NULL, Thread0, NULL, waThread0, sizeof(waThread0))
NIL_THREADS_TABLE_ENTRY(NULL, Thread1, NULL, waThread1, sizeof(waThread1))
NIL_THREADS_TABLE_ENTRY(NULL, Thread2, NULL, waThread2, sizeof(waThread2))
NIL_THREADS_TABLE_ENTRY(NULL, Thread3, NULL, waThread3, sizeof(waThread3))
//NIL_THREADS_TABLE_ENTRY(NULL, ThreadMem, NULL, waThreadMem, sizeof(waThreadMem))
NIL_THREADS_TABLE_END()

