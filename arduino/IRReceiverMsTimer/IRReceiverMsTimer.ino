#include <FlexiTimer2.h>

// RC5 code detection

#define INPUT_IR 21



int unsigned irCode=0;


void setup() {

  
  setupIR();
  lightSetup();
  Serial.begin(115200);
}

void loop() {
  lightLoop(irCode);
}












