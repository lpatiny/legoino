// The maximal length of a parameter value. It is a int so the value must be between -32768 to 32767
#define MAX_PARAM_VALUE_LENGTH 10

char paramSerialValue[MAX_PARAM_VALUE_LENGTH];
byte paramSerialValuePosition=0;
byte paramCurrent=0; // Which parameter are we defining

void serialReset() {
  paramCurrent=0;
  paramSerialValuePosition=0;
  paramSerialValue[0]='\0';
}

void serialPrintHelp() {
  Serial.println(F("(d)ebug"));
  Serial.println(F("(e)eprom"));
  Serial.println(F("(f)ree mem"));
  Serial.println(F("(h)elp"));
  Serial.println(F("(i)2c"));
  Serial.println(F("(l)og"));
  #ifdef ONE_WIRE_BUS1
  Serial.println(F("(o)ne wire"));
  #endif
  Serial.println(F("(s)ettings"));
}


NIL_WORKING_AREA(waThreadSerial, 100);
NIL_THREAD(ThreadSerial, arg) {

  Serial.begin(9600);

  /*
  SerialEvent occurs whenever a new data comes in the
   hardware serial RX.  This routine is run between each
   time loop() runs, so using delay inside loop can delay
   response.  Multiple bytes of data may be available.
   
   This method will mainly set/read the parameters:
   Uppercase + number + CR ((-) and 1 to 5 digit) store a parameter (0 to 25 depending the letter)
   example: A100, A-1
   -> Many parameters may be set at once
   example: C10,20,30,40,50
   Uppercase + CR read the parameter
   example: A
   -> Many parameters may be read at once
   example: A,B,C,D
   s : read all the parameters
   h : help
   l : show the log file
   */

  while(TRUE) {
    while (Serial.available()) {
      // get the new byte:
      char inChar = (char)Serial.read(); 

      if (inChar=='d') { // show debug info
        getDebuggerLog(&Serial);
        serialReset();
      } else if (inChar=='e') { // show debug info
        getStatusEEPROM(&Serial);
        serialReset();
      } else if (inChar=='f') { // show settings
        printFreeMemory(&Serial);
        serialReset();
      } 
      else if (inChar=='h') {
        serialPrintHelp();
        serialReset();
      } 
      else if (inChar=='l') { // show log
        getLoggerLog(&Serial);
        serialReset();
      } 
      else if (inChar=='i') { // show i2c (wire) information
        wireInfo(&Serial);
        serialReset();
      } 
      #ifdef ONE_WIRE_BUS1
      else if (inChar=='o') { // show oneWire information
        oneWireInfo(&Serial);
        serialReset();
      } 
      #endif
      else if (inChar=='s') { // show settings
        printParameters(&Serial);
        serialReset();
      } 
      else if (inChar==',') { // store value and increment
        if (paramCurrent>0) {
          if (paramSerialValuePosition>0) {
            setAndSaveParameter(paramCurrent-1,atof(paramSerialValue));
          } 
          else {
            Serial.println(parameters[paramCurrent-1]);
          }
          if (paramCurrent<=MAX_PARAM) {
            paramCurrent++;
            paramSerialValuePosition=0;
            paramSerialValue[0]='\0';
          } 
          else {
            debugger(1,inChar);
            serialReset();
          }
        }
      }
      else if (inChar==13 || inChar==10) {
        // this is a carriage return;
        if (paramCurrent>0) {
          if (paramSerialValuePosition>0) {
            setAndSaveParameter(paramCurrent-1,atof(paramSerialValue));
          } 
          else {
            Serial.println(parameters[paramCurrent-1]);
          }
        }
        serialReset();
      } 
      else if (inChar>47 && inChar<58 || inChar=='-') {
        if (paramSerialValuePosition<MAX_PARAM_VALUE_LENGTH) {
          paramSerialValue[paramSerialValuePosition]=inChar;
          paramSerialValuePosition++;
          if (paramSerialValuePosition<MAX_PARAM_VALUE_LENGTH) {
            paramSerialValue[paramSerialValuePosition]='\0';
          }
        } 
        else {
          debugger(1,inChar);
          serialReset();
        }
      } 
      else if (inChar>64 && inChar<(66+MAX_PARAM)) { // a character so we define the field
        paramCurrent=inChar-64;
      }
      else {
        debugger(1,inChar);
        serialReset();
      }
    }
    nilThdSleepMilliseconds(1);
  }
}


