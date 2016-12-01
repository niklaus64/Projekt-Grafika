#include "NoCompressed.h"




void NoCompressed::compress()
{
}

NoCompressed::NoCompressed(std::string path, int brightness, int contrast, bool greyScale)
{
	di = new DataImage(C_NOT_COMPRESSED);
	di->LoadFromBMP(path);
	if (greyScale) di->GrayScale();
	if (brightness != 0) di->brightness(brightness);
	if (contrast != 0) di->contrast(contrast);

}

NoCompressed::~NoCompressed()
{
}

void NoCompressed::saveToFile(std::string path)
{
	di->WriteDataToBMP(path);
}
