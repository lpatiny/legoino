
byte MONITORING = 13;
byte monitValue=LOW;

#define BUTTON_POWER       0   // set to one if something is detected
#define BUTTON_UP          1
#define BUTTON_DOWN        2
#define BUTTON_SOUND       3
#define BUTTON_LEFT        4 // we are able to play a random sound between FIRST and LAST
#define BUTTON_RIGHT       5
#define BUTTON_AUTO        6

long unsigned timeLast=0;
boolean highBit=true;
boolean raising=true;

int unsigned irCode=0;
int unsigned newIrCode=0;
int currentBit=0;

byte buttons[7]={
  12,1,33,44,34,2,52};

void irInterrupt() {
  long unsigned timeCurrent=micros();

  monitValue = ! monitValue;
  digitalWrite(MONITORING, monitValue);



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
        if (irCode!=newIrCode) {
          irCode=newIrCode; 
          eventIR(irCode);
        }
      }
    }
  }
};


byte getIntensity() { // value from 0 to 7 should be converted to 31 to 255
  int intensity=(getParameter(PARAM_INTENSITY)+1)*32-1;
  Serial.println(intensity);
  return (getParameter(PARAM_INTENSITY)+1)*32-1;
}


void eventIR(int irCode) {
  irCode=irCode>>7;

  for (byte i=0; i<sizeof(buttons); i++) {
    if (irCode==buttons[i]) {

      switch (i) {
      case BUTTON_POWER:
        if (getParameter(PARAM_POWER)==0) {
          setAndSaveParameter(PARAM_POWER,1);
        } else {
           setAndSaveParameter(PARAM_POWER,0);
        }
        break;
      case BUTTON_UP:
        if (getParameter(PARAM_INTENSITY)<7) {
          incrementAndSaveParameter(PARAM_INTENSITY);
        }
        break;
      case BUTTON_DOWN:
        if (getParameter(PARAM_INTENSITY)>0) {
          decrementAndSaveParameter(PARAM_INTENSITY);
        }
        break;
      case BUTTON_SOUND:
        if (getParameter(PARAM_COLOR_MODEL)>8) {
          setAndSaveParameter(PARAM_COLOR_MODEL,0);
        } 
        else {
          incrementAndSaveParameter(PARAM_COLOR_MODEL);
        }
        break;
      case BUTTON_RIGHT:
        if (getParameter(PARAM_SPEED)<6) {
          incrementAndSaveParameter(PARAM_SPEED);
        }
        break;
      case BUTTON_LEFT:
        if (getParameter(PARAM_SPEED)>0) {
          decrementAndSaveParameter(PARAM_SPEED);
        }
        break;
      case BUTTON_AUTO:
        if (getParameter(PARAM_CHANGE)>5) {
          setAndSaveParameter(PARAM_CHANGE,0);
        } 
        else {
          incrementAndSaveParameter(PARAM_CHANGE);
        }
        break;
      default: 
        // if nothing else matches, do the default
        // default is optional
        break;
      }




      Serial.print(i);
      Serial.print(" - ");
      Serial.print(irCode,BIN);
      Serial.print(" - ");
      Serial.println(irCode);
    } 
  }
}


void setupIR() {
  pinMode(1, INPUT);
  digitalWrite(1, HIGH);
  pinMode(MONITORING, OUTPUT);
  attachInterrupt(3, irInterrupt, CHANGE);
}













