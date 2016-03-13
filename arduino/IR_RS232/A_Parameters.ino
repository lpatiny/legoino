/*********************************************
 * This file is used to declare the parameters
 * table used by the program.
 * 
 * We use the EEPROM for saving the parameters 
 * changed by the user during the functionment 
 * of the Bioreactor.
 * 
 * The parameter are loaded during the boot.
 * 
 * All change to important parameters are saved 
 * to the EEPROM
 *********************************************/

#include <avr/eeprom.h>

#define MAX_PARAM 26   // If the MAX_PARAM change you need to change the pointer in the EEPROM

#define PARAM_POWER          0
#define PARAM_INTENSITY      1
#define PARAM_SPEED          2
#define PARAM_CHANGE         3
#define PARAM_COLOR_MODEL    4

#define EE_START_PARAM           0 // We save the parameter from byte 0 of EEPROM
#define EE_LAST_PARAM            (MAX_PARAM*2-1) // The last parameter is stored at byte 50-51

#define EEPROM_MIN_ADDR            0
#define EEPROM_MAX_ADDR          511


// value that should not be taken into account
// in case of error the parameter is set to this value
#define ERROR_VALUE  -32768

int parameters[MAX_PARAM];

void setupParameters() {
  //We copy all the value in the parameters table
  eeprom_read_block((void*)parameters, (const void*)EE_START_PARAM, MAX_PARAM*2);

  setParameter(PARAM_INTENSITY,3);
  setParameter(PARAM_POWER,1);
  setParameter(PARAM_CHANGE,0);
  setParameter(PARAM_SPEED,0);
  setParameter(PARAM_COLOR_MODEL,0);
}

int getParameter(byte number) {
  return parameters[number];
}


void setParameter(byte number, int value) {
  parameters[number]=value;
}

void incrementParameter(byte number) {
  parameters[number]++;
}

void saveParameters() {
  for (byte i=0; i<MAX_PARAM; i++) {
    eeprom_write_word((uint16_t*) EE_START_PARAM+i, parameters[i]);
  }
}

void incrementAndSaveParameter(byte number) {
  parameters[number]++;
  setAndSaveParameter(number, parameters[number]);
}

void decrementAndSaveParameter(byte number) {
  parameters[number]--;
  setAndSaveParameter(number, parameters[number]);
}

/*
This will take time, around 4 ms
 This will also use the EEPROM that is limited to 100000 writes
 */
void setAndSaveParameter(byte number, int value) {
  parameters[number]=value;
  //The address of the parameter is given by : EE_START_PARAM+number*2
  eeprom_write_word((uint16_t*) EE_START_PARAM+number, value);
}












