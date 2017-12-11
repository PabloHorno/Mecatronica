// MaquinaVending.h

#ifndef _MAQUINAVENDING_h
#define _MAQUINAVENDING_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
#include "PantallaTFT.h"
#include "Stepper.h"
#include "Casilla.h"
/* Define the DIO used for the SDA (SS) and RST (reset) pins. */
#include <SPI.h>
#include <RFID.h>
#include <String.h>
#define SDA_DIO 28
#define RESET_DIO 29

class MaquinaVending
{
 public:
	 MaquinaVending(int sda, int reset, int dirPinStepper1, int stepPinStepper1, int dirPinStepper2, int stepPinStepper2) :
		 lector(sda, reset),
		 stepper1(dirPinStepper1, dirPinStepper2),
		 steper2(dirPinStepper2, stepPinStepper2) {};
	 PantallaTFT pantalla;
	 RFID lector;
	 Stepper stepper1;
	 Stepper steper2;
	 Casilla casillas[9];
	void init();
private:
	const String productos[9] = { "Coca Cola", "Fanta Naranja", "Fanta Limon", "Coca Cola Zero", "Cerevza", "Otros", "Coca Cola Light", "Coca cola Light", "Agua" };
	/*const*/char* imagenes[9] = { "cc.bmp", "fn.bmp", "fl.bmp", "ccz.bmp", "", "", "", "ccl.bmp", ""};
	const float precios[9] = { 0.75, 0.60, 0.60, 1.20, 0.5, 1.0, 0.90, 0.80, 1.2 };
};

#endif

