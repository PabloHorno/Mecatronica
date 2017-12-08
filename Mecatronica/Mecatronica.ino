/*
 Name:		Mecatronica.ino
 Created:	12/7/2017 11:13:06 AM
 Author:	Pablo y Marta
*/

#include "MaquinaVending.h"

MaquinaVending maquina(SDA_DIO, RESET_DIO);

void setup() {
	maquina.init();
}

void loop() {
	maquina.pantalla.inicio();
	if (maquina.lector.isCard())
	{
		maquina.lector.readCardSerial();
	}
	delay(1000);
}
