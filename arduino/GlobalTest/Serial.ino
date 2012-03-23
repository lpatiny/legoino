// The maximal length of a parameter value. It is a int so the value must be between -32768 to 32767
#define MAX_PARAM_VALUE_LENGTH 6

char paramSerialValue[MAX_PARAM_VALUE_LENGTH];
byte paramSerialValuePosition=0;
byte paramCurrent=0; // Which parameter are we defining

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

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 

    if (inChar=='h') {
      serialPrintHelp();
      serialReset();
    } 
    else if (inChar=='l') { // show log
      getLoggerLog(&Serial);
      serialReset();
    } 
    else if (inChar=='d') { // show debug info
      getDebuggerLog(&Serial);
      serialReset();
    } 
    else if (inChar=='i') { // show i2c (wire) information
      wireInfo(&Serial);
      serialReset();
    } 
    else if (inChar=='o') { // show oneWire information
      oneWireInfo(&Serial);
      serialReset();
    } 
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
}

void serialReset() {
  paramCurrent=0;
  paramSerialValuePosition=0;
  paramSerialValue[0]='\0';
}

void serialPrintHelp() {
  Serial.println("(h)elp Menu");
  Serial.println("(d)ebug");
  Serial.println("(i)2c");
  Serial.println("(l)og");
  Serial.println("(o)ne wire");
  Serial.println("(s)ettings");
}






