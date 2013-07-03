#include <PinChangeInt.h>

#define IR_IN  12

uint8_t latest_interrupted_pin;
uint8_t currentPosition;
int unsigned interrupt_time[64]={
  0};
long unsigned timeLast=0;
long unsigned timeCurrent=0;
boolean highBit=true;
boolean raising=true;
int unsigned irCode=0;
int unsigned newIrCode=0;
int unsigned oldIrCode=0;
int currentBit=0;

void quicfunc() {
  timeCurrent=micros();
  if (timeCurrent-timeLast>2000) {
    timeLast=timeCurrent;
    currentPosition=0;
    currentBit=0;
    newIrCode=0;
    highBit=true;
    raising=true;
  }  
  else {
    if (interrupt_time[currentPosition]<1200) {
      highBit=!highBit;
    }

    raising=!raising;
    interrupt_time[currentPosition]=timeCurrent-timeLast;
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

    if (currentPosition<64) {
      currentPosition++;
    }
  }
};



void setup() {
  pinMode(IR_IN, INPUT);
  digitalWrite(IR_IN, HIGH);
  PCintPort::attachInterrupt(IR_IN, &quicfunc, CHANGE);
  currentPosition=0;
  Serial.begin(115200);
}

uint8_t i;
void loop() {
  delay(100);
  if (irCode!=oldIrCode) {
    Serial.println(irCode,BIN);
    oldIrCode=irCode;
  }
  /*

   for (i=0; i < 64; i++) {
   if (interrupt_time[i]!=0) {
   Serial.print(interrupt_time[i]);
   Serial.println("");
   interrupt_time[i]=0;
   }
   }
   Serial.print("--------- ");
   Serial.println(irCode,BIN);
   Serial.print(currentBit);
   */
}









