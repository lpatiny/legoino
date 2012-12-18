/**
 * This application should check every 2 seconds for the temperature
 * Store the last 32 values in an array
 * 
 * This method is called every 2 seconds
 * 
 **/

#define MAX_TEMPERATURES 32
// C1255AC1255AC1255AC1255

int lastTemperatures[MAX_TEMPERATURES];


void setupPascal() {
  lastTemperatures[0]=-32768;
  lastTemperatures[MAX_TEMPERATURES]=32767;
}

void loopPascal() {
  loopOneWire();
  addTemperature(getParameter(20));
  updateMinMaxTemperature();
}

void addTemperature(int temperature) {
  for (int i=0; i<(MAX_TEMPERATURES-1); i++) {
    lastTemperatures[i]=lastTemperatures[i+1];
  }
  lastTemperatures[MAX_TEMPERATURES-1]=temperature;
}

void updateMinMaxTemperature() {
  int minTemperature=lastTemperatures[0];
  int maxTemperature=lastTemperatures[0];
  for (int i=0; i<MAX_TEMPERATURES; i++) {
    if (lastTemperatures[i]<minTemperature) minTemperature=lastTemperatures[i];
    if (lastTemperatures[i]>maxTemperature) maxTemperature=lastTemperatures[i];
  }
  setParameter(21,minTemperature);
  setParameter(22,maxTemperature);

  if (abs(minTemperature-maxTemperature)<getParameter(23)) {
    digitalWrite(RED1,LOW);
    digitalWrite(GREEN1,HIGH);
    digitalWrite(BLUE1,LOW);
  } 
  else {
    digitalWrite(RED1,HIGH);
    digitalWrite(GREEN1,LOW);
    digitalWrite(BLUE1,LOW);
  }
}



