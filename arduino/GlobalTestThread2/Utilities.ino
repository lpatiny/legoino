
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
#define MAX_DISTANCE_COUNTER 2500

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


