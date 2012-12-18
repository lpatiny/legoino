// Small demonstration of rgb1
// RGB1 is NOT pulseWidth Modulated


int rgb1EventStatus=0;

boolean rgb1Red=HIGH;
boolean rgb1Green=HIGH;
boolean rgb1Blue=HIGH;

void setupEventRgb1() {
  pinMode(RED1, OUTPUT);    
  pinMode(GREEN1, OUTPUT); 
  pinMode(BLUE1, OUTPUT); 
}


void runEventRgb1() {
  rgb1EventStatus++;
  if (rgb1EventStatus%getParameter(PARAM_RGB1)==0) { // random color every 1s
    if (random(2)==1) {
      rgb1Red=HIGH;
    } 
    else {
      rgb1Red=LOW;
    }
    if (random(2)==1) {
      rgb1Green=HIGH;
    } 
    else {
      rgb1Green=LOW;
    }
        if (random(2)==1) {
      rgb1Blue=HIGH;
    } 
    else {
      rgb1Blue=LOW;
    }
    
  }


  digitalWrite(RED1,rgb1Red);
  digitalWrite(GREEN1,LOW);
  digitalWrite(BLUE1,!rgb1Red);
  
  /*
  digitalWrite(RED1,rgb1Red);
  digitalWrite(GREEN1,rgb1Green);
  digitalWrite(BLUE1,rgb1Blue);
  */
}











