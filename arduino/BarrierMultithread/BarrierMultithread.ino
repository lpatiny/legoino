#include <avr/eeprom.h>
#include "Arduino.h"
#include <NilRTOS.h>
#include <TimeLib.h>
#include <TimerOne.h>

#define MONITORING_LED 13
#define THR_SERIAL 1
#define INTERRUPT RISING
#define MAX_SIZE 16

#define PARAM_DEBOUNCE 0  // deboucing in microseconds
#define PARAM_COUNTER  1

long unsigned times[MAX_SIZE] = {0};

void setup() {
    setupParameters(); 
  setupBarrier();
  nilSysBegin();
}

void loop() {

}

void resetParameters() {
  setAndSaveParameter(PARAM_DEBOUNCE, 10000);
  setAndSaveParameter(PARAM_COUNTER, 0);
}

