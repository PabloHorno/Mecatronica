/*
 Name:		Mecatronica.ino
 Created:	12/7/2017 11:13:06 AM
 Author:	Pablo y Marta
*/

#include "MaquinaVending.h"
#define DIRPIN1 42
#define STEPPIN1 43
#define DIRPIN2 44
#define STEPPIN2 45

MaquinaVending maquina(SDA_DIO, RESET_DIO, DIRPIN1, STEPPIN1, DIRPIN2, STEPPIN2);

void setup() {
	maquina.init();
}

void loop() {
	maquina.pantalla.inicio();
	if (maquina.lector.isCard())
	{
		maquina.pantalla.tft.setCursor(10, 200);
		maquina.pantalla.tft.print("TARJETA DETECTADA");
		maquina.lector.readCardSerial();
		for (int i = 0; i<5; i++)
			maquina.pantalla.tft.print(maquina.lector.serNum[i], DEC);
		maquina.pantalla.tft.println("\n------");
		for (int i = 0; i<5; i++)
			maquina.pantalla.tft.print(maquina.lector.serNum[i], HEX);
		while (true)
		{
			int respuesta = maquina.pantalla.seleccionProducto(maquina.casillas);
		}
	}
	delay(1000);
}
