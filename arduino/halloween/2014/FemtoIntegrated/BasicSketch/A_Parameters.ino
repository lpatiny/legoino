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

#define MAX_PARAM 52   // If the MAX_PARAM change you need to change the pointer in the EEPROM

#define PARAM_DETECTOR1       0   // set to one if something is detected
#define PARAM_DETECTOR2       1   // set to one if something is detected
#define PARAM_DISTANCE        2
#define PARAM_ALERT_DISTANCE  3

#define PARAM_FIRST_SONG      4 // we are able to play a random sound between FIRST and LAST
#define PARAM_LAST_SONG       5
#define PARAM_CURRENT_SONG    6
#define PARAM_VOLUME          7



#define PARAM_DELAY0         10
#define PARAM_DELAY1         11
#define PARAM_DELAY2         12
#define PARAM_DELAY3         13
#define PARAM_DELAY4         14
#define PARAM_DELAY5         15
#define PARAM_DELAY6         16
#define PARAM_DELAY7         17
#define PARAM_DELAY8         18
#define PARAM_DELAY9         19

#define PARAM_VAR0           20
#define PARAM_VAR1           21
#define PARAM_VAR2           22
#define PARAM_VAR3           23
#define PARAM_VAR4           24
#define PARAM_VAR5           25
#define PARAM_VAR6           26
#define PARAM_VAR7           27
#define PARAM_VAR8           28
#define PARAM_VAR9           29

#define PARAM_STATUS0        30
#define PARAM_STATUS1        31
#define PARAM_STATUS2        32
#define PARAM_STATUS3        33
#define PARAM_STATUS4        34

#define PARAM_SERVO_FROM     35
#define PARAM_SERVO_TO       36
#define PARAM_SERVO_DELAY    37
#define PARAM_SERVO_ACTIVE   38

#define PARAM_ACTION1        40
#define PARAM_ACTION2        41
#define PARAM_ACTION3        42
#define PARAM_ACTION4        43



#define PARAM_TEMPERATURE    47  // just for fun we could register temperature
#define PARAM_IRCODE         48  // we could add a IR receiver

#define PARAM_RELAY_1        49
#define PARAM_RELAY_2        50

#define PARAM_STATUS         51 // allow to test the arduino



void resetParameter() {

  setAndSaveParameter(PARAM_FIRST_SONG,4); // first event may not be zero, it would never starts
  setAndSaveParameter(PARAM_LAST_SONG,7);
  setAndSaveParameter(PARAM_VOLUME,10);

  setAndSaveParameter(PARAM_SERVO_FROM,60);
  setAndSaveParameter(PARAM_SERVO_TO,120);
  setAndSaveParameter(PARAM_SERVO_DELAY,15);
  setAndSaveParameter(PARAM_SERVO_ACTIVE,0);


  setAndSaveParameter(PARAM_DELAY0,1); // first event may not be zero, it would never starts
  setAndSaveParameter(PARAM_DELAY1,25);
  setAndSaveParameter(PARAM_DELAY2,50);
  setAndSaveParameter(PARAM_DELAY3,75);
  setAndSaveParameter(PARAM_DELAY4,100);
  setAndSaveParameter(PARAM_DELAY5,125);
  setAndSaveParameter(PARAM_DELAY6,150);
  setAndSaveParameter(PARAM_DELAY7,175);
  setAndSaveParameter(PARAM_DELAY8,200);
  setAndSaveParameter(PARAM_DELAY9,225);

  setAndSaveParameter(PARAM_VAR0,0);
  setAndSaveParameter(PARAM_VAR1,100);
  setAndSaveParameter(PARAM_VAR2,2);
  setAndSaveParameter(PARAM_VAR3,3);
  setAndSaveParameter(PARAM_VAR4,4);
  setAndSaveParameter(PARAM_VAR5,5);
  setAndSaveParameter(PARAM_VAR6,6);
  setAndSaveParameter(PARAM_VAR7,7);
  setAndSaveParameter(PARAM_VAR8,8);
  setAndSaveParameter(PARAM_VAR9,9);
}



//When parameters are set (and saved) an event is recorded (256-281 : A-Z + .... (if more parameters than 26))
#define EVENT_SAVE_ALL_PARAMETER     255
#define EVENT_PARAMETER_SET          256


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
  setAndSaveParameter(PARAM_STATUS,0);
}

int getParameter(byte number) {
  return parameters[number];
}

void setParameterBit(byte number, byte bitToSet) {
  bitSet(parameters[number], bitToSet);
  // parameters[number]=parameters[number] | (1 << bitToSet);
}

void clearParameterBit(byte number, byte bitToClear) {
  bitClear(parameters[number], bitToClear);
  // parameters[number]=parameters[number] & ( ~ (1 << bitToClear));
}

byte getParameterBit(byte number, byte bitToRead) {
  return bitRead(parameters[number], bitToRead);
  // return (parameters[number] >> bitToRead ) & 1;
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
  writeLog(EVENT_SAVE_ALL_PARAMETER, 0);
}

/*
This will take time, around 4 ms
 This will also use the EEPROM that is limited to 100000 writes
 */
void setAndSaveParameter(byte number, int value) {
  parameters[number]=value;
  //The address of the parameter is given by : EE_START_PARAM+number*2
  eeprom_write_word((uint16_t*) EE_START_PARAM+number, value);

  writeLog(EVENT_PARAMETER_SET+number, value);
}


void printParameter(Print* output, byte number){
  output->print(number);
  output->print("-");
  if (number>25) {
    output->print((char)(floor(number/26) + 64));
  } 
  else {
    output->print(" ");
  }
  output->print((char)(number-floor(number/26)*26 + 65));
  output->print(": ");
  output->println(parameters[number]);
}

void printParameters(Print* output) {
  for (int i = 0; i < MAX_PARAM; i++) {
    printParameter(output, i);
  }
}



uint8_t printCompactParameters(Print* output) {
  printCompactParameters(output, MAX_PARAM);
}

uint8_t printCompactParameters(Print* output, byte number) {
  if (number > MAX_PARAM) {
    number=MAX_PARAM;
  }
  byte checkDigit=0;

  // we first add epoch
  checkDigit^=toHex(output, (long)now());
  for(int i = 0; i < number; i++) {
    int value=getParameter(i);
    checkDigit^=toHex(output, value);
  }
  checkDigit^=toHex(output, (int)getQualifier());
  toHex(output, checkDigit);
  output->println("");
}

/* The qualifier represents the card ID and is stored just after the last parameter */
uint16_t getQualifier() {
  return eeprom_read_word((uint16_t*)(EE_START_PARAM+MAX_PARAM*2));
}

void setQualifier(uint16_t value) {
  eeprom_write_word((uint16_t*)(EE_START_PARAM+MAX_PARAM*2), value);
}













