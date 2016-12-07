#include "RLE.h"

void RLE::compress()
{
	auto a = di->pixmap.begin();
}

void RLE::decompress()
{
}

void RLE::saveToFile(const std::string)
{
}

RLE::RLE(std::string path, int brightness, int contrast, bool greyScale)
{
	di = new DataImage(C_RLE);
	di->LoadFromBMP(path);
	if (greyScale) di->GrayScale();
	if (brightness != 0) di->brightness(brightness);
	if (contrast != 0) di->contrast(contrast);
}


RLE::~RLE()
{
}
