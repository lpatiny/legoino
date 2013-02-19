
long unsigned timeLast=0;
boolean highBit=true;
boolean raising=true;

int unsigned newIrCode=0;
int currentBit=0;

int counter=0;
boolean lastValue=true;

void irInterrupt() {
  boolean value=digitalRead(INPUT_IR);
  
  
  long unsigned timeCurrent=micros();
  if (timeCurrent-timeLast>2000 || timeCurrent<timeLast) {
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
  */

};


void setupIR() {
  pinMode(INPUT_IR, INPUT);
  digitalWrite(INPUT_IR, HIGH);
  FlexiTimer2::set(1, 1.0/2000, irInterrupt);
  FlexiTimer2::start();
}




