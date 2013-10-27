#ifndef RGB_h
#define RGB_h

#include "Arduino.h"
#include "NilRTOS.h"
#include "SoftPWM.h"

class RGB {

public:
	RGB(int red, int green, int blue);
	void set(int newRed, int newGreen, int newBlue);
	void go(int newRed, int newGreen, int newBlue, int nbStep);
	void goRandom(int nbStep);
	void randomColor();

private:
  byte _redPin;
  byte _greenPin;
  byte _bluePin;
  byte _red;
  byte _green;
  byte _blue;
  byte _oriRed;
  byte _oriGreen;
  byte _oriBlue;
  void apply();
};

#endif