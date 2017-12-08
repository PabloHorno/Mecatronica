// MaquinaVending.h

#ifndef _MAQUINAVENDING_h
#define _MAQUINAVENDING_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "PantallaTFT.h"
#include "LectorRIFD.h"

class MaquinaVending
{
 public:
	 PantallaTFT pantalla;
	 LectorRIFD lector;

	void init();

};

void MaquinaVending::init()
{
	pantalla.init();
	lector.init();
}
#endif

