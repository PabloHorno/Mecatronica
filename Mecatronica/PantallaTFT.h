// PantallaTFT.h

#ifndef _PANTALLATFT_h
#define _PANTALLATFT_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <SPI.h>
#include <SD.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Wire.h>
#include <LM75.h>
#include <MCUFRIEND_kbv.h>
#include <TouchScreen.h>
#include "Vector2.h"

// These are the pins for the shield!
#define YP A1  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 6   // can be a digital pin
#define SD_CS 5

enum Color
{
	Negro = 0x0000,
	Azul = 0x001F,
	Rojo = 0xF800,
	Verde = 0x07E0,
	Cyan = 0x07FF,
	Magenta = 0xF81F,
	Amarillo = 0xFFE0,
	Blanco = 0xFFFF
};
class PantallaTFT
{
private:
	MCUFRIEND_kbv tft; 
	TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

	int radio = 0;

public:
	PantallaTFT() {};
	void init();
	void mostrarMenu();
	void dibujarRejilla();
	const int maxPresion = 1000;
	const int minPresion = 10;
	const int limiteTouchDerecha = 170;
	const int limiteTouchIzquierda = 880;
	const int limiteTouchSuperior = 950;
	const int limiteTouchInferior = 180;

	Vector2<int> getTouchPoint();
	Vector2<int> getTouchPoint(int&);
	inline bool esPresionSuficiente(const int presion) { return presion>minPresion && presion < maxPresion; };
	void dibujarBMP(char *filename, int x, int y);

	uint16_t read16(File f);
	uint32_t read32(File f);
	
};

#endif

