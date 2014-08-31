#define SERIAL1_BUFFER_LENGTH 32
char serial1Buffer[SERIAL1_BUFFER_LENGTH];
byte serial1BufferPosition=0;

NIL_WORKING_AREA(waThreadZigbee, 128); // minimum 128
NIL_THREAD(ThreadZigbee, arg) {
  Serial1.begin(38400);
  while(true) {
    //Serial1.println("test");
    while (Serial1.available()) {
      // get the new byte:
      char inChar = (char)Serial1.read(); 
      if (inChar==13 || inChar==10) {
        // this is a carriage return;
        if (serial1BufferPosition>0) {
          printResult(serial1Buffer, &Serial1);
        } 
        serial1BufferPosition=0;
        serial1Buffer[0]='\0';
      } 
      else {
        if (serial1BufferPosition<SERIAL1_BUFFER_LENGTH) {
          serial1Buffer[serial1BufferPosition]=inChar;
          serial1BufferPosition++;
          if (serial1BufferPosition<SERIAL1_BUFFER_LENGTH) {
            serial1Buffer[serial1BufferPosition]='\0';
          }
        }
      }  
    }
    nilThdSleepMilliseconds(1);
  }
}

