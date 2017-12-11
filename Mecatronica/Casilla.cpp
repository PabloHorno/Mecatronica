// 
// 
// 

#include "Casilla.h"

void Casilla::init()
{
	servo.attach(pinServo);
}

bool Casilla::estaDentro(Vector2<int> punto)
{
	return region.X < punto.X && region.X + 80 > punto.X &&
		region.Y < punto.Y && region.Y + 106 > punto.Y;
}

