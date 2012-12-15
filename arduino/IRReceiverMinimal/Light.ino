#define   IO1    9
#define   IO2   10
#define   IO3    4
#define   IO4   12
#define   IO5    2
#define   IO6    3


int unsigned oldIrCode=0;

void lightSetup() {
  pinMode(IO1,OUTPUT);
  pinMode(IO2,OUTPUT);
  pinMode(IO3,OUTPUT);
  pinMode(IO4,OUTPUT);
  pinMode(IO5,OUTPUT);
  pinMode(IO6,OUTPUT);
}

void lightLoop(int irCode) {

  if (irCode!=oldIrCode) {
    Serial.println(irCode,BIN);
    oldIrCode=irCode;
    int temp=irCode;
    bitClear(temp,1);
    Serial.println(temp);



    switch (temp) {
    case 129:
      digitalWrite(IO1,! digitalRead(IO1));
      break;
    case 4225:
      digitalWrite(IO2,! digitalRead(IO2));
      break;
    case 5633:
      digitalWrite(IO3,! digitalRead(IO3));
      break;
    case 4353:
      digitalWrite(IO4,! digitalRead(IO4));
      break;
    case 257:
      digitalWrite(IO5,! digitalRead(IO5));
      break;
    case 6657:
      digitalWrite(IO6,! digitalRead(IO6));
      break;
    case 1537: // OFF
      digitalWrite(IO1,LOW);
      digitalWrite(IO2,LOW);
      digitalWrite(IO3,LOW);
      digitalWrite(IO4,LOW);
      digitalWrite(IO5,LOW);
      digitalWrite(IO6,LOW);
      break;
    default: 
      // if nothing else matches, do the default
      // default is optional

      break;
    }
  }
}







