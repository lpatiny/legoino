// Small demonstration of rgb1
// RGB1 is NOT pulseWidth ModulatedThreadRGB1

#ifdef THR_IRPIN

#include <IRremote.h>

NIL_WORKING_AREA(waThreadIRReceiver, 100);
NIL_THREAD(ThreadIRReceiver, arg) {
  IRrecv irrecv(THR_IRPIN);
  decode_results results;

  irrecv.enableIRIn(); // Start the receiver

  while (TRUE) {
    if (irrecv.decode(&results)) {
      setParameter(PARAM_IRCODE, results.value);
      analyzeIR(results.value);
      Serial.println("ABCD");
      irrecv.resume();
    }
    nilThdSleepMilliseconds(5);
  }
}


// we define some logic to change some values
void analyzeIR(int value) {
  Serial.println(value);
  Serial.println(value%1024);
  Serial.println(value == 20);
  Serial.println(getParameter(PARAM_RGB1));
  if (value % 1024 == 20) {
    if (getParameter(PARAM_RGB1)==-1) {
      setParameter(PARAM_RGB1, 20);
    } 
    else {
      setParameter(PARAM_RGB1, -1);
    }
  }
}

#endif















