// 
// 
// 

#include "MaquinaVending.h"

void MaquinaVending::init()
{
	SPI.begin();
	lector.init();
	pantalla.init();
}