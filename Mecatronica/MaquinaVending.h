// MaquinaVending.h

#ifndef _MAQUINAVENDING_h
#define _MAQUINAVENDING_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
#include "PantallaTFT.h"
/* Define the DIO used for the SDA (SS) and RST (reset) pins. */
#include <SPI.h>
#include <RFID.h>
#define SDA_DIO 28
#define RESET_DIO 29

class MaquinaVending
{
 public:
	 MaquinaVending(int sda, int reset):lector(sda,reset) {};
	 PantallaTFT pantalla;
	 RFID lector;
	void init();

};

#endif

