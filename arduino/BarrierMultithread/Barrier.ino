long unsigned previousMicro = 0;
long unsigned currentMicro = 0;
int counter = 0;
int from;
int to;


void setupBarrier()
{
  Timer1.initialize(26);  // around 38KHz
  Timer1.pwm(9, 511);
  delay(100);
  setParameter(PARAM_COUNTER, 0);
  attachInterrupt(0, change, INTERRUPT); // 0 means D2 on a mini
}


void change() {
  currentMicro = micros();
  if (currentMicro - previousMicro > getParameter(PARAM_DEBOUNCE)) {
      int counter=getParameter(PARAM_COUNTER);
  setParameter(PARAM_COUNTER, counter+1);
    previousMicro = currentMicro;
    times[counter % MAX_SIZE] = currentMicro;
  }
}

void printResults(Print* output) {
  setFromTo();
  for (int i = from; i < to; i++) {
    output->println((double)times[i % MAX_SIZE]/1000);
  }
}

void printDifferences(Print* output) {
  setFromTo();
  for (int i = from; i < to; i++) {
    output->println((double)(times[i % MAX_SIZE] - times[from % MAX_SIZE])/1000);
  }
}

void printConsecutive(Print* output) {
  setFromTo();
  for (int i = from+1; i < to; i++) {
    output->println((double)(times[i % MAX_SIZE] - times[(i-1) % MAX_SIZE])/1000);
  }
}

void setFromTo() {
  int counter=getParameter(PARAM_COUNTER);
  if (counter < MAX_SIZE) {
    from = 0;
    to = counter;
  } else {
    from=counter-MAX_SIZE;
    to=counter;
  }
}

void clearResults() {
  for (int i=0; i<MAX_SIZE; i++) {
      times[i]=0;
      setParameter(PARAM_COUNTER, 0);
  }
}

