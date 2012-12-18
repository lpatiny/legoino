#include <MsTimer2.h>

int interruptCounter=0;

void setupInterrupt() {
  pinMode(IO5, OUTPUT);
  MsTimer2::set(1, interuptFunction); // every ms !!!
  MsTimer2::start();
}

void interuptFunction() {
  interruptCounter++;
  if (interruptCounter<10000) {
    if (interruptCounter%64==0) {
      digitalWrite(IO5, HIGH);
    } 
    else {
      digitalWrite(IO5, LOW);
    }
  } 
  else if (interruptCounter<1000) {
    digitalWrite(IO5, LOW);
  } 
  else {
    interruptCounter=0;
  }
}

