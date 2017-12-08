// MaquinaVending.h

#ifndef _MAQUINAVENDING_h
#define _MAQUINAVENDING_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
#include <SPI.h>
#include <RFID.h>
#include "PantallaTFT.h"
/* Define the DIO used for the SDA (SS) and RST (reset) pins. */
#define SDA_DIO 28
#define RESET_DIO 29
/* Create an instance of the RFID library */
//RFID lector(SDA_DIO, RESET_DIO);
class MaquinaVending
{
 public:
	 PantallaTFT pantalla;

	void init();

};

#endif

