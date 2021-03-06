// 
// 
// 

#include "PantallaTFT.h"


int PantallaTFT::seleccionProducto(Casilla casillas[])
{
	Casilla ok;
	ok.imagen = "ok.bmp";
	ok.region.X = tft.width() * 3 / 4;
	ok.region.Y = 300;

	int seleccion;
	if (ventanaActual != Ventana::Seleccion) { //Renderizados que solo se dibujan una vez
		tft.fillScreen(Color::Negro);
		for (int i = 0; i < 9; i++)
			dibujarBMP(casillas[i].imagen, casillas[i].region.X, casillas[i].region.Y);

		dibujarBMP(ok.imagen,ok.region.X, ok.region.Y);
		dibujarRejilla();
	}
	ventanaActual = Ventana::Seleccion;
	while (1) {
		int presion;
		Vector2<int> punto = getTouchPoint(presion);
		if (esPresionSuficiente(presion))
		{
			for (int i = 0; i < 9; i++)
			{
				if (casillas[i].estaDentro(punto))
				{
					tft.setTextSize(2);
					tft.setTextColor(Color::Azul, Color::Negro);
					tft.fillRect(0, 320, tft.width(), 20, Color::Negro);
					tft.setCursor(0, 320);
					tft.println(String(casillas[i].producto)+"\n");
					tft.setTextColor(Color::Verde, Color::Negro);
					tft.println(String(casillas[i].precio, '\02') + "E");
					seleccion = i;
				}
			}
			if (ok.estaDentro(punto))
				return seleccion;
		}
	}
	return 0;
}
void PantallaTFT::inicio()
{
	if (ventanaActual == Ventana::Inicio)
		return;
	ventanaActual = Ventana::Inicio;
	tft.fillScreen(Color::Blanco);
	tft.setTextColor(Color::Negro);
	tft.setTextSize(3);
	tft.setCursor(0, 10);
	printCentrado("ACERQUE");
	printCentrado("TARJETA NFC");
	tft.setTextSize(1);
	tft.setCursor(10, tft.height() - 30);
	tft.setTextColor(Color::Rojo);
	tft.println("Maquina Vending - Mecatronica 2017\n");
	tft.setTextSize(1);
	tft.setTextColor(Color::Azul);
	tft.println("@Pablo Horno y Marta Vidal");
	dibujarBMP("nfc.bmp", tft.width() * 1 / 4, tft.height() * 1 / 3);
}

