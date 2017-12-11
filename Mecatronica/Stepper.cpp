// 
// 
// 

#include "Stepper.h"

void Stepper::init()
{
	pinMode(dirPin, OUTPUT);
	pinMode(stepPin, OUTPUT);

}

void Stepper::paso(int velocidad)
{
	digitalWrite(stepPin, HIGH);
	delayMicroseconds(velocidad);
	digitalWrite(stepPin, LOW);
	delayMicroseconds(velocidad);
}

void Stepper::direccion(int dir)
{
	if (dir < 0)
		_direccion = !_direccion;
	else
		_direccion = dir;

	digitalWrite(dirPin, _direccion);
}

