#define OUT1    4
#define OUT2    11
#define OUT3    13
#define OUT4    6
#define IO1     8
#define IO2     18
#define IO3     20
#define IO4     19
#define RED1    5
#define GREEN1  9
#define BLUE1   10
#define RED2    21
#define GREEN2  22
#define BLUE2   23


byte IO[]={
  OUT1, OUT2, OUT3, OUT4, IO1, IO2, IO3, IO4, RED1, GREEN1, BLUE1, RED2, GREEN2, BLUE2};


int counter=0;
// the setup routine runs once when you press reset:
void setup() {
  // initialize the digital pin as an output.
  for (byte i=0; i<sizeof(IO); i++) {
    pinMode(IO[i], OUTPUT);     
  }
}

// the loop routine runs over and over again forever:
void loop() {
  for (int i=0; i<200; i=i+20) {
    int currentDelay=10;
    executeStep(i,true, currentDelay);
    executeStep(i,false, currentDelay);
  }
}



// LOW POWER VERSION
void executeStep(int numberSteps, boolean forward, byte currentDelay) {
  // quick acceleration
  for (int i=30; i>currentDelay; i=i-4) {
    counter=oneStep(counter, forward, i);
  }
  while (numberSteps>0) {
    numberSteps--;
    counter=oneStep(counter,forward, currentDelay);
  }
  // quick deceleration
  for (int i=currentDelay; i<30; i=i+4) {
    counter=oneStep(counter, forward, i);
  }
}


int oneStep(int counter, boolean forward, byte currentDelay) {
  if (forward) {
    counter++;
  }
  else { 
    counter--;
  }
  switch (counter%4) {
  case 0:
    digitalWrite(IO1, LOW);
    digitalWrite(OUT1,LOW);
    break;
  case 1:
    digitalWrite(IO1, HIGH);
    digitalWrite(OUT1,LOW);
    break;
  case 2:
    digitalWrite(IO1, LOW);
    digitalWrite(OUT1,HIGH);
    break;
  case 3:
    digitalWrite(IO1, HIGH);
    digitalWrite(OUT1,HIGH);
    break;
  }
  delay(currentDelay);
  return counter;
}

















