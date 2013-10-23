#define   LED1    3
#define   LED2    4
#define   LED3    9
#define   LED4   10
#define   RED1    5
#define   GREEN1  6
#define   BLUE1  11
#define   RED2    7
#define   GREEN2  8
#define   BLUE2  13



byte IO[]={
  LED1, LED2, LED3, LED4, RED1, BLUE1, RED2};

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  for (byte i=0; i<sizeof(IO); i++) {
    pinMode(IO[i], OUTPUT);     
  }
}

// the loop routine runs over and over again forever:
void loop() {
  for (byte i=0; i<sizeof(IO); i++) {
    digitalWrite(IO[i], HIGH);  
    delay(50);
  }
  /*
  for (byte i=0; i<sizeof(IO); i++) {
    digitalWrite(IO[i], LOW);  
    delay(50);
  }
  */
}