void PantallaTFT::printCentrado(String txt)
{
	tft.setCursor((240 - txt.length() * 240 / 13) / 2, tft.getCursorY());
	tft.println(txt);
}
void PantallaTFT::init()
{
#pragma region Inicializacion TFT

	Serial.println(F("TFT LCD test"));
	Serial.print("Tama�o de TFT: width="+String(tft.width())+" height="+String(tft.height()));
	tft.reset();
	uint16_t identifier = tft.readID();
	tft.begin(identifier);
	tft.fillScreen(Color::Negro);

#pragma endregion

#pragma region Inicializacion SD
	bool good = SD.begin(SD_CS);
	if (!good) {
		Serial.print(F("No se pudo iniciar tarjeta SD"));
	}
#pragma endregion

}
void PantallaTFT::dibujarRejilla()
{
	tft.drawFastVLine(tft.width() * 1 / 3, 0, tft.height() * 3 / 4, Color::Rojo);
	tft.drawFastVLine(tft.width() * 2 / 3, 0, tft.height() * 3 / 4, Color::Rojo);

	tft.drawFastHLine(0, tft.height() * 1 / 4, tft.width(), Color::Rojo);
	tft.drawFastHLine(0, tft.height() * 2 / 4, tft.width(), Color::Rojo);
	tft.drawFastHLine(0, tft.height() * 3 / 4, tft.width(), Color::Rojo);
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
Vector2<int> PantallaTFT::getTouchPoint(int &presion) {
	TSPoint tp = ts.getPoint();
	presion = tp.z;
	Vector2<int> punto;
	punto.X = map(tp.x, limiteTouchIzquierda, limiteTouchDerecha, 0, tft.width());
	punto.Y = map(tp.y, limiteTouchSuperior, limiteTouchInferior, 0, tft.height());
	pinMode(XM, OUTPUT);
	pinMode(YP, OUTPUT);
	pinMode(XP, OUTPUT);
	pinMode(YM, OUTPUT);
	return punto;
}

#define BUFFPIXEL 20

void PantallaTFT::dibujarBMP(char *filename, int x, int y) {
	File 	bmpFile;
	int		bmpWidth, bmpHeight;   // W+H in pixels
	uint8_t	bmpDepth;			   // Bit depth (currently must be 24)
	uint32_t bmpImageoffset; 	   // Start of image data in file
	uint32_t rowSize;			   // Not always = bmpWidth; may have padding
	uint8_t	sdbuffer[3 * BUFFPIXEL]; // pixel in buffer (R+G+B per pixel)
	uint16_t lcdbuffer[BUFFPIXEL];  // pixel out buffer (16-bit per pixel)
	uint8_t	buffidx = sizeof(sdbuffer); // Current position in sdbuffer
	boolean	goodBmp = false;	   // Set to true on valid header parse
	boolean	flip = true; 	   // BMP is stored bottom-to-top
	int		w, h, row, col;
	uint8_t	r, g, b;
	uint32_t pos = 0, startTime = millis();
	uint8_t	lcdidx = 0;
	boolean	first = true;
	uint8_t spi_save;

	if ((x >= tft.width()) || (y >= tft.height())) return;

	Serial.println();
	Serial.print("Cargando Imagen '");
	Serial.print(filename);
	Serial.println('\'');
	// Open requested file on SD card
	SPCR = spi_save;
	if ((bmpFile = SD.open(filename)) == NULL) {
		Serial.print("Archivo no encontrado.");
		return;
	}

	// Parse BMP header
	if (read16(bmpFile) == 0x4D42) { // BMP signature
		Serial.print(F("Tamanio de archivo: ")); Serial.println(read32(bmpFile));
		(void)read32(bmpFile); // Read & ignore creator bytes
		bmpImageoffset = read32(bmpFile); // Start of image data
		Serial.print(F("Image Offset: ")); Serial.println(bmpImageoffset, DEC);
		// Read DIB header
		Serial.print(F("Header size: ")); Serial.println(read32(bmpFile));
		bmpWidth = read32(bmpFile);
		bmpHeight = read32(bmpFile);
		if (read16(bmpFile) == 1) { // # planes -- must be '1'
			bmpDepth = read16(bmpFile); // bits per pixel
			Serial.print(F("Bit Depth: ")); Serial.println(bmpDepth);
			if ((bmpDepth == 24) && (read32(bmpFile) == 0)) { // 0 = uncompressed

				goodBmp = true; // Supported BMP format -- proceed!
				Serial.print(F("Image size: "));
				Serial.print(bmpWidth);
				Serial.print('x');
				Serial.println(bmpHeight);

				// BMP rows are padded (if needed) to 4-byte boundary
				rowSize = (bmpWidth * 3 + 3) & ~3;

				// If bmpHeight is negative, image is in top-down order.
				// This is not canon but has been observed in the wild.
				if (bmpHeight < 0) {
					bmpHeight = -bmpHeight;
					flip = false;
				}

				// Crop area to be loaded
				w = bmpWidth;
				h = bmpHeight;
				if ((x + w - 1) >= tft.width())  w = tft.width() - x;
				if ((y + h - 1) >= tft.height()) h = tft.height() - y;

				// Set TFT address window to clipped image bounds
				SPCR = 0;
				tft.setAddrWindow(x, y, x + w - 1, y + h - 1);

				for (row = 0; row < h; row++) { // For each scanline...
											  // Seek to start of scan line.  It might seem labor-
											  // intensive to be doing this on every line, but this
											  // method covers a lot of gritty details like cropping
											  // and scanline padding.  Also, the seek only takes
											  // place if the file position actually needs to change
											  // (avoids a lot of cluster math in SD library).
					if (flip) // Bitmap is stored bottom-to-top order (normal BMP)
						pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
					else 	// Bitmap is stored top-to-bottom
						pos = bmpImageoffset + row * rowSize;
					SPCR = spi_save;
					if (bmpFile.position() != pos) { // Need seek?
						bmpFile.seek(pos);
						buffidx = sizeof(sdbuffer); // Force buffer reload
					}

					for (col = 0; col < w; col++) { // For each column...
												  // Time to read more pixel data?
						if (buffidx >= sizeof(sdbuffer)) { // Indeed
														   // Push LCD buffer to the display first
							if (lcdidx > 0) {
								SPCR = 0;
								tft.pushColors(lcdbuffer, lcdidx, first);
								lcdidx = 0;
								first = false;
							}
							SPCR = spi_save;
							bmpFile.read(sdbuffer, sizeof(sdbuffer));
							buffidx = 0; // Set index to beginning
						}

						// Convert pixel from BMP to TFT format
						b = sdbuffer[buffidx++];
						g = sdbuffer[buffidx++];
						r = sdbuffer[buffidx++];
						lcdbuffer[lcdidx++] = tft.color565(r, g, b);
					} // end pixel
				} // end scanline
				  // Write any remaining data to LCD
				if (lcdidx > 0) {
					SPCR = 0;
					tft.pushColors(lcdbuffer, lcdidx, first);
				}
				Serial.print(F("Loaded in "));
				Serial.print(millis() - startTime);
				Serial.println(" ms");
			} // end goodBmp
		}
	}

	bmpFile.close();
	if (!goodBmp) Serial.println("BMP format not recognized.");
}

// These read 16- and 32-bit types from the SD card file.
// BMP data is stored little-endian, Arduino is little-endian too.
// May need to reverse subscript order if porting elsewhere.

uint16_t PantallaTFT::read16(File f) {
	uint16_t result;
	((uint8_t *)&result)[0] = f.read(); // LSB
	((uint8_t *)&result)[1] = f.read(); // MSB
	return result;
}

uint32_t PantallaTFT::read32(File f) {
	uint32_t result;
	((uint8_t *)&result)[0] = f.read(); // LSB
	((uint8_t *)&result)[1] = f.read();
	((uint8_t *)&result)[2] = f.read();
	((uint8_t *)&result)[3] = f.read(); // MSB
	return result;
}
