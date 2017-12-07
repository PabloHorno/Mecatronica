// 
// 
// 

#include "PantallaTFT.h"

void PantallaTFT::mostrarMenu()
{
	dibujarRejilla();

	while (1) {
		Vector2<int> punto = getTouchPoint();
		tft.setTextSize(2);
		tft.setTextColor(Color::Amarillo, Color::Negro);
		tft.setCursor(0, tft.height() * 3 / 4);
		tft.print("X=" + String(punto.X) + " Y=" + String(punto.Y) + "   ");
	}
}
void PantallaTFT::init()
{
	Serial.println(F("TFT LCD test"));
	Serial.print("Tamaño de TFT"); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());
	tft.reset();
	uint16_t identifier = tft.readID();
	tft.begin(identifier);
	tft.fillScreen(Color::Negro);
}
void PantallaTFT::dibujarRejilla()
{
	tft.drawFastVLine(tft.width() * 2 / 3, 0, tft.height() * 3 / 4, Color::Rojo);
	tft.drawFastVLine(tft.width() * 1 / 3, 0, tft.height() * 3 / 4, Color::Rojo);

	tft.drawFastHLine(0, tft.height() * 1 / 3 * 3 / 4, tft.width(), Color::Rojo);
	tft.drawFastHLine(0, tft.height() * 2 / 3 * 3 / 4, tft.width(), Color::Rojo);
	tft.drawFastHLine(0, tft.height() * 3 / 3 * 3 / 4, tft.width(), Color::Rojo);
}

Vector2<int> PantallaTFT::getTouchPoint()
{
	TSPoint tp = ts.getPoint();
	Vector2<int> punto;
	punto.X = map(tp.x, limiteTouchIzquierda, limiteTouchDerecha, 0, tft.width());
	punto.Y = map(tp.y, limiteTouchSuperior, limiteTouchInferior, 0, tft.height());
	pinMode(XM, OUTPUT);
	pinMode(YP, OUTPUT);
	pinMode(XP, OUTPUT);
	pinMode(YM, OUTPUT);
	return punto;
}
