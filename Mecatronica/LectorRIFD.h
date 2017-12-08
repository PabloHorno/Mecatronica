// LectorRIFD.h

#ifndef _LECTORRIFD_h
#define _LECTORRIFD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
/*
PINOUT:
RC522 MODULE    Uno/Nano     MEGA
SDA             D10          D9
SCK             D13          D52
MOSI            D11          D51
MISO            D12          D50
IRQ             N/A          N/A
GND             GND          GND
RST             D9           D8
3.3V            3.3V         3.3V
*/
/* Include the standard Arduino SPI library */
#include <SPI.h>
/* Include the RFID library */
#include <RFID.h>

/* Define the DIO used for the SDA (SS) and RST (reset) pins. */
#define SDA_DIO 28
#define RESET_DIO 29
/* Create an instance of the RFID library */

RFID lector(SDA_DIO, RESET_DIO);

class LectorRIFD
{
private:
	uint16_t sda_dio, reset_dio;
public:
	void init();
};

#endif

