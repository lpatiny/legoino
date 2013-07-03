/*
  Blink
 Turns on an LED on for one second, then off for one second, repeatedly.
 
 This example code is in the public domain.
 */

// CHAIN000.OGG
// THUNDER1.OGGSerial11
int status=0;

void setup() {               
  Serial1.begin(115200);
  Serial.begin(9600);
  
  delay(1000);
  // we need to switch to file mode each time !
  // we may only do it once otherwise it would crash
  Serial1.print("f");
  Serial1.flush();
  delay(3000);
}

void loop() {

  playSound("WAITING0"); 
  delay(10000);
  cancelSound();  // Cancelling a sound takes around 500ms !!!!!!!!
  delay(500);
  playSound("LASER1");
  delay(3000);
  // cancelSound();
}


void playSound(String name) {
  Serial.print("Start playing: ");
  Serial.println(name);
  Serial1.print("P");
  Serial1.print(name);
  Serial1.print("OGG");
  Serial1.print("\n");
  Serial1.flush();
  while (Serial1.available()) {
    Serial1.read();
  }
}

void cancelSound() {
   Serial.println("Stop");
  Serial1.print("C"); // we cancelthe sound
  Serial1.print("");
  while (Serial1.available()) {
    Serial1.read();
  }
}









