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

	if (maquina.detectarTarjeta())
	{
		Serial.println("Tarjeta");
		maquina.pantalla.tft.setCursor(10, 250);
		maquina.pantalla.tft.setTextColor(Color::Negro);
		maquina.pantalla.tft.setTextSize(3);
		maquina.pantalla.printCentrado("TARJETA"); 
		maquina.pantalla.printCentrado("DETECTADA");
		maquina.lector.readCardSerial();
		maquina.pantalla.tft.setTextSize(2);
		for (int i = 0; i<5; i++)
			maquina.pantalla.tft.print(maquina.lector.serNum[i], HEX);
		delay(5000);

		int respuesta = maquina.pantalla.seleccionProducto(maquina.casillas);
	}
}
