#define   OUT1    2
#define   IO1    A0
#define   OUT2    4
#define   IO2    A1
#define   OUT3    9
#define   IO3    A2
#define   OUT4   10
#define   IO4    A3
#define   RED1    5
#define   GREEN1 11
#define   BLUE1   6
#define   RED2    7
#define   GREEN2 13
#define   BLUE2   8


byte IO[]={
  OUT1, OUT2, OUT3, OUT4, IO1, IO2, IO3, IO4, RED1, GREEN1, BLUE1, RED2, GREEN2, BLUE2};


byte counter=0;
// the setup routine runs once when you press reset:
void setup() {

  // initialize the digital pin as an output.
  for (byte i=0; i<sizeof(IO); i++) {
    pinMode(IO[i], OUTPUT);     
  }
}

// the loop routine runs over and over again forever:
void loop() {
  counter++;
  switch (counter%4) {
  case 0:
    digitalWrite(IO1, LOW);
    digitalWrite(OUT1,LOW);
    break;
  case 1:
    digitalWrite(IO1, LOW);
    digitalWrite(OUT1,HIGH);
    break;
  case 2:
    digitalWrite(IO1, HIGH);
    digitalWrite(OUT1,HIGH);
    break;
  case 3:
    digitalWrite(IO1, HIGH);
    digitalWrite(OUT1,LOW);
    break;
  }
delay(5);



}





