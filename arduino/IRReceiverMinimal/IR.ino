
long unsigned timeLast=0;
boolean highBit=true;
boolean raising=true;

int unsigned newIrCode=0;
int currentBit=0;

void irInterrupt() {
  long unsigned timeCurrent=micros();
  if (timeCurrent-timeLast>2000) {
    timeLast=timeCurrent;
    currentBit=0;
    newIrCode=0;
    highBit=true;
    raising=true;
  }  
  else {
    if (timeCurrent-timeLast<1200) {
      highBit=!highBit;
    }
    raising=!raising;
    timeLast=timeCurrent;
    if (highBit) {
      if (raising) {
        bitSet(newIrCode,currentBit);
      } 
      else {
        bitClear(newIrCode,currentBit);
      }
      currentBit++; 
      if (currentBit==13) {
        irCode=newIrCode; 
      }
    }
  }
};


void setupIR() {
  pinMode(INPUT_IR, INPUT);
  digitalWrite(INPUT_IR, HIGH);
  PCintPort::attachInterrupt(INPUT_IR, &irInterrupt, CHANGE);
  Serial.begin(115200);
}



