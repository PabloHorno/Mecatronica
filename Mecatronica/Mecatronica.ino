/*
 Name:		Mecatronica.ino
 Created:	12/7/2017 11:13:06 AM
 Author:	Pablo y Marta
*/

#include "MaquinaVending.h"

MaquinaVending maquina;

void setup() {
	maquina.init();
}

void loop() {
	maquina.pantalla.inicio();
	delay(1000);
}
