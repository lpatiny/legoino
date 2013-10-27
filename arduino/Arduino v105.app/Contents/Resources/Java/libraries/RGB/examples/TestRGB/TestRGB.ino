#include <NilRTOS.h>
#include <SoftPWM.h>
#include <RGB.h>

#define RED1   11
#define GREEN1 5
#define BLUE1  6

#define RED2   7
#define GREEN2 13
#define BLUE2  8

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
//RGB rgb1(RED1, GREEN1, BLUE1);
//RGB rgb2(RED2, GREEN2, BLUE2);


void setup()
{
  nilSysBegin();
}

void loop()
{

// rgb1.goRandom(20);
  
//rgb1.randomColor();
//rgb2.randomColor();
//delay(250);
  
  
}




NIL_WORKING_AREA(waThreadAction1, 50);
NIL_THREAD(ThreadAction1, arg) {
  RGB rgb1(RED1, GREEN1, BLUE1);
  
  while (TRUE) {
  
	rgb1.go(255,0,0,25);
	rgb1.go(0,255,0,25);
	rgb1.go(0,0,255,25);
 //   rgb1.goRandom(20);

  }
}

NIL_THREADS_TABLE_BEGIN()
NIL_THREADS_TABLE_ENTRY(NULL, ThreadAction1, NULL, waThreadAction1, sizeof(waThreadAction1))
NIL_THREADS_TABLE_END()