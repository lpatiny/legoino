unsigned int IOEventStatus=0;
unsigned int IOEventStatusCounter=0;

void setupEventIO() {
  for (int i=0; i<4; i++) {
    pinMode(IO[i], OUTPUT);    
  }
}

void runEventIO() {
  IOEventStatusCounter++;
  if (IOEventStatusCounter%getParameter(PARAM_SCAN)==0) {
    IOEventStatus++;
  }
  for (int i=0; i<4; i++) {
    if (i!=IOEventStatus%4) {
      digitalWrite(IO[i],LOW);
    } 
    else {
      digitalWrite(IO[i],HIGH);
    }
  }
}

