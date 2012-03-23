//#define       NO_PORTB_PINCHANGES // IS USELESS HERE!  Modify it in PinChangeIntConfig.h
//#define       NO_PORTC_PINCHANGES // IS USELESS HERE!  Modify it in PinChangeIntConfig.h
#define VERSION 110 // 110 if using PinChangeInt-1.1, 120 for version 1.2, 200 for ooPinChangeIntversion 1.00
                    // 201 for ooPinChangeInt version 2.01, etc.
#define SERIALSTUFF // undef to take out all serial statements.  Default:  #define for measuring time.
#undef MEMTEST     // undef to take out memory tests.  Default:  #undef for measuring time.
//-----------------------
#if VERSION >= 200
#include <ooPinChangeInt.h>
#else
#include <PinChangeInt.h>
#endif
#include <cb.h>

#undef FLASH // to flash LED on pin 13 during test
#ifdef MEMTEST
#include <MemoryFree.h>
#endif

#define TEST 5

#if   TEST == 1
#define PTEST 2  // pin to trigger interrupt.  pins 0 and 1 are used
#define PLOW  2  // by Serial, so steer clear of them!
#define PHIGH 2  // Interrupts are attached to these pins

#elif TEST == 2  // see the #if TEST == 2 || TEST == 3 code, below
#define PTEST 2
#define PLOW  2
#define PHIGH 2  // need to attachInterrupt to 5 in the code

#elif TEST == 3  // see the #if TEST == 2 || TEST == 3 code, below
#define PTEST 5
#define PLOW  2
#define PHIGH 2  // need to attachInterrupt to 5 in the code

#elif TEST == 4
#define PTEST 2
#define PLOW  2
#define PHIGH 5

#elif TEST == 5
#define PTEST 3
#define PLOW  2
#define PHIGH 5

#elif TEST == 6
#define PTEST 4
#define PLOW  2
#define PHIGH 5

#elif TEST == 7
#define PTEST 5
#define PLOW  2
#define PHIGH 5
#endif

uint8_t qf0;
void quicfunc() {
  qf0=TCNT0;
}


class speedy : public CallBackInterface
{
 public:
   uint8_t id;
   static uint8_t var0;
   speedy () { id=0; };
   speedy (uint8_t _i): id(_i) {};

   void cbmethod() {
     speedy::var0=TCNT0;
     //Serial.print("Speedy method "); // debugging
     //Serial.println(id, DEC);
   };
};
uint8_t speedy::var0=0;

volatile uint8_t *led_port;
volatile uint8_t *pinT_OP;
volatile uint8_t *pinT_IP;
uint8_t led_mask, not_led_mask;
uint8_t pinT_M, not_pinT_M;
volatile uint8_t pintest, pinIntLow, pinIntHigh;
uint8_t totalpins;
speedy speedster[8]={speedy(0), speedy(1), speedy(2), speedy(3), speedy(4), speedy(5), speedy(6), speedy(7) };
#ifdef MEMTEST
int freemem;
#endif

int i=0;

#define PINLED 13
void setup()
{
#ifdef SERIALSTUFF
  Serial.begin(115200); Serial.println("---------------------------------------");
#endif SERIALSTUFF
  pinMode(PINLED, OUTPUT); digitalWrite(PINLED, LOW);
  // set up ports for trigger
  pinMode(0, OUTPUT); digitalWrite(0, HIGH);
  pinMode(1, OUTPUT); digitalWrite(1, HIGH);
  pinMode(2, OUTPUT); digitalWrite(2, HIGH);
  pinMode(3, OUTPUT); digitalWrite(3, HIGH);
  pinMode(4, OUTPUT); digitalWrite(4, HIGH);
  pinMode(5, OUTPUT); digitalWrite(5, HIGH);
  pinMode(6, OUTPUT); digitalWrite(6, HIGH);
  pinMode(7, OUTPUT); digitalWrite(7, HIGH);
#ifdef FLASH
  led_port=portOutputRegister(digitalPinToPort(PINLED));
  led_mask=digitalPinToBitMask(PINLED);
  not_led_mask=led_mask^0xFF;
#endif
  // *****************************************************************************
  // set up ports for output ************ PIN TO TEST IS GIVEN HERE **************
  // *****************************************************************************
  pintest=PTEST;
  pinIntLow=PLOW; pinIntHigh=PHIGH;  // Interrupts are attached to these pins
  // *****************************************************************************
  // *****************************************************************************
  pinT_OP=portOutputRegister(digitalPinToPort(pintest)); // output port
  pinT_IP=portInputRegister(digitalPinToPort(pintest));  // input port
  pinT_M=digitalPinToBitMask(pintest);                   // mask
  not_pinT_M=pinT_M^0xFF;                       // not-mask
  *pinT_OP|=pinT_M;
  for (i=pinIntLow; i <= pinIntHigh; i++) {
#if VERSION >= 200
    PCintPort::attachInterrupt(i, &speedster[i], CHANGE); // C++ technique; v1.3 or better
#else
    PCintPort::attachInterrupt(i, &quicfunc, CHANGE);      // C technique; v1.2 or earlier
#endif
  }
#if TEST == 2 || TEST == 3
  i=5; totalpins=2;
#if VERSION >= 131
  PCintPort::attachInterrupt(i, &speedster[i], CHANGE); // C++ technique; v1.3 or better
#else
  PCintPort::attachInterrupt(i, &quicfunc, CHANGE);      // C technique; v1.2 or earlier
#endif
#else
  totalpins=pinIntHigh - pinIntLow + 1;
#endif
  i=0;
} // end setup()

uint8_t k=0;
unsigned long milliStart, milliEnd, elapsed;
void loop() {
  k=0;
  *pinT_OP|=pinT_M;        // pintest to 1
#ifdef SERIALSTUFF
  Serial.print("TEST: "); Serial.print(TEST, DEC); Serial.print(" ");
#ifndef MEMTEST
  Serial.print("test pin mask: "); Serial.print(pinT_M, HEX);
  Serial.print(" interrupted pin: ");
  Serial.print(speedster[pintest].id, DEC);
  Serial.print(" of a total of "); Serial.print(totalpins, DEC); Serial.println(" pins.");
#endif
#ifdef MEMTEST
  freemem=freeMemory(); Serial.print("Free memory: ");  Serial.println(freemem, DEC);
#endif
#endif
  delay(2000);
  Serial.println("Start...");
  #ifdef FLASH
  *led_port|=led_mask;
  #endif
  milliStart=millis();
  while (k < 10) {
    i=0;
    while (i < 10000) {
      *pinT_OP&=not_pinT_M;    // pintest to 0 ****************************** 16.8 us
      *pinT_OP|=pinT_M;        // pintest to 1 ****************************** ...to get here
      i++;
    }
    k++;
  }
  milliEnd=millis();
  #ifdef FLASH
  *led_port&=not_led_mask;
  #endif
  elapsed=milliEnd-milliStart;
#ifdef SERIALSTUFF
#ifndef MEMTEST
  Serial.print("Elapsed: "); 
  Serial.println(elapsed, DEC);
#endif
#endif
  delay(500);
}

