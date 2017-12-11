// Stepper.h

#ifndef _STEPPER_h
#define _STEPPER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class Stepper
{
 protected:

	 int dirPin, stepPin, _direccion;
 public:
	 Stepper(int dirPin, int stepPin)
	 {
		 this->dirPin = dirPin;
		 this->stepPin = stepPin;
	 }
	void init();
	void paso(int velocidad = 500);
	void direccion(int dir = -1);
};

#endif

