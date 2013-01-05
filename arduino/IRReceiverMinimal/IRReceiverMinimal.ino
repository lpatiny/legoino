#include <PinChangeInt.h>

// RC5 code detection

#define INPUT_IR A1



int unsigned irCode=0;


void setup() {
  setupIR();
  lightSetup();
  Serial.begin(115200);
}

void loop() {
  lightLoop(irCode);
}












