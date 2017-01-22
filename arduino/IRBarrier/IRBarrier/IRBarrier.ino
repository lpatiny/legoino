#include <TimerOne.h>

/*
    we would like to record precisely the time when we cross an IR barrier

    On an ATMEGA32U4 we could use the following pins but we should take care to have one in 5V. We could not let it work
    on an micro pro
    On one hand we will generate a 38KHz on pin 9
    We will receive the signal based on interrupt on pin 7 (nothing else special on this one)
    On a mini we can only use D2 (int.0) and D3 (int.1)
    
    For the IR led we use 3 kohms otherwise it is too sensible !
*/

// check also https://www.pjrc.com/teensy/td_libs_TimerOne.html


#define MAX_SIZE   16
#define INTERRUPT  RISING   // may be RISING CHANGE of FALLING
#define DEBOUNCE   10000      // microseconds for debouncing


int counter = 0;
long unsigned times[MAX_SIZE] = {0};
long unsigned previousMicro = 0;
long unsigned currentMicro = 0;

void setup(void)
{
  Timer1.initialize(26);  // around 38KHz
  Timer1.pwm(9, 511);
  attachInterrupt(0, change, INTERRUPT); // 0 means D2 on a mini
  Serial.begin(9600);
}

void loop(void)
{
  if (Serial.available() > 0) {
    while (Serial.available() > 0) {
      Serial.read();
    }
    printResults();
  }
}

void change() {
  currentMicro = micros();
  if (currentMicro - previousMicro > DEBOUNCE) {
    previousMicro = currentMicro;
    times[counter++ % MAX_SIZE] = currentMicro;
  }
}

void printResults() {
  Serial.println(counter);
  for (int i = 0; i < MAX_SIZE; i++) {
    Serial.println(times[(i + counter + 1) % MAX_SIZE]);
  }
}

