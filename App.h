#pragma once
#include "RLE.h"
#include "Enum.h"
#include "Own5Bits.h"
#include "NoCompressed.h"

class App
{
	//tymczasowe scie¿ki plików
	const std::string PATH_TO_FILE_BMP = "3.bmp";
	const std::string PATH_TO_FILE_SZMIK = "wynik.szmik";
	const std::string PATH_TO_SAVE_FILE_SZMIK = "wynik.szmik";
	const std::string PATH_TO_SAVE_FILE_BMP = "wynik.bmp";


	compressionType cT;
	Algorithm *al;
public:
	App();
	void po_nacisnieciu_compress();
	void poNacisnieciuSave();
	~App();
};
