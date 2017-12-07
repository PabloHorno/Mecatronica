/*
 Name:		Mecatronica.ino
 Created:	12/7/2017 11:13:06 AM
 Author:	Pablo y Marta
*/

#include "PantallaTFT.h"

PantallaTFT pantalla;
void setup() {
	pantalla.init();
}

void loop() {
	pantalla.mostrarMenu();
	delay(1000);
}
