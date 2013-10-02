
/*
Getting the distance using an Ultrasonic Module HC-SR04 ($3 on ebay ...)
 This device is designed to use 2 pins, one to trigger the distance measurement and one to read the distance
 It works by sending 8 distance measurement after a short trigger, after this it gives back the distance using a high signal
 on the output pin during the corresponding time.
 The following method works by putting a resistor of 1kohms on the input and output of the HC-SR04 and to connect the other
 end of the resistor on the same arduino pin.
 */

// 2500 corresponds to around 1.5 meter (or 1500 mm), just ignore if it is over
// The maximum time spend in this function is around 13ms (for a max counter value of 2500)
#define MAX_DISTANCE_COUNTER 2000

unsigned int getDistance(byte pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, HIGH);   // set the LED on
  delayMicroseconds(10);              // wait for a second
  digitalWrite(pin, LOW);    // set the LED off
  int counter=0;
  pinMode(pin, INPUT);
  while (digitalRead(pin)==0 && counter++<MAX_DISTANCE_COUNTER) {
  }
  long start=micros();
  if (counter<MAX_DISTANCE_COUNTER) {
    while (digitalRead(pin)==1 && counter++<MAX_DISTANCE_COUNTER) {
    }
    start=micros()-start;
    return 0.1717*start;
  }
  return 65535;
}


// function to print a device address
static void printFreeMemory(Print* output)
{
  nilPrintUnusedStack(output);
}



// The idea is to have 2 sounds on the SD card:
// ZZZZZZZZ: 30s silent
// YYYYYYYY: the sound to play

void initSound() {
  Serial1.begin(115200);
  delay(2000);
  // we need to switch to file mode each time !
  // we may only do it once otherwise it would crash
  Serial1.print("f");
  Serial1.flush();
  delay(500);
  cancelSound(); 
  delay(500);
}

void listSound() {
  Serial1.print("L");
  Serial1.print("\n");
  Serial1.flush();
  while (Serial1.available()) {
    Serial1.read();
  }
}

void playSound(String name) {
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
  Serial1.print("C"); // we cancelthe sound
  Serial1.print("");
  while (Serial1.available()) {
    Serial1.read();
  }
}


