// Casilla.h

#ifndef _CASILLA_h
#define _CASILLA_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Servo.h>
#include "Vector2.h"

class Casilla
{
 protected:
	 Servo servo;
public:
	int pinServo;
	String producto;
	char* imagen;
	float precio;
	Vector2<int> region;
	void init();
	void abrir() {
		servo.write(170);
	}
	void cerrar()
	{
		servo.write(20);
	}
	bool estaDentro(Vector2<int> punto);
};

#endif

