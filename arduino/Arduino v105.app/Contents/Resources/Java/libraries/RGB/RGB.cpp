#include "Arduino.h"
#include "RGB.h"
#include "NilRTOS.h"
#include "SoftPWM.h"


RGB::RGB(int redPin, int greenPin, int bluePin) {
  _redPin=(byte)redPin;
  _greenPin=(byte)greenPin;
  _bluePin=(byte)bluePin;
#ifdef SOFTPWM_H
	SoftPWMBegin();
	SoftPWMSet(_redPin, 0);
	SoftPWMSet(_greenPin, 0);
	SoftPWMSet(_bluePin, 0);
#else
	pinMode(_redPin, OUTPUT);
	pinMode(_greenPin, OUTPUT);
	pinMode(_bluePin, OUTPUT);
#endif
}

void RGB::set(int newRed, int newGreen, int newBlue) {
  _red=newRed;
  _green=newGreen;
  _blue=newBlue;
  apply();
}


void RGB::goRandom(int nbStep) {
	go((byte)random(256),(byte)random(256),(byte)random(256),nbStep);
}

void RGB::go(int newRed, int newGreen, int newBlue, int nbStep) {
	double stepRed=(newRed-_red)/nbStep;
	double stepGreen=(newGreen-_green)/nbStep;
	double stepBlue=(newBlue-_blue)/nbStep;
	_oriRed=_red;
	_oriGreen=_green;
	_oriBlue=_blue;
	for (int i=1; i<=nbStep; i++) {
		_red=_oriRed+(stepRed*i);
		_green=_oriGreen+(stepGreen*i);
		_blue=_oriBlue+(stepBlue*i);
		apply();
#ifdef NilRTOS_h
	nilThdSleepMilliseconds(40);
#else
	delay(40);
#endif
	}
}

void RGB::randomColor() {
	_red=(byte)random(256);
	_green=(byte)random(256);
	_blue=(byte)random(256);
	apply();
}

void RGB::apply() {

#ifdef SOFTPWM_H
	SoftPWMSet(_redPin, _red);
	SoftPWMSet(_greenPin, _green);
	SoftPWMSet(_bluePin, _blue);
#else
	analogWrite(_redPin, _red);
	analogWrite(_greenPin, _green);
	analogWrite(_bluePin, _blue);
#endif

}

