// We plan to have 16 parameters that are int
// The parameters should be saved in the EEPROM
// And could be modified using a serial port.

#define MAX_PARAM 26    // If the MAX_PARAM change you need to change the pointer in the EEPROM



int parameters[MAX_PARAM];

void setupParameters() {
  EXROM.read(EE_PARAMETERS, parameters, MAX_PARAM*2);
}

int getParameter(byte number) {
  return parameters[number];
}

void setParameter(byte number, int value) {
   parameters[number]=value;
}

/*
This will take time, around 4 ms
This will also use the EEPROM that is limited to 100000 writes
*/
void setAndSaveParameter(byte number, int value) {
   parameters[number]=value;
   // Writing one parameter takes 4mS
   EXROM.write(EE_PARAMETERS+number*2, value);
}

void printParameters(Print* output) {
  output->println("Current settings:");
  for (int i=0; i<MAX_PARAM; i++) {
    output->print(i);
    output->print("-");
    output->print((char)(i+65));
    output->print(":");
    output->println(parameters[i]);
  }
}
