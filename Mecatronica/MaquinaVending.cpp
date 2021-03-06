// 
// 
// 

#include "MaquinaVending.h"

bool MaquinaVending::
detectarTarjeta()
{
	SPI.endTransaction();
	SPI.beginTransaction(SPISettings());
	return maquina.lector.isCard();
}

void MaquinaVending::init()
{
	SPI.begin();
	pantalla.init();
	lector.init();

	Serial.println("\nCASILLAS");
	for (int i = 0, index = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			casillas[index].region.X = 240 * j / 3;
			casillas[index].region.Y = 400 * i / 4;
			casillas[index].producto = this->productos[index];
			casillas[index].precio = this->precios[index];
			casillas[index].imagen = this->imagenes[index];
			index++;
		}
}